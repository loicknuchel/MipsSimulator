#include "inc.h"
//#define DEBUG

/* Commandes a ajouter :
	- smems <size> : change la taille de la memoire
	- smemi <address> <instr> : rentre en memoire l'instruction en parametre
	- dmemnn [<address>] [<address>] : display memoire not null : idem que dmem sans ecrire les octet a 0
*/

// load <filename>
int s_load(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide){
	int len;
	int i;
	int j = 0;
	unsigned int instr32, instr32LO, A, P, S, modif, AHL, AHI, ALO;
	Elf32_Rel entry;
	FILE * source;
	char file_name[50];
	
	unsigned char *textSection = NULL;
	unsigned char *dataSection = NULL;
	Elf32_Sym *symbolTable = NULL;
	unsigned char **stringTable = NULL;
	Elf32_Rel *relTextSection = NULL;
	Elf32_Rel *relDataSection = NULL;
	
	unsigned int textSectionSize = 0;
	unsigned int dataSectionSize = 0;
	unsigned int bssSectionSize = 0;
 	unsigned int symbolTableSize = 0;
 	unsigned int stringTableSize = 0;
	unsigned int relTextSectionSize = 0;
	unsigned int relDataSectionSize = 0;
	
	unsigned int textSectionAddr = 0;
	unsigned int dataSectionAddr = 0;
	unsigned int textSectionfin = 0;
	unsigned int dataSectionfin = 0;
	unsigned int nb_octet_text = 0;
	unsigned int nb_octet_data = 0;
	
	len = strlen(util_sim[1]);
	
	if(util_sim[3][0] != '\0'){
		RED
		printf("\n  ERROR : too many arguments in fonction load (%s)\n", util_sim[2]);
		ENDCOLOR
		return 1;
	}
	else if(util_sim[2][0] != '\0' && is_number(util_sim[2]) == 0){
		RED
		printf("\n  ERROR : l'argument 2 doit etre une addresse (%s)\n", util_sim[2]);
		ENDCOLOR
		return 1;
	}
	else if(util_sim[1][0] == '\0'){
		RED
		printf("\n  ERROR : You have to write the filename\n");
		ENDCOLOR
		return 1;
	}
	else if(util_sim[1][len-4] != '.' && ( (util_sim[1][len-3] != 'e' && util_sim[1][len-2] != 'l' && util_sim[1][len-1] != 'f') || (util_sim[1][len-3] != 'o' && util_sim[1][len-2] != 'u' && util_sim[1][len-1] != 't') ) ){
		RED
		printf("\n  ERROR : the file must be a .out (ou .elf) file !\n");
		ENDCOLOR
		return 1;
	}
	else{
		strcpy(file_name, util_sim[1]);
		if(strcmp(file_sim->nom, "") != 0){
			RED
			printf("\n  Former file (%s) overwritten.\n", file_sim->nom);
			ENDCOLOR
		}
		if(is_number(util_sim[2]) != 0){
			textSectionAddr = atohi(util_sim[2]);
		}
		else{
			textSectionAddr = 0;
		}
		source = fopen(file_name, "r");
		if(source == NULL){
			RED
			printf("\n  Problem opening the file \"%s\"\n", file_name);
			ENDCOLOR
			return 1;
		}
		fclose(source);
		
		util_sim[1][0] = '\0';
		s_clear(simulateur, breakpoint, instruction_asm, aide);
		
		openElf(file_name);
		
		getTextSection(&textSectionSize, &textSection);
		getDataSection(&dataSectionSize, &dataSection);
		getBssSection(&bssSectionSize);
		getSymbolTable(&symbolTableSize, &symbolTable);
		getStringTable(&stringTableSize, &stringTable);
		getTextRelocSection(&relTextSectionSize, &relTextSection);
		getDataRelocSection(&relDataSectionSize, &relDataSection);
		
		textSectionfin = textSectionAddr + textSectionSize;
		dataSectionAddr = 4096*(textSectionfin/4096)+4096;
		dataSectionfin = dataSectionAddr + dataSectionSize;
		
		#ifdef DEBUG
			printf("\n");
			printSection(".text", textSectionSize, textSection);
			printf("\n");
			printSection(".data", dataSectionSize, dataSection);
			printf("\n");
			printf("Section .bss: %d octets (all at 0)\n", bssSectionSize);
			printf("\n");
			printSymbols(symbolTable, stringTable, symbolTableSize);
			printf("\n");
			printRelTable(".rel.text", relTextSectionSize, relTextSection);
			printf("\n");
			printRelTable(".rel.data", relDataSectionSize, relDataSection);
			printf("\n");
		#endif
		
		if(dataSectionfin > mem_size_sim){
			RED
			printf("\n  File too big !\n");
			ENDCOLOR
			return 1;
		}
		
		
		nb_octet_text = loadSectionReloc(simulateur, textSectionAddr, dataSectionAddr, textSectionAddr, textSectionSize, textSection, relTextSection);
		*breakpoint = add_bp(*breakpoint, textSectionfin, 2);
		nb_octet_data = loadSectionReloc(simulateur, textSectionAddr, dataSectionAddr, dataSectionAddr, dataSectionSize, dataSection, relDataSection);
		*breakpoint = add_bp(*breakpoint, dataSectionfin, 2);
		
		printf("\n  Section .text : 0x%x octets at the adress 0x%x\n", nb_octet_text, textSectionAddr);
		printf("  Section .data : 0x%x octets at the adress 0x%x\n", nb_octet_data, dataSectionAddr);
		
		set_file(file_sim, file_name, dataSectionfin, 0, bssSectionSize, textSectionAddr, textSectionSize, dataSectionAddr, dataSectionSize);
		
		closeElf();
		if(textSection) free(textSection);
		if(dataSection) free(dataSection);
		if (stringTable) {
			for (i=0; i<stringTableSize; i++)
				free(stringTable[i]);
			free(stringTable);
		}
	}
	
	printf("Load ok\n");
	return 1;
}

