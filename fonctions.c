#include "inc.h"
//#define DEBUG

int execute_instruction(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, char * error){
	unsigned int PC;
	int right;
	uint instruction;
	uint opcode;
	uint rs;
	uint rt;
	uint rd;
	uint sa;
	uint function;
	uint immediate;
	uint instr_index;
	uint reste;
	
	PC = get_pc(simulateur);
	instruction = assemble_mot(get_mem(simulateur, PC), get_mem(simulateur, PC+1), get_mem(simulateur, PC+2), get_mem(simulateur, PC+3));
	if(PC < file_sim->text || PC > file_sim->text + file_sim->sizetext){
		sprintf(error, "  ERROR. Execution forbiden outside of the section .text");
		return 2;
	}
	PC = PC+4;
	if(set_pc(simulateur, PC) == 2){
		RED
		printf("\n  execution Adress uncorrect\n");
		ENDCOLOR
		return 1;
	}
	
	if(instruction != 0){
		opcode = recup_opcode(instruction);
		if(opcode == 0){
			function = recup_function(instruction);
			if( instruction_exist( instruction_asm, get_nom_instr( instruction_asm, function ) ) == 1 ){
				instruction_asm[function].instr(simulateur, instruction_asm, instruction, error);
			}
			else{
				sprintf(error, "  ERROR MEMORY. Unknown fonction !");
				return 1;
			}
		}
		else{
			if( instruction_exist( instruction_asm, get_nom_instr( instruction_asm, opcode+NB_MAX_OPCODE ) ) == 1 ){
				instruction_asm[opcode+NB_MAX_OPCODE].instr(simulateur, instruction_asm, instruction, error);
			}
			else{
				sprintf(error, "  ERROR MEMORY. Unknown fonction !");
				return 1;
			}
		}
	}
	
	return 1;
}

char * traduit_instruction(MIPS simulateur, INSTR * instruction_asm, int adresse, char * error){
	uint instruction;
	uint opcode;
	uint rs;
	uint rt;
	uint rd;
	uint sa;
	uint function;
	uint immediate;
	uint instr_index;
	char * traduction = calloc(50, sizeof(char));
	
	
	instruction = assemble_mot(get_mem(simulateur, adresse), get_mem(simulateur, adresse+1), get_mem(simulateur, adresse+2), get_mem(simulateur, adresse+3));
	
	if(instruction == 0){
		strcpy(traduction, "NOP");
	}
	else{
		opcode = recup_opcode(instruction);
		if(opcode == 0){
			function = recup_function(instruction);
			if( instruction_exist( instruction_asm, get_nom_instr( instruction_asm, function ) ) == 1 ){
				instruction = instruction | 63;
				strcpy(traduction, instruction_asm[function].instr(simulateur, instruction_asm, instruction, error));
			}
			else{
				return "";
			}
		}
		else{
			if( instruction_exist( instruction_asm, get_nom_instr( instruction_asm, opcode+NB_MAX_OPCODE ) ) == 1 ){
				instruction = instruction << 6;
				instruction = instruction >> 6;
				strcpy(traduction, instruction_asm[opcode+NB_MAX_OPCODE].instr(simulateur, instruction_asm, instruction, error));
			}
			else{
				return "";
			}
		}
	}
	
	return traduction;
}

int coupe_mot(char ** mot, char * source){
	int i = 1;
	char *pointeur;
	char copie[256];
	char *sep = " ";
	
	strcpy(copie, source);
	pointeur = strtok(copie, sep);
	strcpy(mot[0], copie);
	
	while(pointeur != NULL && i<10){
		pointeur = strtok(NULL, sep);
		if ( pointeur != NULL ){
			strcpy(mot[i], pointeur);
		} 
		i++;
	}
	
	return 1;
}

int is_number(char * source){
	int i;
	char cpy[50];
	strcpy(cpy, source);
	
	if(strlen(cpy) != 0){
		if(source[0] == '0' && cpy[1] == 'x' && strlen(cpy) > 2){
			
			for(i=0; i<strlen(cpy)-2; i++){
				cpy[i] = cpy[i+2];
			}
			cpy[i] = '\0';
			
			for(i=0; i<strlen(cpy); i++){
				if(isxdigit(cpy[i]) == 0){
					return 0;
				}
			}
		}
		else{
			for(i=0; i<strlen(cpy); i++){
				if(isdigit(cpy[i]) == 0){
					return 0;
				}
			}
		}
	}
	else{
		return 0;
	}
	return 1;
}

int atohi(char * source){
	int i = 0;
	unsigned int val;
	char cpy[50];
	strcpy(cpy, source);
	
	if(is_number(cpy) == 1){
		if(cpy[0] == '0' && cpy[1] == 'x' && strlen(cpy) > 2){
			for(i=0; i<strlen(cpy)-2; i++){
				cpy[i] = cpy[i+2];
			}
			cpy[i] = '\0';
			sscanf(cpy, "%x", &val);
		}
		else{
			val = atoi(cpy);
		}
		
		return val;
	}
	else{
		return 0;
	}
}

int save_res(MIPS simulateur, INSTR * instruction_asm, char * entree_util){
	char mot0[50];
	char mot1[50];
	
	sscanf(entree_util, "%s%s", mot0, mot1);
	
	if(strcmp(util_sim[0], "dasm") == 0){
		save_dasm(simulateur, instruction_asm, mot1);
	}
	else if(strcmp(util_sim[0], "dreg") == 0){
		save_dreg(simulateur, instruction_asm, mot1);
	}
	else if(strcmp(util_sim[0], "dmem") == 0){
		save_dmem(simulateur, instruction_asm, mot1);
	}
	
	printf("\n  %s saved in \"%s\"\n", util_sim[0], mot1);
	
	entree_util[0] = '\0';
	
	printf("\n");
	BLUE
	printf("> ");
	scanf("%[^\n]s", entree_util);
	ENDCOLOR
}








