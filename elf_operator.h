#ifndef _ELF_OPERATOR_H_
#define _ELF_OPERATOR_H_

int loadSection(MIPS simulateur, unsigned int addr, unsigned int size, unsigned char *Section);
void printSection(char * name, unsigned int size, unsigned char *data);


#endif