// clear
int s_clear(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide){
	int i;
	
	if(util_sim[1][0] == '\0'){
		for(i=0; i<32; i++){
			reg_sim[i].val = 0;
		}
		
		for(i=0; i<mem_size_sim; i++){
			mem_sim[i] = 0;
		}
		
		rm_all_bp(breakpoint, 0); /*0 : bp du stpi*/
		rm_all_bp(breakpoint, 1); /*1 : bp utilisateur*/
		rm_all_bp(breakpoint, 2); /*2 : bp de fin de section*/
		*breakpoint = add_bp(*breakpoint, mem_size_sim, 3);
		
		empty_file(file_sim);
		
		pc_sim->val = 0;
		hi_sim->val = 0;
		lo_sim->val = 0;
		
		for(i=0; i<NB_ENTREE_UTIL; i++){
			util_sim[i][0] = '\0';
		}
	}
	else{
		if(strcmp(util_sim[1], "reg") == 0){
			for(i=0; i<32; i++){
				reg_sim[i].val = 0;
			}
			
			pc_sim->val = 0;
			hi_sim->val = 0;
			lo_sim->val = 0;
		}
		else if(strcmp(util_sim[1], "mem") == 0){
			for(i=0; i<mem_size_sim; i++){
				mem_sim[i] = 0;
			}
			
			empty_file(file_sim);
		}
		else{
			RED
			printf("\n  Synthaxe Error\n");
			ENDCOLOR
		}
	}
	
	return 1;
}

