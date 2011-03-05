/*--------------------------------------------------------------------------*/
/* PHELMA 2009/10 filières SICOM & SEI - Projet Informatique                */
/*                                                                          */
/* elfLoaderTest.c v1.1:                                                    */
/* exemple de programme qui ouvre un fichier au format Elf, extrait les     */
/* données contenues et les affiche à l'écran.                              */
/* Nb: vous devez auparavant avoir installé libelf et elfLoader             */
/*                                                                          */
/* contact: Matthieu.Chabanas@grenoble-inp.fr                               */
/*--------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include <elfLoader.h>


/*--------------------------------------------------------------------------*/
void printSection(char * name, unsigned int size, unsigned char *data)
{
	int i;
	int cr = 0;
	printf("Section: %s, %d octets\n", name, size);
	for (i=0; i<size; i++) {
		if (cr >= 16) { /* saut de ligne tous les 16 octets */
			printf("\n");
			cr = 0;
		}
		printf("%02x ", data[i]);
		cr = cr+1;;
	}
	printf("\n");
}

/*--------------------------------------------------------------------------*/
void printRelTable(char * name, unsigned int size, Elf32_Rel *relTable)
{
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

/*--------------------------------------------------------------------------*/
unsigned char * getSectionName(unsigned char **stringTable, Elf32_Sym *symbolTable, 
                      unsigned int size, unsigned int shndx)
{
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

/*--------------------------------------------------------------------------*/
void printSymbols(Elf32_Sym *symbolTable, unsigned char **stringTable, unsigned int size)
{
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



/*--------------------------------------------------------------------------*/
int main(int argc, char *argv[]) {
	char * filename = NULL;
	int i;

	unsigned char *textSection = NULL;
	unsigned char *dataSection = NULL;
	Elf32_Sym *symbolTable = NULL;
	unsigned char **stringTable = NULL;
	Elf32_Rel *relTextSection = NULL;
	Elf32_Rel *relDataSection = NULL;
	
	unsigned int textSectionSize = 0;
	unsigned int dataSectionSize = 0;
	unsigned int bssSectionSize = 0;
 	unsigned int symbolTableSize = 0;
 	unsigned int stringTableSize = 0;
	unsigned int relTextSectionSize = 0;
	unsigned int relDataSectionSize = 0;

	/* lecture du nom de programme donné en paramètre */
	/* Rappel: argc contient le nombre de "mots" dans la ligne de commande, 
	   et argv est un tableau de chaînes contenant ces "mots".	
	   Si vous tapez: elfLoaderTest test.o
	   alors argc == 2, argv[0] == "elfLoaderTest" (nom de la commande),
	   et argv[1] =="test.o" (1er paramètre). */
	if ((argc < 2) || (argc > 2)) {
		printf("Usage: %s <fichier_elf> \n", argv[0]);
		exit(1);
	}


	printf("Opening File %s...\n", argv[1]);
	filename = argv[1];
	
	/* Ouverture du fichier elf */	
	openElf(filename);
	
	/* lecture des sections .text and .data */
	getTextSection(&textSectionSize, &textSection);
	getDataSection(&dataSectionSize, &dataSection);
	getBssSection(&bssSectionSize);
	getSymbolTable(&symbolTableSize, &symbolTable);
	getStringTable(&stringTableSize, &stringTable);
	getTextRelocSection(&relTextSectionSize, &relTextSection);
	getDataRelocSection(&relDataSectionSize, &relDataSection);

	/* Print */
	printf("\n");
	printSection(".text", textSectionSize, textSection);
	printf("\n");
	printSection(".data", dataSectionSize, dataSection);
	printf("\n");
	printf("Section .bss: %d octets (tous nuls)\n", bssSectionSize);
	printf("\n");
 	printSymbols(symbolTable, stringTable, symbolTableSize);
	printf("\n");
	printRelTable(".rel.text", relTextSectionSize, relTextSection);
	printf("\n");
	printRelTable(".rel.data", relDataSectionSize, relDataSection);
	printf("\n");
	
	/* On ferme, et on fait le ménage... */
	closeElf();
	if (textSection)
		free(textSection);
	if (dataSection)
		free(dataSection);
	if (stringTable) {
		for (i=0; i<stringTableSize; i++)
			free(stringTable[i]);
		free(stringTable);
	}
/*	pas de copie profonde de ces tables (bof?), ne pas les liberer...
	if (symbolTable)
		free(symbolTable);
	if (relTextSection)
		free(relTextSection);
	if (relDataSection)
		free(relDataSection);*/
	
	printf("\nThat's all folks!\n");
	return 1;
}
