#include "inc.h"
//#define DEBUG

unsigned int assemble_mot(OCTET O1, OCTET O2, OCTET O3, OCTET O4){
	unsigned int res;
	res = (O1 << 24) | (O2 << 16) | (O3 << 8) | O4;
	return res;
}

OCTET recup_octet_mot(unsigned int source, int numero){
	OCTET cible;
	cible = (source >> (4-numero)*8) & 255;
	return cible;
}

int recup_bit(unsigned char source, int no_bit){
	return (source >> no_bit) & 1;
}


int recup_bit_int(unsigned int source, int no_bit){
	return (source >> no_bit) & 1;
}	

char * print_oct_bin(OCTET octet){
	int i;
	int tab[8];
	char * oct;
	oct = calloc(10, sizeof(char));
	
	for(i=0; i<8; i++){
		tab[i] = recup_bit(octet, 7-i);
		sprintf(oct, "%s%d", oct, tab[i]);
	}
	
	return oct;
}

char * print_int_bin(unsigned int octet){
	int i;
	int tab[32];
	char * oct;
	oct = calloc(33, sizeof(char));
	
	for(i=0; i<32; i++){
		tab[i] = recup_bit_int(octet, 31-i);
		sprintf(oct, "%s%d", oct, tab[i]);
	}
	
	return oct;
}

unsigned int recup_opcode(unsigned int source){
	unsigned int res;
	res = source >> 26;
	return res;
}

unsigned int recup_rs(unsigned int source){
	unsigned int res;
	res = (source >> 21) & 31;
	return res;
}

unsigned int recup_rt(unsigned int source){
	unsigned int res;
	res = (source >> 16) & 31;
	return res;
}

unsigned int recup_rd(unsigned int source){
	unsigned int res;
	res = (source >> 11) & 31;
	return res;
}

unsigned int recup_sa(unsigned int source){
	unsigned int res;
	res = (source >> 6) & 31;
	return res;
}

unsigned int recup_function(unsigned int source){
	unsigned int res;
	res = source & 63;
	return res;
}

unsigned int recup_immediate(unsigned int source){
	return ((source << 16) >> 16);
}

int recup_immediate_signed(int source){
	return ((source << 16) >> 16);
}

unsigned int recup_instr_index(unsigned int source){
	unsigned int res;
	res = source & 67108863;
	return res;
}




