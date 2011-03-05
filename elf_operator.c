#include "inc.h"
//#define DEBUG

int loadSection(MIPS simulateur, unsigned int addr, unsigned int size, unsigned char *Section){
	int i;
	for (i=0; i<size; i++) {
		mem_sim[addr+i] = Section[i];
	}
	return i;
	
}

int loadSectionReloc(MIPS simulateur, unsigned int textaddr, unsigned int dataaddr, unsigned int addr_section, unsigned int size, unsigned char *Section, Elf32_Rel *relTable){
	int i = 0;
	int j = 0;
	int rel = 0;
	unsigned int instr32, instr32LO, A, P, S, modif, AHL, AHI, ALO;
	Elf32_Rel entry;
	
	if(relTable != NULL){
		entry = relTable[j];
		rel = 1;
	}
	
	for (i=0; i<size; i=i+4) {
		if(entry.r_offset == i && rel == 1){
			
			
			instr32 = assemble_mot(Section[i], Section[i+1], Section[i+2], Section[i+3]);
			
			if(ELF32_R_SYM(entry.r_info) == 1){
				S = textaddr;
			}
			else if(ELF32_R_SYM(entry.r_info) == 2){
				S = dataaddr;
			}
			
			P = i; /*adresse de l'instruction a reloger*/
			if(ELF32_R_TYPE(entry.r_info) == 2){
				A = instr32;
				instr32 = A + S;
				mem_sim[addr_section+i] = recup_octet_mot(instr32, 1);
				mem_sim[addr_section+i+1] = recup_octet_mot(instr32, 2);
				mem_sim[addr_section+i+2] = recup_octet_mot(instr32, 3);
				mem_sim[addr_section+i+3] = recup_octet_mot(instr32, 4);
			}
			else if(ELF32_R_TYPE(entry.r_info) == 4){
				A = (instr32 << 6) >> 6;
				modif = (((A<<2) | (P & 0xF0000000)) + S) >> 2;
				instr32 = ((instr32 >> 26) << 26) + modif;
				mem_sim[addr_section+i] = recup_octet_mot(instr32, 1);
				mem_sim[addr_section+i+1] = recup_octet_mot(instr32, 2);
				mem_sim[addr_section+i+2] = recup_octet_mot(instr32, 3);
				mem_sim[addr_section+i+3] = recup_octet_mot(instr32, 4);
			}
			else if(ELF32_R_TYPE(entry.r_info) == 5){
				AHI = (instr32 << 16) >> 16;
				instr32LO = assemble_mot(Section[i+4], Section[i+5], Section[i+6], Section[i+7]);
				ALO = (instr32LO << 16) >> 16;
				AHL = ((AHI<<16) + (short)ALO);
				
				instr32 = (instr32 >> 16) << 16;
				instr32LO = (instr32LO >> 16) << 16;
				
				instr32 = instr32 + ((AHL + S) >> 16);
				instr32LO = instr32LO + (((AHL + S) << 16 ) >> 16);
				
				mem_sim[addr_section+i] = recup_octet_mot(instr32, 1);
				mem_sim[addr_section+i+1] = recup_octet_mot(instr32, 2);
				mem_sim[addr_section+i+2] = recup_octet_mot(instr32, 3);
				mem_sim[addr_section+i+3] = recup_octet_mot(instr32, 4);
				mem_sim[addr_section+i+4] = recup_octet_mot(instr32LO, 1);
				mem_sim[addr_section+i+5] = recup_octet_mot(instr32LO, 2);
				mem_sim[addr_section+i+6] = recup_octet_mot(instr32LO, 3);
				mem_sim[addr_section+i+7] = recup_octet_mot(instr32LO, 4);
				
			}
			
			#ifdef DEBUG
				printf("%d) ", ELF32_R_TYPE(entry.r_info));
				printf("%02x %02x %02x %02x <= %02x %02x %02x %02x\n", mem_sim[addr_section+i], mem_sim[addr_section+i+1], mem_sim[addr_section+i+2], mem_sim[addr_section+i+3], Section[i], Section[i+1], Section[i+2], Section[i+3]);
				if(ELF32_R_TYPE(entry.r_info) == 5){
					printf("6) %02x %02x %02x %02x <= %02x %02x %02x %02x\n", mem_sim[addr_section+i+4], mem_sim[addr_section+i+5], mem_sim[addr_section+i+6], mem_sim[addr_section+i+7], Section[i+4], Section[i+5], Section[i+6], Section[i+7]);
				}
			#endif
			if(ELF32_R_TYPE(entry.r_info) == 5){
				i = i + 4;
				j++;
			}
			
			j++;
			entry = relTable[j];
		}
		else{
			mem_sim[addr_section+i] = Section[i];
			mem_sim[addr_section+i+1] = Section[i+1];
			mem_sim[addr_section+i+2] = Section[i+2];
			mem_sim[addr_section+i+3] = Section[i+3];
			#ifdef DEBUG
				printf("   %02x %02x %02x %02x\n", mem_sim[addr_section+i], mem_sim[addr_section+i+1], mem_sim[addr_section+i+2], mem_sim[addr_section+i+3]);
			#endif
		}
	}
	
	return i;
}

