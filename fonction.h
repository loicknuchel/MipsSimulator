#ifndef _FONCTION_H_
#define _FONCTION_H_


int execute_instruction(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, char * error);
char * traduit_instruction(MIPS simulateur, INSTR * instruction_asm, int adresse, char * error);
int coupe_mot(char ** mot, char * source);
int is_number(char * source);
int test(MIPS simulateur, BP * breakpoint);
int save_res(MIPS simulateur, INSTR * instruction_asm, char * entree_util);

#endif

















