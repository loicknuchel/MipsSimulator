#ifndef _SHELL_H_
#define _SHELL_H_

typedef struct _COMMANDE{
	char nom[MAX_NOM_COMMANDE];
	int (*commande)(MIPS , BP * , INSTR * , HELP);
} COMMANDE;


int display_nom_commande(COMMANDE * commandes_utilisateur);
int charge_nom_shell(COMMANDE * commandes_utilisateur);
int get_no_commande(COMMANDE * commandes_utilisateur, char * commande);
int link_shell(COMMANDE * commandes_utilisateur);
int commande_exist(COMMANDE * commandes_utilisateur, char * commande);

#endif