// dasm
int s_dasm(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide){
	int i;
	char error[256];
	unsigned int textaddr, dataaddr, textfin, datafin;
	
	if(file_sim->nom[0] != '\0'){
		textaddr = file_sim->text;
		textfin = file_sim->text + file_sim->sizetext;
		dataaddr = file_sim->data;
		datafin = file_sim->data + file_sim->sizedata;
		
		printf("\n  ---------- Desassemblage --------------------------------------------\n");
		printf("  --\n");
		printf("  --                 .set noreorder\n");
		printf("  --                 .set noat\n");
		printf("  --                 .text\n");
		for(i=textaddr; i<textfin; i=i+4){
			printf("  -- %04x  %08x  %s\n", i, assemble_mot(mem_sim[i], mem_sim[i+1], mem_sim[i+2], mem_sim[i+3]), traduit_instruction(simulateur, instruction_asm, i, error));
		}
		printf("  --\n");
		/*printf("  --                 .data\n");
		for(i=dataaddr; i<datafin; i=i+4){
			printf("  -- %04x  %08x\n", i, assemble_mot(mem_sim[i], mem_sim[i+1], mem_sim[i+2], mem_sim[i+3]), traduit_instruction(simulateur, instruction_asm, i, error));
		}
		printf("  --\n");*/
		printf("  --------------------------------------------------------------------\n");
	}
	else{
		RED
		printf("\n  No file loaded in memory !\n");
		ENDCOLOR
	}
	return 1;
}

// dreg [<registername>]
int s_dreg(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide){
	int no = 0;
	char nom_reg[20];
	
	if(util_sim[2][0] == '\0'){
		if(util_sim[1][0] == '\0'){
			display_reg(simulateur);
		}
		else{
			if(is_number(util_sim[1]) == 0){
				if(strcmp(util_sim[1], "PC") == 0){
					printf("\n  REGISTRE special PC : 0x%x\n", get_pc(simulateur));
				}
				if(strcmp(util_sim[1], "HI") == 0){
					printf("\n  REGISTRE special HI : 0x%x\n", get_hi(simulateur));
				}
				if(strcmp(util_sim[1], "LO") == 0){
					printf("\n  REGISTRE special LO : 0x%x\n", get_lo(simulateur));
				}
				else if(util_sim[1][0] != '$'){
					sprintf(nom_reg, "$%s", util_sim[1]);
				}
				else{
					sprintf(nom_reg, "%s", util_sim[1]);
				}
				no = get_no_reg(reg_sim, nom_reg);
				if(no == 32){
					printf("\n  registre not found\n");
					return 1;
				}
			}
			else{
				no = atohi(util_sim[1]);
				if(no < 0 || no > 31){
					RED
					printf("\n  There are only 32 registers (0 to 31) !\n");
					ENDCOLOR
					return 1;
				}
			}
			
			printf("\n  REGISTRE no 0x%x (%s) : 0x%x\n", no, reg_sim[no].nom, reg_sim[no].val);
		}
	}
	else{
		RED
		printf("\n  Synthaxe Error\n");
		ENDCOLOR
	}
	
	return 1;
}

// sreg <registername> <value>
int s_sreg(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide){
	int no = 0;
	int val = 0;
	char nom_reg[20];
	
	if(util_sim[1][0] != '\0' && util_sim[2][0] != '\0' && util_sim[3][0] == '\0'){
		if(is_number(util_sim[1]) == 0){
			if(util_sim[1][0] != '$'){
				sprintf(nom_reg, "$%s", util_sim[1]);
			}
			else{
				sprintf(nom_reg, "%s", util_sim[1]);
			}
			
			no = get_no_reg(reg_sim, nom_reg);
			if(no == 32){
				RED
				printf("\n  registre not found\n");
				ENDCOLOR
				return 1;
			}
		}
		else{
			no = atohi(util_sim[1]);
			if(no < 0 || no > 31){
				RED
				printf("\n  There are only 32 registers (0 to 31) !\n");
				ENDCOLOR
				return 1;
			}
		}
		
		if(is_number(util_sim[2]) == 0){
			RED
			printf("\n  Synthaxe Error\n");
			ENDCOLOR
			return 1;
		}
		else{
			val = atohi(util_sim[2]);
			if(val > 255){
				RED
				printf("\n  ERREOR : a register takes values between 0 and 255 !");
				ENDCOLOR
				return 1;
			}
		}
		
		reg_sim[no].val = val;
		printf("\n  REGISTER no 0x%x (%s) : 0x%02x\n", no, reg_sim[no].nom, reg_sim[no].val);
		
	}
	else{
		RED
		printf("\n  Synthaxe Error\n");
		ENDCOLOR
	}
	
	return 1;
}

