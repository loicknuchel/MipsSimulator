#include "inc.h"
//#define DEBUG

BP create_bp(){
   return NULL;
}

int is_bp_empty(BP breakliste){
	if (breakliste==NULL) return 0;
	else return 1;
}

int display_bp(BP breakliste, int type){
	int i;
	int j;
	int aff = 0;
	
	if(type != 10){
		printf("\n  ---- BREAKPOINT - type %d -------------------------------\n", type);
	}
	else{
		printf("\n  ---- BREAKPOINT ----------------------------------------\n");
		type = 1;
	}
	printf("  --\n");
	if(breakliste == NULL){
		printf("  -- No breakpoint\n");
	}
	else{
		i = 0;
		j = 1;
		printf("  -- ");
		while(breakliste->suiv != NULL){
			if(breakliste->type == type){
				printf("0x%x - ", breakliste->bp);
				if(9*j == i){
					printf("\n  -- ");
					j++;
				}
				i++;
				aff = 1;
			}
			breakliste = breakliste->suiv;
		}
		if(breakliste->type == type){
			printf("0x%x\n", breakliste->bp);
		}
		else if(aff == 1){
			printf("\n");
		}
		else{
			printf(" No breakpoint\n");
		}
	}
	printf("  --------------------------------------------------------\n");
	
	return 1;
}

BP add_bp(BP breakliste, int val_bp, int type){
	BP new_liste = calloc(1,sizeof(*new_liste));
	BP p = calloc(1,sizeof(*p));
	p = breakliste;
	
	new_liste->bp = val_bp;
	new_liste->type = type;
	new_liste->suiv = NULL;
	
	if(p == NULL){
		new_liste->suiv = p;
		return new_liste;
	}
	
	else if(p->suiv == NULL){
		if(p->bp < new_liste->bp){
			p->suiv = new_liste;
			return breakliste;
		}
		else if(p->bp > new_liste->bp){
			new_liste->suiv = p;
			return new_liste;
		}
		else{
			//printf("Warning, breakpoint already loaded/*deja entre*/ !!\n");
			return breakliste;
		}
	}
	
	else if(p->bp > new_liste->bp){
		new_liste->suiv = p;
		return new_liste;
	}
	
	else{
		while(p->suiv != NULL && p->suiv->bp < new_liste->bp){
			p = p->suiv;
		}
		if(p->suiv == NULL){
			if(p->bp == new_liste->bp){
				//printf("Warning, breakpoint already loaded/*deja entre*/ !!\n");
				return breakliste;
			}
			p->suiv = new_liste;
			return breakliste;
		}
		else{
			if(p->bp == new_liste->bp || p->suiv->bp == new_liste->bp){
				//printf("Warning, breakpoint already loaded/*deja entre*/ !!\n");
				return breakliste;
			}
			new_liste->suiv = p->suiv;
			p->suiv = new_liste;
			return breakliste;	
		}
	}
}

BP rm_bp(BP * breakliste, int val_bp, int type){
	BP p = calloc(1,sizeof(*p));
	p = *breakliste;
	
	if(p == NULL){
		//printf("There is not any breakpoint in this list!\n");
		return p;
	}
	else if(p->suiv == NULL){
		if(p->bp == val_bp){
			return p->suiv;
		}
		else{
			//printf("The breakpoint to erase could not have been found !\n");
			return p;
		}
	}
	else if(p->bp == val_bp){
		p=p->suiv;
		return p;
	}
	else{
		while(p->suiv->suiv != NULL && p->suiv->bp != val_bp){
			p = p->suiv;
		}
		if(p->suiv->bp == val_bp){
			if(p->suiv->suiv == NULL){
				p->suiv = NULL;
				return *breakliste;
			}
			else{
				p->suiv = p->suiv->suiv;
				return *breakliste;
			}
		}
		else if(p->suiv->suiv == NULL){
			//printf("The breakpoint to find has not been found !\n");
			return *breakliste;
		}
	}
}

BP rm_all_bp(BP * breakliste, int type){
	int i = 0;
	
	while(is_bp_empty(*breakliste) != 0){
		*breakliste = rm_bp(breakliste, (*breakliste)->bp, type);
		i++;
	}
	
	return *breakliste;
}

