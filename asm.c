#include "inc.h"
//#define DEBUG

int display_nom_instr(INSTR * instruction_asm){
	int i;
	for(i=0; i<NB_MAX_OPCODE; i++){
		if(instruction_asm[i].nom[0] != '\0'){
			printf("opcode: %02x (%02x) nom: %s\n", i, get_no_instr(instruction_asm, instruction_asm[i].nom), instruction_asm[i].nom);
		}
	}
	printf("\n");
	for(i=NB_MAX_OPCODE; i<2*NB_MAX_OPCODE; i++){
		if(instruction_asm[i].nom[0] != '\0'){
			printf("opcode: %02x (%02x) nom: %s\n", i-NB_MAX_OPCODE, get_no_instr(instruction_asm, instruction_asm[i].nom), instruction_asm[i].nom);
		}
	}
	return 1;
}

int charge_nom_instr(INSTR * instruction_asm){
	FILE * cfg;
	char type;
	char nom[15];
	int opcode;
	
	int i;
	char tmp[30];
	
	for(i=0; i<2*NB_MAX_OPCODE; i++){
		instruction_asm[i].nom[0] = '\0';
	}
	
	cfg = fopen("cfg_asm.txt", "r");

	while(feof(cfg) == 0){
		type = '0';
		nom[0] = '\0';
		opcode = 0;
		
		fscanf(cfg, "%c", &type);
		if(type == '/'){
			fscanf(cfg, "%[^\n]s", tmp);
			fscanf(cfg, "%c", &type);
			continue;
		}
		fscanf(cfg, "%s", nom);
		fscanf(cfg, "%x", &opcode);
		
		if(type == 'R'){
			strcpy(instruction_asm[opcode].nom, nom);
		}
		else if(type == 'I' || type == 'J'){
			strcpy(instruction_asm[opcode+NB_MAX_OPCODE].nom, nom);
		}
		else{
			fscanf(cfg, "%[^\n]s", tmp);
			fscanf(cfg, "%c", &type);
			continue;
		}
		
		fscanf(cfg, "%c", &type);
	}
	
	fclose(cfg);
	return 1;
}

char * get_nom_instr(INSTR * instr, int opcode){
	return instr[opcode].nom;
}

int get_no_instr(INSTR * instr, char * nom){
	int i;
	for(i=0; i<2*NB_MAX_OPCODE; i++){
		if(strcmp(instr[i].nom, nom) == 0){
			return i;
		}
	}
	
	return i+1;
}

int link_asm(INSTR * instruction_asm){
	
	instruction_asm[ get_no_instr(instruction_asm, "ADD") ].instr = ADD;
	instruction_asm[ get_no_instr(instruction_asm, "ADDU") ].instr = ADDU;
	instruction_asm[ get_no_instr(instruction_asm, "AND") ].instr = AND;
	instruction_asm[ get_no_instr(instruction_asm, "DIV") ].instr = DIV;

	instruction_asm[ get_no_instr(instruction_asm, "JR") ].instr = JR;
	instruction_asm[ get_no_instr(instruction_asm, "MFHI") ].instr = MFHI;
	instruction_asm[ get_no_instr(instruction_asm, "MFLO") ].instr = MFLO;
	instruction_asm[ get_no_instr(instruction_asm, "MULT") ].instr = MULT;
	instruction_asm[ get_no_instr(instruction_asm, "OR") ].instr = OR;
	instruction_asm[ get_no_instr(instruction_asm, "SLL") ].instr = SLL;
	instruction_asm[ get_no_instr(instruction_asm, "SLT") ].instr = SLT;
	instruction_asm[ get_no_instr(instruction_asm, "SRL") ].instr = SRL;
	instruction_asm[ get_no_instr(instruction_asm, "SUB") ].instr = SUB;
	instruction_asm[ get_no_instr(instruction_asm, "SYSCALL") ].instr = SYSCALL;
	
	instruction_asm[ get_no_instr(instruction_asm, "ADDI") ].instr = ADDI;
	instruction_asm[ get_no_instr(instruction_asm, "ADDIU") ].instr = ADDIU;
	instruction_asm[ get_no_instr(instruction_asm, "BEQ") ].instr = BEQ;
	instruction_asm[ get_no_instr(instruction_asm, "BGTZ") ].instr = BGTZ;
	instruction_asm[ get_no_instr(instruction_asm, "BLEZ") ].instr = BLEZ;
	instruction_asm[ get_no_instr(instruction_asm, "BNE") ].instr = BNE;
	instruction_asm[ get_no_instr(instruction_asm, "J") ].instr = J;
	instruction_asm[ get_no_instr(instruction_asm, "JAL") ].instr = JAL;
	instruction_asm[ get_no_instr(instruction_asm, "LB") ].instr = LB;
	instruction_asm[ get_no_instr(instruction_asm, "LBU") ].instr = LBU;
	instruction_asm[ get_no_instr(instruction_asm, "LUI") ].instr = LUI;
	instruction_asm[ get_no_instr(instruction_asm, "LW") ].instr = LW;
	instruction_asm[ get_no_instr(instruction_asm, "ORI") ].instr = ORI;
	instruction_asm[ get_no_instr(instruction_asm, "SB") ].instr = SB;
	instruction_asm[ get_no_instr(instruction_asm, "SW") ].instr = SW;
	instruction_asm[ get_no_instr(instruction_asm, "XOR") ].instr = XOR;
	
	return 1;
}

int instruction_exist(INSTR * instruction_asm, char * nom_instruction){
	int i;
	if(nom_instruction[0] == '\0'){
		return 0;
	}
	for(i=0; i<2*NB_MAX_OPCODE; i++){
		if(strcmp(instruction_asm[i].nom, nom_instruction) == 0){
			return 1;
		}
	}
	
	return 0;
}


