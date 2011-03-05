#include "inc.h"
//#define DEBUG

int save_dasm(MIPS simulateur, INSTR * instruction_asm, char * filename){
	int i;
	char error[256];
	unsigned int textaddr, dataaddr, textfin, datafin;
	FILE * save;
	
	save = fopen(filename, "w");
	
	fprintf(save, "\n>>fichier \"%s\", PC actuel : %x<<\n", file_sim->nom, get_pc(simulateur));
	
	if(file_sim->nom[0] != '\0'){
		textaddr = file_sim->text;
		textfin = file_sim->text + file_sim->sizetext;
		dataaddr = file_sim->data;
		datafin = file_sim->data + file_sim->sizedata;
		
		fprintf(save, "\n  ---------- Desassemblage ------------------------------------------\n\n\n", file_sim->nom);
		fprintf(save, "                  .set noreorder\n");
		fprintf(save, "                  .set noat\n");
		fprintf(save, "                  .text\n");
		for(i=textaddr; i<textfin; i=i+4){
			fprintf(save, "  %04x  %08x  %s\n", i, assemble_mot(mem_sim[i], mem_sim[i+1], mem_sim[i+2], mem_sim[i+3]), traduit_instruction(simulateur, instruction_asm, i, error));
		}
		fprintf(save, "\n");
	}
	
	fclose(save);
	
	return 1;
}

int save_dreg(MIPS simulateur, INSTR * instruction_asm, char * filename){

	int no = 0;
	char nom_reg[20];
	FILE * save;
	int i;
	save = fopen(filename, "w");
	
	fprintf(save, "\n>>fichier \"%s\", PC actuel : %x<<\n", file_sim->nom, get_pc(simulateur));
	
	fprintf(save, "\n  ---- REGISTRES ----------------------------------------------\n");
	fprintf(save, "  --\n");
	
	
	fprintf(save, "  --     0x%02x      ", 0);
	for(i=1; i<8; i++){
		fprintf(save, "  0x%02x      ", i);
	}
	fprintf(save, "\n  --     %s       ", reg_sim[0].nom);
	for(i=1; i<8; i++){
		fprintf(save, " %s        ", reg_sim[i].nom);	
	}
	fprintf(save, "\n  --  0x%08x ", reg_sim[0].val);
	for(i=1; i<8; i++){
		fprintf(save, " 0x%08x ", reg_sim[i].val);
	}
	fprintf(save, "\n  --\n");
	
	
	fprintf(save, "  --     0x%02x      ", 8);
	for(i=9; i<16; i++){
		fprintf(save, "  0x%02x      ", i);
	}
	fprintf(save, "\n  --      %s        ", reg_sim[8].nom);
	for(i=9; i<16; i++){
		fprintf(save, " %s        ", reg_sim[i].nom);	
	}
	fprintf(save, "\n  --  0x%08x ", reg_sim[8].val);
	for(i=9; i<16; i++){
		fprintf(save, " 0x%08x ", reg_sim[i].val);
	}
	fprintf(save, "\n  --\n");
	
	
	fprintf(save, "  --     0x%02x      ", 16);
	for(i=17; i<24; i++){
		fprintf(save, "  0x%02x      ", i);
	}
	fprintf(save, "\n  --      %s        ", reg_sim[16].nom);
	for(i=17; i<24; i++){
		fprintf(save, " %s        ", reg_sim[i].nom);	
	}
	fprintf(save, "\n  --  0x%08x ", reg_sim[16].val);
	for(i=17; i<24; i++){
		fprintf(save, " 0x%08x ", reg_sim[i].val);
	}
	fprintf(save, "\n  --\n");
	
	
	fprintf(save, "  --     0x%02x      ", 24);
	for(i=25; i<32; i++){
		fprintf(save, "  0x%02x      ", i);
	}
	fprintf(save, "\n  --      %s        ", reg_sim[24].nom);
	for(i=25; i<32; i++){
		fprintf(save, " %s        ", reg_sim[i].nom);	
	}
	fprintf(save, "\n  --  0x%08x ", reg_sim[24].val);
	for(i=25; i<32; i++){
		fprintf(save, " 0x%08x ", reg_sim[i].val);
	}	
	fprintf(save, "\n  --\n");
	

	fprintf(save, "  --\n  -- speciaux: %s:0x%x, %s:0x%x, %s:0x%x\n", pc_sim->nom, pc_sim->val, hi_sim->nom, hi_sim->val, lo_sim->nom, lo_sim->val);
	
			
	fclose(save);
	
	return 1;
}

int save_dmem(MIPS simulateur, INSTR * instruction_asm, char * filename){
	
	int i, j, k, debut, fin;
	FILE * save;
	
	save = fopen(filename, "w");
	
	fprintf(save, "\n>>fichier \"%s\", PC actuel : %x<<\n", file_sim->nom, get_pc(simulateur));
	
	if(util_sim[1][0] != '\0' && util_sim[2][0] != '\0'){
		debut = atohi(util_sim[1]);
		fin = atohi(util_sim[2]);
	}
	else{
		debut = atohi(util_sim[1]);
		fin = debut + 15;
	}
		fprintf(save, "\n  ---- MEMOIRE ---- from 0x%x to 0x%x -------------------------------------\n", debut, fin);
		fprintf(save, "  --\n");
	
		for(i=debut; i<fin+1; i=i+16){
			fprintf(save, "  -- 0x%06x)", i);
			k = 0;
			for(j=0; j<16; j++){
				if(k == 4){
					fprintf(save, "  ");
				k = 0;
				}
				fprintf(save, " 0x%02x", mem_sim[i+j]);
				k++;
			}
			fprintf(save, "\n");
		}
	fclose(save);
	
	return 1;
}





