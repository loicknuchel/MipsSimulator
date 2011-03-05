#ifndef _BINARY_OPERATOR_H_
#define _BINARY_OPERATOR_H_

unsigned int recup_opcode(unsigned int source);
unsigned int recup_rs(unsigned int source);
unsigned int recup_rt(unsigned int source);
unsigned int recup_rd(unsigned int source);
unsigned int recup_sa(unsigned int source);
unsigned int recup_function(unsigned int source);
unsigned int recup_immediate(unsigned int source);
int recup_immediate_signed(int source);
unsigned int recup_instr_index(unsigned int source);

unsigned int assemble_mot(OCTET O1, OCTET O2, OCTET O3, OCTET O4);
OCTET recup_octet_mot(unsigned int source, int numero);
int recup_bit(OCTET source, int no_bit);
int recup_bit_int(unsigned int source, int no_bit);
char * print_oct_bin(OCTET octet);
char * print_int_bin(unsigned int octet);

#endif