// dmem <adress> [<address>]
int s_dmem(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide){//OK
	int debut;
	int fin;
	
	if(is_number(util_sim[1]) == 1){
		debut = atohi(util_sim[1]);
		if(debut > mem_size_sim){
			RED
			printf("\n  The begin adress required is higher than the memory size (0x%x)!\n", mem_size_sim);
			ENDCOLOR
		}
		else{
			if(is_number(util_sim[2]) == 1){
				fin = atohi(util_sim[2]); 
				if(fin > mem_size_sim){
					RED
					printf("\n  The end adress required is more important than the memory size  (0x%x)!\n", mem_size_sim); 
					ENDCOLOR
				}
				else{
					if(fin < debut){
						RED
						printf("\n  The begin adress(0x%x) is higher than the end adress(0x%x) !\n", debut, fin);
						ENDCOLOR
					}
					else{
						if(util_sim[3][0] == '\0'){
							display16_mem(simulateur, instruction_asm, debut, fin);
						}
						else if(is_number(util_sim[3]) == 1 && atohi(util_sim[3]) == 4){
							display4_mem(simulateur, instruction_asm, debut, fin);
						}
						else{
							RED
							printf("\n  dmem does not take argument 3 !\n");
							ENDCOLOR
						}
					}
				}
			}
			else{	
				display16_mem(simulateur, instruction_asm, debut, debut+1);
			}
		}
		
	}
	else{
		RED
		printf("\n  The argument 1 must be an adress\n");
		ENDCOLOR
	}
	
	
	return 1;
}

// smem <address> <value>
int s_smem(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide){
	
	if(is_number(util_sim[1]) == 0){
		RED
		printf("\n  The argument 1 must be an adress\n");
		ENDCOLOR
	}
	else if(is_number(util_sim[2]) == 0){
		RED
		printf("\n  The argument 2 must be an hexadecimal or a decimal value\n");
		ENDCOLOR
	}
        else{
		simulateur.memoire[atohi(util_sim[1])]=atohi(util_sim[2]);
		printf("mem[0x%x]=0x%02x\n", atohi(util_sim[1]), atohi(util_sim[2]));
	}

	return 1;
}

// run [<address>]
int s_run(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide){
	int val_pc, right, exec = 0;
	BP p = calloc(1,sizeof(*p));
	p = *breakpoint;
	char error[256];
	
	if(util_sim[1][0] != '\0'){
		if(is_number(util_sim[1]) != 0){
			val_pc = atohi(util_sim[1]);
			val_pc = 4*(val_pc/4);
			set_pc(simulateur, val_pc);
			exec = 1;
		}
		else{
			RED
			printf("\n  The argument 1 must be an adress\n");
			ENDCOLOR
		}
	}
	else{
		val_pc = get_pc(simulateur);
		exec = 1;
	}
	
	if(exec == 1){
		while(p->bp <= val_pc){
			if(p->suiv == NULL){
				RED
				printf("\n  execution Adress uncorrect\n");
				ENDCOLOR
				return 1;
			}
			p = p->suiv;
		}
		
		while(get_pc(simulateur) < p->bp){
			error[0] = '\0';
			right = execute_instruction(simulateur, &bp_sim, instruction_asm, error);
			if(error[0] != '\0'){
				RED
				printf("  %s\n", error);
				ENDCOLOR
			}
			if(right == 2){
				return 1;
			}
		}
		
		if(p->type == 0){/*bp de stepi*/
			return 1;
		}
		else if(p->type == 1){/*bp utilisateur*/
			printf("\n  Bp found\n");
		}
		else if(p->type == 2){/*bp fin section*/
			printf("\n  You have reached the end of the section .text\n");
		}
		else if(p->type == 3){/*bp fin memoire*/
			printf("\n  You have reached the end of the memory\n");
		}
		
		printf("PC: 0x%x\n", get_pc(simulateur));
	}
	
	return 1;
}

