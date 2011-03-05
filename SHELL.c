#include "inc.h"
//#define DEBUG

int display_nom_commande(COMMANDE * commandes_utilisateur){
	int i;
	for(i=0; i<NB_MAX_COMMANDE; i++){
		if(commandes_utilisateur[i].nom[0] != '\0'){
			printf("code: %02x nom: %s\n", i, commandes_utilisateur[i].nom);
		}
	}
	return 1;
}

int charge_nom_shell(COMMANDE * commandes_utilisateur){
	FILE * cfg;
	char nom[15];
	int code;
	
	int i;
	char tmp[30];
	
	for(i=0; i<NB_MAX_COMMANDE; i++){
		commandes_utilisateur[i].nom[0] = '\0';
	}
	
	cfg = fopen("cfg_shell.txt", "r");
	
	while(feof(cfg) == 0){
		nom[0] = '\0';
		code = 0;
		
		fscanf(cfg, "%s", nom);
		if(nom[0] == '/'){
			fscanf(cfg, "%[^\n]s", tmp);
			continue;
		}
		fscanf(cfg, "%x", &code);
		
		strcpy(commandes_utilisateur[code].nom, nom);
	}
	
	fclose(cfg);
	return 1;
}

int get_no_commande(COMMANDE * commandes_utilisateur, char * commande){
	int i;
	for(i=0; i<NB_MAX_COMMANDE; i++){
		if(strcmp(commandes_utilisateur[i].nom, commande) == 0){
			return i;
		}
	}
	
	return i+1;
}

int commande_exist(COMMANDE * commandes_utilisateur, char * commande){
	int i;
	for(i=0; i<NB_MAX_COMMANDE; i++){
		if(strcmp(commandes_utilisateur[i].nom, commande) == 0){
			return 1;
		}
	}
	
	return 0;
}

int link_shell(COMMANDE * commandes_utilisateur){
		
	commandes_utilisateur[ get_no_commande(commandes_utilisateur, "load") ].commande = s_load;
	commandes_utilisateur[ get_no_commande(commandes_utilisateur, "clear") ].commande = s_clear;
	commandes_utilisateur[ get_no_commande(commandes_utilisateur, "dasm") ].commande = s_dasm;
	commandes_utilisateur[ get_no_commande(commandes_utilisateur, "dreg") ].commande = s_dreg;
	commandes_utilisateur[ get_no_commande(commandes_utilisateur, "sreg") ].commande = s_sreg;
	commandes_utilisateur[ get_no_commande(commandes_utilisateur, "dmem") ].commande = s_dmem;
	commandes_utilisateur[ get_no_commande(commandes_utilisateur, "smem") ].commande = s_smem;
	commandes_utilisateur[ get_no_commande(commandes_utilisateur, "run") ].commande = s_run;
	commandes_utilisateur[ get_no_commande(commandes_utilisateur, "step") ].commande = s_step;
	commandes_utilisateur[ get_no_commande(commandes_utilisateur, "stepi") ].commande = s_stepi;
	commandes_utilisateur[ get_no_commande(commandes_utilisateur, "addbp") ].commande = s_addbp;
	commandes_utilisateur[ get_no_commande(commandes_utilisateur, "rmbp") ].commande = s_rmbp;
	commandes_utilisateur[ get_no_commande(commandes_utilisateur, "dbp") ].commande = s_dbp;
	commandes_utilisateur[ get_no_commande(commandes_utilisateur, "help") ].commande = s_help;
	commandes_utilisateur[ get_no_commande(commandes_utilisateur, "exit") ].commande = s_exit;
	
	commandes_utilisateur[ get_no_commande(commandes_utilisateur, "dfile") ].commande = s_dfile;
	commandes_utilisateur[ get_no_commande(commandes_utilisateur, "smems") ].commande = s_smems;
	commandes_utilisateur[ get_no_commande(commandes_utilisateur, "dmemnn") ].commande = s_dmemnn;
	commandes_utilisateur[ get_no_commande(commandes_utilisateur, "dmips") ].commande = s_dmips;
	
	
	return 1;
}
























