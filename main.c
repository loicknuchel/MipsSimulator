#include "inc.h"
//#define DEBUG
//#define TESTCOLOR
#define EXEC

main(){
	MIPS simulateur;
	HELP aide;
	COMMANDE commandes_utilisateur[NB_MAX_COMMANDE];
	INSTR instruction_asm[2*NB_MAX_OPCODE];
	unsigned int instruction_courante;
	
	uint i;
	uint j;
	
	char entree_util[128];
	int fin;
	char ctmp;
	char tmp[128];
	char error[256];
	
	#ifdef TESTCOLOR
		/*
		printf("\033[30;40m Texte noir sur fond noir \033[0m\n");
		printf("\033[31;40m Texte rouge sur fond noir \033[0m\n");
		printf("\033[32;40m Texte vert sur fond noir \033[0m\n");
		printf("\033[33;40m Texte brown sur fond noir \033[0m\n");
		printf("\033[34;40m Texte blue sur fond noir \033[0m\n");
		printf("\033[35;40m Texte magenta sur fond noir \033[0m\n");
		printf("\033[36;40m Texte cyan sur fond noir \033[0m\n");
		printf("\033[37;40m Texte grey sur fond noir \033[0m\n");
		
		printf("\033[30;47m Texte noir sur fond grey \033[0m\n");
		printf("\033[31;47m Texte rouge sur fond grey \033[0m\n");
		printf("\033[32;47m Texte vert sur fond grey \033[0m\n");
		printf("\033[33;47m Texte brown sur fond grey \033[0m\n");
		printf("\033[34;47m Texte blue sur fond grey \033[0m\n");
		printf("\033[35;47m Texte magenta sur fond grey \033[0m\n");
		printf("\033[36;47m Texte cyan sur fond grey \033[0m\n");
		printf("\033[37;47m Texte grey sur fond grey \033[0m\n");
		
		printf("\033[30;46m Texte noir sur fond cyan \033[0m\n");
		printf("\033[31;46m Texte rouge sur fond cyan \033[0m\n");
		printf("\033[32;46m Texte vert sur fond cyan \033[0m\n");
		printf("\033[33;46m Texte brown sur fond cyan \033[0m\n");
		printf("\033[34;46m Texte blue sur fond cyan \033[0m\n");
		printf("\033[35;46m Texte magenta sur fond cyan \033[0m\n");
		printf("\033[36;46m Texte cyan sur fond cyan \033[0m\n");
		printf("\033[37;46m Texte grey sur fond cyan \033[0m\n");
		
		printf("\033[30;44m Texte noir sur fond blue \033[0m\n");
		printf("\033[31;44m Texte rouge sur fond blue \033[0m\n");
		printf("\033[32;44m Texte vert sur fond blue \033[0m\n");
		printf("\033[33;44m Texte brown sur fond blue \033[0m\n");
		printf("\033[34;44m Texte blue sur fond blue \033[0m\n");
		printf("\033[35;44m Texte magenta sur fond blue \033[0m\n");
		printf("\033[36;44m Texte cyan sur fond blue \033[0m\n");
		printf("\033[37;44m Texte grey sur fond blue \033[0m\n");
		
		printf("\033[30;41m Texte noir sur fond rouge \033[0m\n");
		printf("\033[31;41m Texte rouge sur fond rouge \033[0m\n");
		printf("\033[32;41m Texte vert sur fond rouge \033[0m\n");
		printf("\033[33;41m Texte brown sur fond rouge \033[0m\n");
		printf("\033[34;41m Texte blue sur fond rouge \033[0m\n");
		printf("\033[35;41m Texte magenta sur fond rouge \033[0m\n");
		printf("\033[36;41m Texte cyan sur fond rouge \033[0m\n");
		printf("\033[37;41m Texte grey sur fond rouge \033[0m\n");
		*/
		printf("\033[30m Texte noir sur fond blanc \033[0m\n");
		printf("\033[31m Texte rouge sur fond blanc \033[0m\n");
		printf("\033[32m Texte vert sur fond blanc \033[0m\n");
		printf("\033[33m Texte brown sur fond blanc \033[0m\n");
		printf("\033[34m Texte blue sur fond blanc \033[0m\n");
		printf("\033[35m Texte magenta sur fond blanc \033[0m\n");
		printf("\033[36m Texte cyan sur fond blanc \033[0m\n");
		printf("\033[37m Texte grey sur fond blanc \033[0m\n");
	#endif
	
		
	
	/*cr�ation de la structure HELP avec le nom des instruction, la description courte et la description lonue*/
	aide = charge_help();
	
	/*cr�ation :
	**	- des registres et les initialises � 0 (reg_sim)
	**	- de la m�moire et l'initialise � 0 avec calloc (mem_sim)
	**	- des breakpoint et initialise � NULL la liste (bp_sim)
	**	- la structure FILE en l'initialisant � 0 dans tous les champs(file_sim)
	**	- des registres sp�ciaux PC, HI et LO initialis�s � 0 (pc_sim, hi_sim et lo_sim)
	**	- de l'entr�e utilisateur (char **) initialis�e avec des chaines NULL (util_sim)
	**		ATTENTION dans l'entr�e util : 10 mots max et de longueur 19 max !!!! */
	simulateur = create_mips();
	
	/*chargement des noms des commandes shell � partir du fichier cfg_shell.txt*/
	charge_nom_shell(commandes_utilisateur);
	/*initialisation des liens entre les fonctions shell et les commandes entr�es*/
	link_shell(commandes_utilisateur);
	
	/*chargement des noms des instructions asm � partir du fichier cfg_asm.txt*/
	charge_nom_instr(instruction_asm);
	/*initialisation des liens entre les fonctions asm et les instructions lues               */
	link_asm(instruction_asm);
	/********************************************************************************************************************/
printf("\n");
printf("                ////////     ////////  ///////  //////////       /// ///    \n");
printf("                /////////    ////////  ///////  /////////////  /////////    \n");
printf("                  // ////    // ///      ///      ///    //// ///   ////    \n");
printf("                  //  ////  /// ///      ///      ///     /// /////         \n");
printf("                  //  ////  //  ///      ///      ///   /////  ////////     \n");
printf("                  //   /// //   ///      ///      //////////     ///////    \n");
printf("                  //   //////   ///      ///      ///                ////  \n");
printf("                  //    ////    ///      ///      ///         ////    ///  \n");
printf("                //////   ///  ///////  ///////  ///////       //////////   \n");
printf("                //////   //   ///////  ///////  ///////       ///  ///    \n");
printf("\n------------------------------------------------\n-------------- Simulateur de MIPS --------------\n\n\n");
	#ifdef DEBUG
		for(i=0; i<NB_MAX_COMMANDE; i++){
			printf("%d-%x) %s \n", i, i, commandes_utilisateur[i].nom);
		}
		affiche_mips(simulateur, instruction_asm);
	#endif
	
	#ifdef EXEC
	fin = 1;
	while(fin != 0){
		entree_util[0] = '\0';
		
		BLUE
		printf("> ");
		scanf("%[^\n]s", entree_util);
		ENDCOLOR
		if(entree_util[0] == 's', entree_util[1] == 'a', entree_util[2] == 'v', entree_util[3] == 'e'){
			getchar();
			save_res(simulateur, instruction_asm, entree_util);
		}
		for(i=0; i<10; i++){
			sprintf(util_sim[i], "");
		}
		getchar();
		coupe_mot(util_sim, entree_util);
		
		if(commande_exist(commandes_utilisateur, util_sim[0]) == 0 || entree_util[0] == '\0'){
			printf("\n command \"%s\" does not exist !\n\n", entree_util);
			continue;
		}
		
		fin = commandes_utilisateur[ get_no_commande(commandes_utilisateur, util_sim[0]) ].commande(simulateur, &bp_sim, instruction_asm, aide);
		printf("\n");
	}
	#endif
	
	/********************************************************************************************************************/
	/*desalloue toute la memoire allouee par calloc et malloc*/
	free(aide);
	free(reg_sim);
	free(pc_sim);
	free(hi_sim);
	free(lo_sim);
	free(mem_sim);
	free(bp_sim);
	free(util_sim);
	
	printf("\n--------------- Fin du programme ---------------\n\n");
	printf("Thanks for using KNUCHEL and MEYER software.");
	
	printf("\033[35;44m\033[0m\n");
	getchar();
	return 1;
}



