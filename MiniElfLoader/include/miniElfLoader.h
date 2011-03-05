/*--------------------------------------------------------------------------*/
/* Phelma 2009/10 - Projet Informatique                                     */
/*                                                                          */
/* miniElfLoader.h                                                          */
/* Ouverture et récupération des données dans un fichier au format Elf,     */
/* assemblé pour une architecture MIPS.                                     */
/* Version "mini", qui ne permet de récupérer que les sections .text et     */
/* .data                                                                    */
/* Nb: vous devez auparavant avoir installé libelf et configuré votre       */
/* environnement correctement (définition des variables LIBELF_DIR et       */
/* LIBMINIELFLOADER_LIB). Tout est ok à l'école, voir la page web du projet */
/* pour le faire sur une machine perso).                                    */
/*--------------------------------------------------------------------------*/

#ifndef _MINIELFLOADER_
#define _MINIELFLOADER_

#include <libelf/libelf.h>
#include <libelf/gelf.h>


/** Ouvre un fichier au format elf à partir de son nom.
 *  L'exécution est interrompue si problème à l'ouverture */
void openElf(char * filename);

/**
 * Lit la section .text d'un fichier elf ouvert.
 * Le tableau d'octets non signés data est alloué au sein de cette
 * fonction, avec la taille size. Il devra être libéré par l'utilisateur.
 * Un fichier elf doit auparavant avoir été ouvert à l'aide de la 
 * fonction openEfl. Une erreur est levée sinon.
 * @param size le nombre d'octets de la section .text, éventuellement 0
 * @param data le tableau des octets de la section .text, éventuellement null.
 */
void getTextSection(unsigned int * size, unsigned char ** data);

/**
 * Lit la section .data d'un fichier elf ouvert.
 * Le tableau d'octets non signés data est alloué au sein de cette
 * fonction, avec la taille size. Il devra être libéré par l'utilisateur.
 * Un fichier elf doit auparavant avoir été ouvert à l'aide de la 
 * fonction openEfl. Une erreur est levée sinon.
 * @param size le nombre d'octets de la section .data, éventuellement 0
 * @param data le tableau des octets de la section .data, éventuellement null.
 */
void getDataSection(unsigned int * size, unsigned char ** data);


/** Ferme le dernier fichier elf ayant été ouvert. Une erreur est levée 
 *  si aucun fichier n'est ouvert au moment de l'appel. */
void closeElf();

#endif	 /* #define _MINIELFLOADER_ */