unsigned char * getSectionName(unsigned char **stringTable, Elf32_Sym *symbolTable, unsigned int size, unsigned int shndx){
	/* On cherche parmi les sections celle dont l'index est shndx */
	int i=0;
	while (i<size) {
		if ((ELF32_ST_TYPE(symbolTable[i].st_info) == 3) && (shndx == symbolTable[i].st_shndx)) {
			return stringTable[i];
		}
		else
			i++;
	}
	return stringTable[0];	/* chaine vide "" ('\0') */
}

void printSection(char * name, unsigned int size, unsigned char *data){
	int i;
	int cr = 0;
	printf("Section: %s, %d octets\n", name, size);
	for (i=0; i<size; i++) {
		if (cr >= 4) { /* saut de ligne tous les 4 octets */
			printf("\n");
			cr = 0;
		}
		printf("%02x ", data[i]);
		cr = cr+1;;
	}
	printf("\n");
}

void printRelTable(char * name, unsigned int size, Elf32_Rel *relTable){
	Elf32_Rel entry;
	int i;
	printf("Section: %s, %d entrees\n", name, size);
	printf("  Offset      Info         Type\n");
	for (i=0; i<size; i++) {
		entry = relTable[i];
		printf("%08x  %08x  ", entry.r_offset, entry.r_info);
		switch (ELF32_R_TYPE(entry.r_info)) {
			case R_MIPS_32:
				printf("  R_MIPS_32  ");
				break;
			case R_MIPS_26:
				printf("  R_MIPS_26  ");
				break;
			case R_MIPS_HI16:
				printf("R_MIPS_HI16  ");
				break;
			case R_MIPS_LO16:
				printf("R_MIPS_LO16  ");
				break;
			default:
				printf("    UNKNOWN  ");
		}
		printf("\n");
	}
}

void printSymbols(Elf32_Sym *symbolTable, unsigned char **stringTable, unsigned int size){
	int i;
	Elf32_Sym sym;
	
	printf("Table des symboles: %d symboles\n", size);
	/* Affichage de tous les champs un a un */
/*	for (i=0; i<size; i++) {
		sym = data[i];
		printf("num %d; name %d; value %x; size %d, bind %hhd, type %hhd, other %hhd, shndx %d\n",
			i, sym.st_name, sym.st_value, sym.st_size, ELF32_ST_BIND(sym.st_info),
			ELF32_ST_TYPE(sym.st_info), sym.st_other, sym.st_shndx);		
	}*/
		
	/* Affichage formatte a la "readelf -s" */
	printf("   Num:    Value Type     Bind    Ndx Name\n");
	for (i=0; i<size; i++) {
		sym = symbolTable[i];
		printf("%6d: %08x ", i, sym.st_value);
		switch (ELF32_ST_TYPE(sym.st_info)) {
			case 0:
				printf("NOTYPE   ");
				break;
			case 3:
				printf("SECTION  ");
				break;
			default:
				printf("UNKNOWN  ");
		}
		
		switch (ELF32_ST_BIND(sym.st_info)) {
			case 0:
				printf("LOCAL ");
				break;
			case 1:
				printf("GLOBAL");
				break;
			default:
				printf("UNKNOWN");
		}
		printf("  %3d", sym.st_shndx);
		
		printf("  %s", stringTable[i]);
		
		printf("\n");
	}
	printf("\nPour ne garder que les symboles definis localement (hors\n");
	printf("sections), il suffit de ne garder que ceux de num>0 dont\n");
	printf("le type est NOTYPE:\n");

	printf("   Symbole   Section de definition    Offset\n");
	for (i=1; i<size; i++) {
		sym = symbolTable[i];
		if (ELF32_ST_TYPE(sym.st_info) == 0) {
			printf("%10s", stringTable[i]);
 			printf("  %5s", getSectionName(stringTable, symbolTable, size, sym.st_shndx));
			printf("               ");
			printf("%8x\n", sym.st_value);
		}
	}
}



