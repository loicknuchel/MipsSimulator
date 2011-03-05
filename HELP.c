#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_help.h"
//#define DEBUG

HELP create_help(){
	return NULL;
}

HELP add_help(HELP aide, char * commande, char * proto, char * short_desc, char * long_desc){
	HELP new_HELP = calloc(1,sizeof(*new_HELP));
	
	if(strlen(commande) < 1){return aide;}
	
	strcpy(new_HELP->commande, commande);
	strcpy(new_HELP->prototype, proto);
	strcpy(new_HELP->short_desc, short_desc);
	strcpy(new_HELP->long_desc, long_desc);
	
	new_HELP->suiv = aide;
	
	return new_HELP;
}


int display_help(HELP aide){
	
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> HELP <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n\n");
	
	if(aide == NULL){
		printf("There is notnhing in Help !\n");
	}
	else{
		while(aide->suiv != NULL){
			printf("################## %s ##################\n\n", aide->commande);
			printf("> %s\n\n", aide->prototype);
			printf("> %s\n\n", aide->short_desc);
			printf("> %s\n", aide->long_desc);
			printf("\n\n\n");
			aide = aide->suiv;
		}
		printf("################## %s ##################\n\n", aide->commande);
		printf("> %s\n\n", aide->prototype);
		printf("> %s\n\n", aide->short_desc);
		printf("> %s\n", aide->long_desc);
		printf("\n\n\n");
	}
	
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> END HELP <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
}

HELP charge_help(){
	FILE * help;
	char commande[MAX_NOM_COMMANDE],commande1[MAX_NOM_COMMANDE];
	char prototype[MAX_PROTO_COMMANDE];
	char short_desc[MAX_SHORT_DESC];
	char long_desc[MAX_LONG_DESC];
	char tmp[2024];
	char c;
	HELP aide;
	
	help = fopen("HELP.txt", "r");
	if(help == NULL){
		printf("Problem opening HELP.txt\n");
		return aide;
	}
	aide = create_help();
	
	do{
		fgets(commande, MAX_NOM_COMMANDE, help);
		fgets(prototype, MAX_PROTO_COMMANDE, help);
		fgets(short_desc, MAX_SHORT_DESC, help);
		
		fgets(tmp, 2024, help);
		while(tmp[0] != '@'){
			strcat(long_desc, tmp);
			tmp[0] = '\0';
			fgets(tmp, 2024, help);
		}
		
		commande[strlen(commande) -2] = '\0'; /* 2 pour : \r\n */
		prototype[strlen(prototype) -2] = '\0';
		short_desc[strlen(short_desc) -2] = '\0';
		long_desc[strlen(long_desc) - 2] = '\0';
		
		if(strlen(commande) > MAX_NOM_COMMANDE){
			commande[MAX_NOM_COMMANDE] = '\0';
			commande[MAX_NOM_COMMANDE-1] = '>';
			commande[MAX_NOM_COMMANDE-2] = '>';
		}
		if(strlen(prototype) > MAX_PROTO_COMMANDE){
			prototype[MAX_PROTO_COMMANDE] = '\0';
			prototype[MAX_PROTO_COMMANDE-1] = '>';
			prototype[MAX_PROTO_COMMANDE-2] = '>';
		}
		if(strlen(short_desc) > MAX_SHORT_DESC){
			short_desc[MAX_SHORT_DESC] = '\0';
			short_desc[MAX_SHORT_DESC-1] = '>';
			short_desc[MAX_SHORT_DESC-2] = '>';
		}
		if(strlen(long_desc) > MAX_LONG_DESC){
			long_desc[MAX_LONG_DESC] = '\0';
			long_desc[MAX_LONG_DESC-1] = '>';
			long_desc[MAX_LONG_DESC-2] = '>';
		}

		if(commande[0] != '/'){
			aide = add_help(aide, commande, prototype, short_desc, long_desc);
		}
		
		commande[0] = '\0';
		short_desc[0] = '\0';
		long_desc[0] = '\0';
	}
	while(feof(help) == 0);
	
	fclose(help);
	
	return aide;
}

char * get_short_desc(HELP aide, char * commande){
	while(strcmp(commande, aide->commande) != 0){
		if(aide->suiv == NULL){
			return "no data";
		}
		aide = aide->suiv;
	}
	
	return aide->short_desc;
}

char * get_long_desc(HELP aide, char * commande){
	while(strcmp(commande, aide->commande) != 0){
		if(aide->suiv == NULL){
			return "no data";
		}
		aide = aide->suiv;
	}
	
	return aide->long_desc;
}

int display_help_long(HELP aide, char * commande){
	if(aide == NULL){
		printf("\nHelp is empty\n\n");
	}
	while(strcmp(commande, aide->commande) != 0){
		if(aide->suiv == NULL){
			printf("\nCommand %s unobtainable\n\n", commande);
			return 0;
		}
		aide = aide->suiv;
	}
	
	printf("\n################## %s ##################\n\n", aide->commande);
	printf("%s\n\n", aide->long_desc);
	printf("###########################################\n\n");
	
	return 1;
}

int display_help_all(HELP aide){
	if(aide == NULL){
		printf("\nHelp is empty\n\n");
		return 0;
	}
	printf(".\n");
	while(aide->suiv != NULL){
		printf(". %s: %s\n.\n", aide->commande, aide->short_desc);
		aide = aide->suiv;
	}
	printf(". %s: %s\n.\n", aide->commande, aide->short_desc);
	
	return 1;
}


