#ifndef _LIB_SHELL_H_
#define _LIB_SHELL_H_

//char ** entree_util
int s_load(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide);
int s_clear(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide);
int s_dasm(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide);
int s_dreg(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide);
int s_sreg(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide);
int s_dmem(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide);
int s_smem(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide);
int s_run(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide);
int s_step(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide);
int s_stepi(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide);
int s_addbp(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide);
int s_rmbp(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide);
int s_dbp(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide);
int s_help(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide);
int s_exit(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide);

int s_dfile(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide);
int s_smems(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide);
int s_dmemnn(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide);
int s_dmips(MIPS simulateur, BP * breakpoint, INSTR * instruction_asm, HELP aide);




#endif

