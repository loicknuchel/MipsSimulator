#include "inc.h"
//#define DEBUG

MIPS create_mips(){
	MIPS simulateur;
	int i;
	
	reg_sim = create_reg();
	mem_size_sim = MEM_SIZE;
	mem_sim = create_mem(simulateur);
	bp_sim = create_bp();
	bp_sim = add_bp(bp_sim, MEM_SIZE, 3);
	file_sim = init_file();
	pc_sim = calloc(1, sizeof(REG));
	strcpy(simulateur.PC->nom, "PC");
	pc_sim->val = 0;
	hi_sim = calloc(1, sizeof(REG));
	strcpy(hi_sim->nom, "HI");
	hi_sim->val = 0;
	lo_sim = calloc(1, sizeof(REG));
	strcpy(lo_sim->nom, "LO");
	lo_sim->val = 0;
	util_sim = calloc(NB_ENTREE_UTIL, sizeof(char *));
	for(i=0; i<NB_ENTREE_UTIL; i++){
		util_sim[i] = calloc(SIZE_MOT_UTIL, sizeof(char));
		util_sim[i][0] = '\0';
	}
	
	return simulateur;
}

unsigned int get_pc(MIPS simulateur){
	  return pc_sim->val;
}

unsigned int get_hi(MIPS simulateur){
	  return hi_sim->val;
}

unsigned int get_lo(MIPS simulateur){
	  return lo_sim->val;
}

int set_pc(MIPS simulateur, unsigned int val){
	if(val < file_sim->text || val > file_sim->text + file_sim->sizetext){
		RED
		printf("\n  execution Adress uncorrect\n");
		ENDCOLOR
		return 2;
	}
	else{
		if(val%4 != 0){
			RED
			printf("\n  Unaligned Memory\n");
			ENDCOLOR
		}
		val = 4*(val/4);
		pc_sim->val = val;
	}
	
	 return 1;
}

int set_hi(MIPS simulateur, unsigned int val){
	 hi_sim->val = val;
	 return 1;
}

int set_lo(MIPS simulateur, unsigned int val){
	 lo_sim->val = val;
	 return 1;
}

void affiche_mips(MIPS simulateur, INSTR * instruction_asm){
	int i;
	int j;
	
	display16_mem(simulateur, instruction_asm, 0, 96);
	display_reg(simulateur);
	display_bp(bp_sim, 10);
	display_file(file_sim);
	printf("\n  ---- MEMOIRE ---- from 0x%x to 0x%x -------------------------------------\n");
	printf("  --\n");
	printf("  -- mem_size: 0x%x\n", mem_size_sim);
	printf("  ------------------------------------------------------------------\n");
}

int display_reg_col(MIPS simulateur){
	int i;
	
	printf("\n  ---- REGISTRES ----------------------------------------------\n");
	printf("  --\n");

	for(i=0; i<32; i++){
		printf("  -- %02d %s 0x%x\n", i, reg_sim[i].nom, reg_sim[i].val);
	}	

	printf("  --\n  -- speciaux: %s:0x%x, %s:0x%x, %s:0x%x\n", pc_sim->nom, pc_sim->val, hi_sim->nom, hi_sim->val, lo_sim->nom, lo_sim->val);
	printf("  ------------------------------------------------------------\n");
	
	return 1;
}

int display_reg_line(MIPS simulateur){
	int i;
	
	printf("\n  ---- REGISTRES ----------------------------------------------\n");
	printf("  --\n");
	
	
	printf("  --     0x%02x      ", 0);
	for(i=1; i<8; i++){
		printf("  0x%02x      ", i);
	}
	printf("\n  --     %s       ", reg_sim[0].nom);
	for(i=1; i<8; i++){
		printf(" %s        ", reg_sim[i].nom);	
	}
	printf("\n  --  0x%08x ", reg_sim[0].val);
	for(i=1; i<8; i++){
		printf(" 0x%08x ", reg_sim[i].val);
	}
	printf("\n  --\n");
	
	
	printf("  --     0x%02x      ", 8);
	for(i=9; i<16; i++){
		printf("  0x%02x      ", i);
	}
	printf("\n  --      %s        ", reg_sim[8].nom);
	for(i=9; i<16; i++){
		printf(" %s        ", reg_sim[i].nom);	
	}
	printf("\n  --  0x%08x ", reg_sim[8].val);
	for(i=9; i<16; i++){
		printf(" 0x%08x ", reg_sim[i].val);
	}
	printf("\n  --\n");
	
	
	printf("  --     0x%02x      ", 16);
	for(i=17; i<24; i++){
		printf("  0x%02x      ", i);
	}
	printf("\n  --      %s        ", reg_sim[16].nom);
	for(i=17; i<24; i++){
		printf(" %s        ", reg_sim[i].nom);	
	}
	printf("\n  --  0x%08x ", reg_sim[16].val);
	for(i=17; i<24; i++){
		printf(" 0x%08x ", reg_sim[i].val);
	}
	printf("\n  --\n");
	
	
	printf("  --     0x%02x      ", 24);
	for(i=25; i<32; i++){
		printf("  0x%02x      ", i);
	}
	printf("\n  --      %s        ", reg_sim[24].nom);
	for(i=25; i<32; i++){
		printf(" %s        ", reg_sim[i].nom);	
	}
	printf("\n  --  0x%08x ", reg_sim[24].val);
	for(i=25; i<32; i++){
		printf(" 0x%08x ", reg_sim[i].val);
	}	
	printf("\n  --\n");
	

	printf("  --\n  -- speciaux: %s:0x%x, %s:0x%x, %s:0x%x\n", pc_sim->nom, pc_sim->val, hi_sim->nom, hi_sim->val, lo_sim->nom, lo_sim->val);
	printf("  ------------------------------------------------------------\n");
	
	return 1;
}

int display_reg_spe(MIPS simulateur){
	int i;
	
	printf("\n  ---- REGISTRES ----------------------------------------------\n");
	printf("  --\n");
	printf("  -- 00 %s 0x%08x\n", reg_sim[0].nom, reg_sim[0].val);
	printf("  -- 01 %s 0x%08x\n", reg_sim[1].nom, reg_sim[1].val);
	printf("  -- 02 %s 0x%08x  03 %s 0x%08x\n", reg_sim[2].nom, reg_sim[2].val, reg_sim[3].nom, reg_sim[3].val);
	printf("  -- 04 %s 0x%08x  05 %s 0x%08x  06 %s 0x%08x  07 %s 0x%08x\n", reg_sim[4].nom, reg_sim[4].val, reg_sim[5].nom, reg_sim[5].val, reg_sim[6].nom, reg_sim[6].val, reg_sim[7].nom, reg_sim[7].val);


	printf("  --\n  -- speciaux: %s:0x%x, %s:0x%x, %s:0x%x\n", pc_sim->nom, pc_sim->val, hi_sim->nom, hi_sim->val, lo_sim->nom, lo_sim->val);
	printf("  ------------------------------------------------------------\n");
	
	return 1;
}

int display_reg(MIPS simulateur){
	return display_reg_line(simulateur);
}


