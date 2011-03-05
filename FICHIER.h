#ifndef _FICHIER_H_
#define _FICHIER_H_

typedef struct _FICHIER{
	char nom[FILE_NAME_MAX_SIZE];
	int taille;
	int bss;
	int sizebss;
	int text;
	int sizetext;
	int data;
	int sizedata;
} FICHIER;

//int init_file(FICHIER * file);
FICHIER * init_file();
int set_file(FICHIER * file, char * nom, int taille, int bss, int sizebss, int text, int sizetext, int data, int sizedata); /*mettre la chaine vide ou -1 aux int pour ne pas les changer*/
int display_file(FICHIER * file);
int empty_file(FICHIER * file);
char * get_file_name(FICHIER * file);
int get_file_size(FICHIER * file);
int get_addr_data(FICHIER * file);
int get_addr_text(FICHIER * file);
int get_addr_bss(FICHIER * file);


#endif
