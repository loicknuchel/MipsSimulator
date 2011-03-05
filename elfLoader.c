/*--------------------------------------------------------------------------*/
/* Phelma 2009/10 - Projet Informatique                                     */
/*                                                                          */
/* elfLoader.c :                                                            */
/* Ouverture et recuperation des sections .text et .data dans un fichier    */
/* au format Elf, architecture MIPS.                                        */
/*                                                                          */
/* VOUS N'AVEZ PAS BESOIN DE COMPRENDRE TOUT CA!!!!                         */
/* Voir elfLoaderTest.s pour un exemple d'utilisation.                      */
/* Nb: vous devez auparavant avoir installe libelf                          */
/*--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>

#include "elfLoader.h"


/* Private*/
static Elf *elf = NULL;
static void throwError(const char *fmt, ...);


/*------------------------------------------------------------------------*/
/*          PRIVATE FUNCTIONS - defined locally only                      */
/*------------------------------------------------------------------------*/
static int getSectionInfos(Elf *elf, const char *sectionName, 
	Elf_Scn **section, Elf_Data **sectionData, GElf_Shdr **sectionHeader);

static int getSection(Elf *elf, const char *sectionName, unsigned int * size,
	unsigned char ** data);

static void getRelocSection(unsigned int * size, Elf32_Rel ** data, char * name);


/*------------------------------------------------------------------------*/
/*          PUBLIC FUNCTIONS                                              */
/*------------------------------------------------------------------------*/

void openElf(char * filename)
{
	long fd ;
	/* Lecture du fichier ELF */  
	if ((fd = open(filename, O_RDONLY)) == -1) {
		throwError("Unable to open (ELF) file", filename);
	}

	elf_version(EV_CURRENT);
	if ((elf = elf_begin(fd, ELF_C_READ, NULL)) == NULL) {
		throwError("Unable to read ELF file", filename);
	}
}

void getTextSection(unsigned int * size, unsigned char ** data)
{
	getSection(elf, ".text", size, data);
}

void getDataSection(unsigned int * size, unsigned char ** data)
{
	getSection(elf, ".data", size, data);
}


void getBssSection(unsigned int * size)
{
	Elf_Scn *scn = NULL;        /* Section */
	Elf_Data *scnData = NULL;   /* Section data */
	GElf_Shdr *shdr = NULL;     /* Elf section header table entry */
	
	if (getSectionInfos(elf, ".bss", &scn, &scnData, &shdr) == 0) {
		/* Section not found, no bytes... */
		*size = 0;
	} 
	else {
		*size = scnData->d_size;
	}
}

void getStringTable(unsigned int * size, unsigned char *** data)
{
	Elf_Scn *scn = NULL;        /* Section */
	Elf_Data *scnData = NULL;   /* Section data */
	GElf_Shdr *shdr = NULL;     /* Elf section header table entry */
	int i, nbC, offset, n;
	char c;
	
	if (getSectionInfos(elf, ".strtab", &scn, &scnData, &shdr) == 0) {
		/* No string table found */
		*size = 0;
		*data = NULL;
	}
	else {
		/* affichage de la table des symboles octet par octet *
		for (i=0; i<scnData->d_size; i++) {
			c = *(char *) (scnData->d_buf+i);
			printf("%c ", c);
		}
		printf("\n"); */
		
		/* Un premier parcours pour determiner le nb de chaines */
		nbC = 0;
		for (i=0; i<scnData->d_size; i++) {
			c = *(char *) (scnData->d_buf+i);
			if (c == '\0')
				nbC++;
		}
		*size = nbC;
		*data = (unsigned char **) calloc(nbC, sizeof(unsigned char*));
		
		/* second parcours pour creer les chaines */
		(*data)[0] = (unsigned char *) calloc(1, sizeof(unsigned char));
		(*data)[0][0] = '\0';	/* chaine vide, sentinelle */
		offset = 1;
		for (i=1; i<nbC; i++) {
			n = strlen(scnData->d_buf+offset);
			(*data)[i] = (unsigned char *) calloc(n, sizeof(unsigned char));
			strcpy((char *)((*data)[i]), scnData->d_buf+offset);
			offset += n+1;	/* taille chaine + le '\0' */			
/*			printf("%s\n", (*data)[i]); */
		}
	}
}

void getSymbolTable(unsigned int * size, Elf32_Sym ** data)
{
	Elf_Scn *scn = NULL;        /* Section */
	Elf_Data *scnData = NULL;   /* Section data */
	GElf_Shdr *shdr = NULL;     /* Elf section header table entry */
	
	if (getSectionInfos(elf, ".symtab", &scn, &scnData, &shdr) == 0) {
		/* No symbol table found */
		*size = 0;
		*data = NULL;
	}
	else {
		*size = scnData->d_size / shdr->sh_entsize;
		*data = (Elf32_Sym *) (scnData->d_buf + scnData->d_off);
	}
}

