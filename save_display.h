#ifndef _SAVE_DISPLAY_H_
#define _SAVE_DISPLAY_H_

int save_dasm(MIPS simulateur, INSTR * instruction_asm, char * filename);
int save_dreg(MIPS simulateur, INSTR * instruction_asm, char * filename);
int save_dmem(MIPS simulateur, INSTR * instruction_asm, char * filename);


#endif
