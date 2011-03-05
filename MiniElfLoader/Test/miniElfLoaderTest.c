/*--------------------------------------------------------------------------*/
/* PHELMA 2009/10 filières SICOM & SEI - Projet Informatique                */
/*                                                                          */
/* miniElfLoaderTest.c v1.1:                                                */
/* exemple de programme qui ouvre un fichier au format Elf, extrait les     */
/* données contenues et les affiche à l'écran.                              */
/* Nb: vous devez auparavant avoir installé libelf et miniElfLoader         */
/*                                                                          */
/* contact: Matthieu.Chabanas@grenoble-inp.fr                               */
/*--------------------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include "miniElfLoader.h"


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
int main(int argc, char *argv[]) {
	char * filename = NULL;
	
	unsigned char *textSection = NULL;
	unsigned char *dataSection = NULL;
	unsigned int textSectionSize = 0;
	unsigned int dataSectionSize = 0;


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

	/* Print */
	printSection(".text", textSectionSize, textSection);
	printSection(".data", dataSectionSize, dataSection);
	
	/* On ferme, et on fait le ménage... */
	closeElf();
	if (textSection)
		free(textSection);
	if (dataSection)
		free(dataSection);
	
	printf("That's all folks!\n");
	return 1;
}
