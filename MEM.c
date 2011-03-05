#include "inc.h"
//#define DEBUG

OCTET * create_mem(MIPS simulateur){
	OCTET * mem;
	int mem_size;
	
	mem_size = simulateur.mem_size;
	
	mem = calloc(mem_size, sizeof(OCTET));
	
	return (OCTET *) mem;
}

OCTET get_mem(MIPS simulateur, int adresse){
	  return mem_sim[adresse];
}


int set_mem(MIPS simulateur, int adresse, OCTET val){
	mem_sim[adresse]=val;
	return 1;
}

int cpy_mem(MIPS simulateur, int source, int cible){
	set_mem(simulateur, cible, get_mem(simulateur, source));
	return 1;
}

int display4_mem(MIPS simulateur, INSTR * instruction_asm, int debut, int fin){
	char error[256];
	char err[128];
	int i;
	debut = debut - (debut%4);
	if(fin - debut > 1024){
		fin = debut + 1024;
		sprintf(err, "Warning, the memory area printed has been reduced from 0x%x to 0x%x\n", debut, fin);
	}
	else{
		sprintf(err, "");
	}
	
	printf("\n  ---- MEMOIRE ---- from 0x%x to 0x%x -------------------------------------\n", debut, fin);
	printf("  --\n");
	
	for(i=debut; i<fin+1; i=i+4){
		printf("  -- 0x%06x) 0x%02x 0x%02x 0x%02x 0x%02x : %s\n", i, mem_sim[i], mem_sim[i+1], mem_sim[i+2], mem_sim[i+3], traduit_instruction(simulateur, instruction_asm, i, error));
	}
		
	printf("  ------------------------------------------------------------------\n");
	printf("%s", err);
	return 1;
}

int display16_mem(MIPS simulateur, INSTR * instruction_asm, int debut, int fin){
	char err[128];
	int i;
	int j;
	int k;
	debut = debut - (debut%4);
	if(fin - debut > 1024){
		fin = debut + 1024;
		sprintf(err, "Warning, the memory area printed has been reduced from 0x%x to 0x%x\n", debut, fin);
	}
	else{
		sprintf(err, "");
	}
	
	printf("\n  ---- MEMOIRE ---- from 0x%x to 0x%x -------------------------------------\n", debut, fin);
	printf("  --\n");
	
	for(i=debut; i<fin+1; i=i+16){
		printf("  -- 0x%06x)", i);
		k = 0;
		for(j=0; j<16; j++){
			if(k == 4){
				printf("  ");
			k = 0;
			}
			printf(" 0x%02x", mem_sim[i+j]);
			k++;
		}
		printf("\n");
	}
		
	printf("  ------------------------------------------------------------------\n");
	printf("%s", err);
	return 1;
}

int display_mem_not_null(MIPS simulateur, INSTR * instruction_asm, int debut, int fin){
	int i;
	char error[256];
	debut = debut - (debut%4);
	
	printf("\n  ---- MEMOIRE ---- from %d to %d -------------------------------------\n", debut, fin);
	printf("  --\n");
	for(i=debut; i<fin+1; i=i+4){
		if(mem_sim[i] != 0 || mem_sim[i+1] != 0 || mem_sim[i+2] != 0 || mem_sim[i+3] != 0){
			printf("  -- %06d) %03d %03d %03d %03d : %s\n", i, mem_sim[i], mem_sim[i+1], mem_sim[i+2], mem_sim[i+3], traduit_instruction(simulateur, instruction_asm, i, error));
		}
	}
	printf("  ------------------------------------------------------------------\n");

	return 1;
}










