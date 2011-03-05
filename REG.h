#ifndef _REG_H_
#define _REG_H_

typedef struct _REG{
	char nom[MAX_NOM_REG];
	unsigned int val;
} REG;

REG * create_reg();
int get_no_reg(REG * registres, char * nom);
char * get_nom_reg(REG * registres, int no_reg);
int get_reg(REG * registres, int no_reg);
int set_reg(REG * registres, int no_reg, unsigned int val);

//BIT get_bit_reg(REG * registres, int no_reg, int no_bit);
//int set_bit_reg(REG * registres, int no_reg, int no_bit, BIT val);

#endif


