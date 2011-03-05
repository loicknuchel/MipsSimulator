#include "inc.h"
//#define DEBUG

FICHIER * init_file(){
	FICHIER * file = calloc(1, sizeof(FICHIER));
	
	strcpy((*file).nom, "");
	(*file).taille = 0;
	(*file).bss = 0;
	(*file).sizebss = 0;
	(*file).text = 0;
	(*file).sizetext = 0;
	(*file).data = 0;
	(*file).sizedata = 0;
	
	#ifdef DEBUG
		printf("FICHIER initialise\n\n");
	#endif
	
	return file;
}

int set_file(FICHIER * file, char * nom, int taille, int bss, int sizebss, int text, int sizetext, int data, int sizedata){
	#ifdef DEBUG
		printf("prev file : \"%s\". size:%d, bss:%d, text:%d, data:%d\n", (*file).nom, (*file).taille, (*file).bss, (*file).text, (*file).data);
		printf(" set_file : \"%s\". size:%d, bss:%d, text:%d, data:%d\n", nom, taille, bss, text, data);
	#endif
	
	if(strcmp(nom, "") != 0){
		strcpy((*file).nom, nom);
	}
	if(taille != -1){
		(*file).taille = taille;
	}
	if(bss != -1){
		(*file).bss = bss;
	}
	if(sizebss != -1){
		(*file).sizebss = sizebss;
	}
	if(text != -1){
		(*file).text = text;
	}
	if(sizetext != -1){
		(*file).sizetext = sizetext;
	}
	if(data != -1){
		(*file).data = data;
	}
	if(sizedata != -1){
		(*file).sizedata = sizedata;
	}
	
	#ifdef DEBUG
		printf(" new file : \"%s\". size:%d, bss:%d, text:%d, data:%d\n\n", (*file).nom, (*file).taille, (*file).bss, (*file).text, (*file).data);
	#endif
	
	return 1;
}

int display_file(FICHIER * file){
	printf("\n  ---- FILE ------------------\n");
	printf("  --\n");
	printf("  -- current file: \"%s\"\n", file->nom);
	printf("  -- size: 0x%x octetes utilises\n", file->taille);
	printf("  -- .text: 0x%x octets en 0x%x\n", file->sizetext,  file->text);
	printf("  -- .data: 0x%x octets en 0x%x\n", file->sizedata,  file->data);
	printf("  -- .bss: 0x%x octets\n", file->sizebss);
	printf("  ----------------------------\n");
	
	return 1;
}

int empty_file(FICHIER * file){
	strcpy((*file).nom, "");
	(*file).taille = 0;
	(*file).bss = 0;
	(*file).sizebss = 0;
	(*file).text = 0;
	(*file).sizetext = 0;
	(*file).data = 0;
	(*file).sizedata = 0;
	
	#ifdef DEBUG
		printf("file restarted :\n");
		printf(" new file : \"%s\". size:%d, bss:%d, text:%d, data:%d\n\n", (*file).nom, (*file).taille, (*file).bss, (*file).text, (*file).data);
	#endif
	
	return 1;
}

char * get_file_name(FICHIER * file){
	return file->nom;
}

int get_file_size(FICHIER * file){
	return file->taille;
}

int get_addr_data(FICHIER * file){
	return file->data;
}

int get_addr_text(FICHIER * file){
	return file->text;
}

int get_addr_bss(FICHIER * file){
	return file->bss;
}




