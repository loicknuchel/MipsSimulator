#ifndef _LIB_ASM_H_
#define _LIB_ASM_H_


char * ADD(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * ADDI(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * ADDIU(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * ADDU(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * AND(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
//B
char * BEQ(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * BGTZ(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * BLEZ(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * BNE(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * DIV(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * J(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * JAL(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * JR(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * LB(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * LBU(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * LUI(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * LW(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * MFHI(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * MFLO(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * MULT(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * OR(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * ORI(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * SB(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * SLL(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * SLT(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * SRL(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * SUB(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * SW(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * SYSCALL(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);
char * XOR(MIPS simulateur, INSTR * instruction_asm, int instr32, char * error);





#endif

