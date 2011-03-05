#ifndef _HELP_H_
#define _HELP_H_
#include "my_help.h"

#define MAX_NOM_COMMANDE 20
#define MAX_PROTO_COMMANDE 128
#define MAX_SHORT_DESC 256
#define MAX_LONG_DESC 2048

typedef struct _HELP{
	char commande[MAX_NOM_COMMANDE];
	char prototype[MAX_PROTO_COMMANDE];
	char short_desc[MAX_SHORT_DESC];
	char long_desc[MAX_LONG_DESC];
	struct _HELP *suiv;
} * HELP;

/*
 Cree le HELP et l'initialise avec 0 maillon.
*/
HELP create_help();

/*
 Affiche l'ensemble du contenu du HELP
*/
int display_help(HELP aide);

/*
 Ajoute (en-tete) un element au HELP.
*/
HELP add_help(HELP aide, char * commande, char * proto, char * short_desc, char * long_desc);

/*

*/
HELP charge_help();
char * get_short_desc(HELP aide, char * commande); 
char * get_long_desc(HELP aide, char * commande);
int display_help_long(HELP aide, char * commande);
int display_help_all(HELP aide);

#endif
