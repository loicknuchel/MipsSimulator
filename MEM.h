#ifndef _MEM_H_
#define _MEM_H_
#include "ASM.h"

OCTET * create_mem(MIPS simulateur);
int set_mem(MIPS simulateur, int adresse, OCTET val);
OCTET get_mem(MIPS simulateur, int adresse);
int cpy_mem(MIPS simulateur, int source, int cible);
int display4_mem(MIPS simulateur, INSTR * instruction_asm, int debut, int fin);
int display16_mem(MIPS simulateur, INSTR * instruction_asm, int debut, int fin);
int display_mem_not_null(MIPS simulateur, INSTR * instruction_asm, int debut, int fin);


#endif







