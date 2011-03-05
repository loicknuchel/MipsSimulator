#ifndef _BP_H_
#define _BP_H_

typedef struct _BP{
	int bp;
	int type; /*0: stepi, 1: utilisateur, 2: fin section, 3: fin memoire*/
	struct _BP *suiv;
} * BP;

BP create_bp();
int is_bp_empty(BP breakliste);
int display_bp(BP breakliste, int type);
BP add_bp(BP breakliste, int val_bp, int type);
BP rm_bp(BP * breakliste, int val_bp, int type);
BP rm_all_bp(BP * breakliste, int type);

#endif