void getTextRelocSection(unsigned int * size, Elf32_Rel ** data)
{
	getRelocSection(size, data, ".rel.text");
}

void getDataRelocSection(unsigned int * size, Elf32_Rel ** data)
{
	getRelocSection(size, data, ".rel.data");	
}

void closeElf()
{
	if (elf == NULL) {
		throwError("closeElf: createElf must have been called first") ;
	}
	elf_end(elf);
}







/*--------------------------------------------------------------------------*/
/*          PRIVATE FUNCTIONS - defined locally only                        */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Cherche une section dans le fichier.
 Si elle est trouvee retourne son scn et data */
int getSectionInfos(Elf *e, const char *sectionName, Elf_Scn **section, 
		Elf_Data **sectionData, GElf_Shdr **sectionHeader)
{
	Elf_Scn *scn = NULL;		/* Section */
	Elf_Data *scnData = NULL;	/* Section data */
	GElf_Shdr *shdr = NULL;		/* Elf section header table entry */
	size_t shstrndx;		/* Elf section string index */
	char *sname = NULL;		/* Elf section name */
	

	/* Init: section and data are null by default (nothing found) */	
	*section = NULL;
	*sectionData = NULL;	
	*sectionHeader = NULL;
	
	/* Browse the file looking for the section... */	
	if (elf_getshstrndx(e, &shstrndx) == 0) {
		throwError("getshstrndx failed", NULL);
	}
	while ((scn = elf_nextscn(e, scn)) != NULL) {
		shdr = (GElf_Shdr *) malloc(sizeof(GElf_Shdr));
		if (gelf_getshdr(scn, shdr) != shdr) {
			throwError("getshdr failed", NULL);
			return 0;
		}
		
		if ((sname = elf_strptr(e, shstrndx, shdr->sh_name)) == NULL) {
			throwError("strptr failed", NULL);
			return 0;
		}
		
		if (strcmp(sname, sectionName) == 0) {
			/* Yep, we've found the rigth section! */
			break;
		}
	}

	if (scn == NULL) {
		/* section not found. Bye bye... */
		return 0;
	}

	/* Ok, register the section address */
	*section = scn;
	*sectionHeader = shdr;

	/* Is there any data in this section? */
	if (((scnData = elf_getdata(scn, NULL)) != NULL) && (scnData->d_size != 0)) {
		/* Ok, register the section data address */
		*sectionData = scnData;
	}
	else
		return 0;
	
	/* Everything went fine */
	return 1;
}




/*--------------------------------------------------------------------------*/
int getSection(Elf *e, const char *sectionName, 
			   unsigned int * size, unsigned char ** data) {
	Elf_Scn *scn = NULL;          /* Elf section */
	Elf_Data *scnData = NULL;     /* Elf section data */
	GElf_Shdr *shdr = NULL;       /* Elf header table entry */

	unsigned int n;
	char *p;


	if (e == NULL) {
		throwError("An elf file must be opened first using: openElf()");
	}

	/*-------------------------------------------- Part I: Get the bytes ---*/
	/* Browse the file looking for the section... */	
	if (getSectionInfos(e, sectionName, &scn, &scnData, &shdr) == 0) {
		/* Section not found, get back home. Return 0 (no bytes found). */
		return 0;
	}

	/*-------------------------------------------- Part II: Get the data ---*/
	/* Good, we can then hard-copy everything. */
	/* Number of bytes */
	*size = scnData->d_size;
	/* Bytes array */
	*data = (unsigned char *) malloc (sizeof(unsigned char)*scnData->d_size);
	n = 0;
	p = (char *) scnData->d_buf;	/* data buffer */
	while (p < (char *) scnData->d_buf + scnData->d_size) {
		(*data)[n] = (unsigned char) *p;
		p++; n++;
	}
	return *size;
}


/*--------------------------------------------------------------------------*/
void getRelocSection(unsigned int * size, Elf32_Rel ** data, char * name)
{
	Elf_Scn *scn = NULL;        /* Section */
	Elf_Data *scnData = NULL;   /* Section data */
	GElf_Shdr *shdr = NULL;     /* Elf section header table entry */
	
	if (getSectionInfos(elf, name, &scn, &scnData, &shdr) == 0) {
		/* Section not found, no bytes... */
		*size = 0;
		*data = NULL;
	} 
	else {
		*size = scnData->d_size  / shdr->sh_entsize;;
		*data = (Elf32_Rel *) (scnData->d_buf + scnData->d_off);
	}	
}

/*--------------------------------------------------------------------------*/
/* Print an error msg to stderr, and stop the execution */
void throwError(const char *fmt, ...)
{
	va_list args;
	fprintf (stderr, "ERROR ");
	va_start(args,fmt);
	vfprintf (stderr, fmt, args);
	va_end(args);
	fprintf(stderr,"\n");
	exit(2);
}


