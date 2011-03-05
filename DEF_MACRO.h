#define uchar unsigned char
#define uint unsigned int
 
#define MEM_SIZE 131072
#define FILE_MAX_SIZE 2000000
#define FILE_NAME_MAX_SIZE 50
#define MAX_NOM_REG 6
#define MAX_NOM_INSTR 8
#define MAX_NOM_COMMANDE 20
#define MAX_PROTO_COMMANDE 128
#define MAX_SHORT_DESC 256
#define MAX_LONG_DESC 2048
#define NB_MAX_OPCODE 64
#define NB_MAX_COMMANDE 32
#define NB_ENTREE_UTIL 10
#define SIZE_MOT_UTIL 20
 
#define PRINT(x) fprintf( stderr, "Value of "#x"= %d at %p (%s, l. %d)\n", x, (void *)&x, __FILE__, __LINE__ )
#define BUG fprintf( stderr, "\n\tNow in file \"%s\", function \"%s\", line %d\n\n", __FILE__, __FUNCTION__, __LINE__ );

#define RED printf("\033[31m \033[27m");
#define GREEN printf("\033[32m \033[27m");
#define BLUE printf("\033[34m \033[27m");
#define ENDCOLOR printf("\033[31m \033[0m");

#define reg_sim simulateur.registres
#define mem_size_sim simulateur.mem_size
#define mem_sim simulateur.memoire
#define bp_sim simulateur.breakpoint
#define file_sim simulateur.file
#define pc_sim simulateur.PC
#define hi_sim simulateur.HI
#define lo_sim simulateur.LO
#define util_sim simulateur.entree_utilisateur

