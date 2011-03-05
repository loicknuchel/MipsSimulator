#include "inc.h"
//#define DEBUG

REG * create_reg(){
	int i;
	
	REG * tab = calloc(32, sizeof(REG));
	
	strcpy(tab[0].nom, "$zero");
	strcpy(tab[1].nom, "$at");
	strcpy(tab[2].nom, "$v0");
	strcpy(tab[3].nom, "$v1");
	strcpy(tab[4].nom, "$a0");
	strcpy(tab[5].nom, "$a1");
	strcpy(tab[6].nom, "$a2");
	strcpy(tab[7].nom, "$a3");
	strcpy(tab[8].nom, "$t0");
	strcpy(tab[9].nom, "$t1");
	strcpy(tab[10].nom, "$t2");
	strcpy(tab[11].nom, "$t3");
	strcpy(tab[12].nom, "$t4");
	strcpy(tab[13].nom, "$t5");
	strcpy(tab[14].nom, "$t6");
	strcpy(tab[15].nom, "$t7");
	strcpy(tab[16].nom, "$s0");
	strcpy(tab[17].nom, "$s1");
	strcpy(tab[18].nom, "$s2");
	strcpy(tab[19].nom, "$s3");
	strcpy(tab[20].nom, "$s4");
	strcpy(tab[21].nom, "$s5");
	strcpy(tab[22].nom, "$s6");
	strcpy(tab[23].nom, "$s7");
	strcpy(tab[24].nom, "$t8");
	strcpy(tab[25].nom, "$t9");
	strcpy(tab[26].nom, "$k0");
	strcpy(tab[27].nom, "$k1");
	strcpy(tab[28].nom, "$gp");
	strcpy(tab[29].nom, "$sp");
	strcpy(tab[30].nom, "$fp");
	strcpy(tab[31].nom, "$ra");
	
	for(i=0; i<32; i++){
		tab[i].val = 0;
	}
	
	return tab;
}

int get_no_reg(REG * registres, char * nom){
	int i = 0;
	
	while(strcmp(registres[i].nom, nom) != 0 && i<32){
		i++;
	}
	
	return i;
}

char * get_nom_reg(REG * registres, int no_reg){
	return registres[no_reg].nom;
}

int get_reg(REG * registres, int no_reg){
	return registres[no_reg].val;
}

int set_reg(REG * registres, int no_reg, unsigned int val){
	registres[no_reg].val = val;
	return 1;
}