// step
int s_step(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide){
	char error[256];
	char instr[256];
	int right;
	int PC;
	
	if(util_sim[1][0] == '\0' || is_number(util_sim[1]) != 0){
		if(is_number(util_sim[1]) != 0){
			PC = atohi(util_sim[1]);
			set_pc(simulateur, PC);
		}
		error[0] = '\0';
		sprintf(instr, "%s", traduit_instruction(simulateur, instruction_asm, get_pc(simulateur), error));
		right = execute_instruction(simulateur, &bp_sim, instruction_asm, error);
		if(right != 2){
			printf("\n  %s\n", instr);
		}
		if(error[0] != '\0'){
			RED
			printf("  %s\n", error);
			ENDCOLOR
		}
		if(right == 2){
			return 1;
		}
	}
	else{
		RED
		printf("\n  Synthaxe Error\n");
		ENDCOLOR
		return 1;
	}
	
	printf("  PC: 0x%x\n", get_pc(simulateur));
	return 1;
}

// stepi
int s_stepi(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide){
	char error[256];
	unsigned int PC;
	
	PC = get_pc(simulateur);
	
	*breakpoint = add_bp(*breakpoint, PC+4, 0); /*0: ajout bp stepi*/
	s_run(simulateur, breakpoint, instruction_asm, aide);
	*breakpoint = rm_bp(breakpoint, PC+4, 0); /*suppr bp stepi*/
	
	printf("  PC: 0x%x\n", get_pc(simulateur));
	return 1;
}

// addbp <address>
int s_addbp(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide){
	int val;
	
	if(util_sim[1][0] != '\0'){
		if(is_number(util_sim[1]) == 1){
			val = 4*(atohi(util_sim[1])/4);
			*breakpoint = add_bp(*breakpoint, val, 1); /*1: bp ajoute par l'utilisateur*/
		}
		else{
			RED
			printf("\n  The argument 1 must be a valid adress\n");
			ENDCOLOR
		}
	}
	else{
		RED
		printf("\n  Synthaxe Error\n");
		ENDCOLOR
	}
	
	return 1;
}

// rmbp [<address>]
int s_rmbp(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide){
	int val;
	
	if(strcmp(util_sim[1], "") == 0){
		*breakpoint = rm_all_bp(breakpoint, 1);/*type 1 : bp utilisateur*/
	}
	else{
		if(is_number(util_sim[1]) == 1){
			val = atohi(util_sim[1]);
			*breakpoint = rm_bp(breakpoint, val, 1);
		}
		else{
			RED
			printf("\n  Synthaxe Error\n");
			ENDCOLOR
		}
	}
	
	return 1;
}

// dbp
int s_dbp(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide){
	int type;
	
	if(is_number(util_sim[1]) == 1){
		type = atohi(util_sim[1]);
		if(type == 0 || type == 1 || type == 2 || type == 3){
			display_bp(bp_sim, type);/*0: step, 1: utilisateur, 2: fin section, 3: fin memoire*/
		}
		else{
			RED
			printf("  Second argument unknown\n");
			ENDCOLOR
		}
	}
	else if(util_sim[2][0] == '\0'){
		display_bp(bp_sim, 10); /*1: affiche les bp de l'utilisateur*/
	}
	else{
		RED
		printf("  Second argument wrong\n");
		ENDCOLOR
	}
	
	return 1;
}

// help [<command>]
int s_help(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide){
	
	if(util_sim[1][0] == '\0'){
		printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> HELP <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n>>\n");
		if(aide == NULL){
			RED
			printf("\n>>  There is notnhing in Help !\n");
			ENDCOLOR
		}
		else{
			while(aide->suiv != NULL){
				/*printf("################## %s ##################\n\n", aide->commande);
				printf("> %s\n\n", aide->short_desc);
				printf("> %s\n", aide->long_desc);
				printf("\n\n\n");*/
				printf(">> ");
				GREEN
				printf("%s", aide->prototype);
				ENDCOLOR
				printf(" : %s\n>>\n", aide->short_desc);
				aide = aide->suiv;
			}
			printf(">> ");
			GREEN
			printf("%s", aide->prototype);
			ENDCOLOR
			printf(" : %s\n>>\n", aide->short_desc);
		}
		
		printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> END HELP <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	}
	else{
		while(aide->suiv != NULL){
			if(strcmp(util_sim[1], aide->commande) == 0){
				GREEN
				printf("\n  %s", aide->prototype);
				ENDCOLOR
				printf(" : \n\n  %s\n", aide->long_desc);
				return 1;
			}
			aide = aide->suiv;
		}
	}
	//display_help(aide);
	return 1;
}

