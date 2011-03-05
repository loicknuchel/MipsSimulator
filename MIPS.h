#ifndef _MIPS_H_
#define _MIPS_H_

typedef struct _MIPS {
        REG * registres;
        REG * PC;
        REG * HI;
        REG * LO;
        int mem_size;
        OCTET * memoire;
        BP breakpoint;
        FICHIER * file;
        char ** entree_utilisateur;
} MIPS;


typedef struct _INSTR{
	char nom[MAX_NOM_INSTR];
	char * (*instr)(MIPS, struct _INSTR *, int, char *);
} INSTR;


MIPS create_mips();
void affiche_mips(MIPS simulateur, INSTR * instruction_asm);
unsigned int get_pc(MIPS simulateur);
unsigned int get_hi(MIPS simulateur);
unsigned int get_lo(MIPS simulateur);
int set_pc(MIPS simulateur, unsigned int val);
int set_hi(MIPS simulateur, unsigned int val);
int set_lo(MIPS simulateur, unsigned int val);
int display_reg_col(MIPS simulateur);
int display_reg_line(MIPS simulateur);
int display_reg_spe(MIPS simulateur);
int display_reg(MIPS simulateur);

int display_nom_instr(INSTR * instruction_asm);
int charge_nom_instr(INSTR * instruction_asm);
int get_no_instr(INSTR * instruction_asm, char * nom);
char * get_nom_instr(INSTR * instruction_asm, int opcode);
int link_asm(INSTR * instruction_asm);
int instruction_exist(INSTR * instruction_asm, char * nom_instruction);
#endif