// exit
int s_exit(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide){
	char c;
	
	/*while(c != 'y' || c != 'n'){
		printf("  Quit program ? (y)es (n)o\n  ");
		scanf("%c", &c);
		if(c == 'y'){
			getchar();
			return 0;
		}
		else if(c == 'n'){
			getchar();
			return 1;
		}
	}
	*/
	return 0;
}








int s_dfile(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide){
	display_file(file_sim);
	return 1;
}

int s_smems(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide){
/*	void * tmp;
	int taille;
	
	if(is_number(util_sim[1]) != 0){
		taille = atohi(util_sim[1]);
		tmp = realloc(mem_sim, taille);
		if(tmp != NULL){
			mem_sim = tmp;
			free(tmp);
		}
		else{
			printf("  reallocation de memoire echoue\n");
		}
	}
	else{
		printf(" L'argument 1 doit etre la taille de la memoire\n");
	}
	
	return 1;
*/
}

int s_dmemnn(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide){
	int i;
	int n;
	char error[256];
	
	printf("\n  ---- MEMOIRE Non Nulle -----------------------------------------\n");
	printf("  --\n");
	
	if(strcmp(util_sim[1], "") == 0 || atohi(util_sim[1]) == 4){
		for(i=0; i<mem_size_sim; i=i+4){
			if(mem_sim[i] != 0 || mem_sim[i+1] != 0 || mem_sim[i+2] != 0 || mem_sim[i+3] != 0){
				printf("  -- 0x%06x) 0x%02x 0x%02x 0x%02x 0x%0x2 : %s\n", i, mem_sim[i], mem_sim[i+1], mem_sim[i+2], mem_sim[i+3], traduit_instruction(simulateur, instruction_asm, i, error));
				n = 1;
			}
			else{
				if(n == 1){
					printf("  --\n");
				}
				n = 0;
			}
		}
	}
	else if(strcmp(util_sim[1], "") == 0){
		for(i=0; i<mem_size_sim; i=i+16){
			if(mem_sim[i] != 0 || mem_sim[i+1] != 0 || mem_sim[i+2] != 0 || mem_sim[i+3] != 0 || mem_sim[i+4] != 0 || mem_sim[i+5] != 0 || mem_sim[i+6] != 0 || mem_sim[i+7] != 0 || mem_sim[i+8] != 0 || mem_sim[i+9] != 0 || mem_sim[i+10] != 0 || mem_sim[i+11] != 0 ||mem_sim[i+12] != 0 || mem_sim[i+13] != 0 || mem_sim[i+14] != 0 || mem_sim[i+15] != 0){
				printf("  -- 0x%06x) 0x%02x 0x%02x 0x%02x 0x%0x2   0x%02x 0x%02x 0x%02x 0x%0x2   0x%02x 0x%02x 0x%02x 0x%0x2   0x%02x 0x%02x 0x%02x 0x%0x2\n", i, mem_sim[i], mem_sim[i+1], mem_sim[i+2], mem_sim[i+3], mem_sim[i+4], mem_sim[i+5], mem_sim[i+6], mem_sim[i+7], mem_sim[i+8], mem_sim[i+9], mem_sim[i+10], mem_sim[i+11], mem_sim[i+12], mem_sim[i+13], mem_sim[i+14], mem_sim[i+15]);
				n = 1;
			}
			else{
				if(n == 1){
					printf("  --\n");
				}
				n = 0;
			}
		}
	}
	
	printf("  ------------------------------------------------------------------\n");
	
	return 1;
}

int s_dmips(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide){
	affiche_mips(simulateur, instruction_asm);
	return 1;
}





