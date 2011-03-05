/*--------------------------------------------------------------------------*/
/* Phelma 2009/10 - Projet Informatique                                     */
/*                                                                          */
/* elfLoader.h                                                              */
/* Ouverture et récupération des données dans un fichier au format Elf,     */
/* assemblé pour une architecture MIPS.                                     */
/* Nb: vous devez auparavant avoir installé libelf et configuré votre       */
/* environnement correctement (définition des variables LIBELF_DIR et       */
/* LIBELFLOADER_LIB). Tout est ok à l'école, voir la page web du projet     */
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

/**
 * Lit la taille de la section .bss d'un fichier elf ouvert.
 * Un fichier elf doit auparavant avoir été ouvert à l'aide de la 
 * fonction openEfl. Une erreur est levée sinon.
 * @param size le nombre d'octets de la section .bss, éventuellement 0
 */
void getBssSection(unsigned int * size);

/**
 * Lit la table des chaines d'un fichier elf ouvert.
 * Un fichier elf doit auparavant avoir été ouvert à l'aide de la 
 * fonction openEfl. Une erreur est levée sinon.
 * Pas de copie profonde des chaines, ne pas desallouer le tableau data,
 * il est libere par closeElf() !!
 * @param size le nombre de chaines dans la table, éventuellement 0
 * @param data le tableau des chaines de caracteres lues, éventuellement NULL
 */
void getStringTable(unsigned int * size, unsigned char *** data);

/**
 * Lit la table des symboles d'un fichier elf ouvert.
 * La table contient tous les symboles: symboles définis et/ou utilises, 
 * qu'ils soient local ou global, et noms de sections.
 * Un fichier elf doit auparavant avoir été ouvert à l'aide de la 
 * fonction openEfl. Une erreur est levée sinon.
 * Pas de copie profonde des chaines, ne pas desallouer le tableau data,
 * il est libere par closeElf() !!
 * @param size le nombre de symboles dans la table, éventuellement 0
 * @param data le tableau des symboles elf, éventuellement NULL
 */
void getSymbolTable(unsigned int * size, Elf32_Sym ** data);


/**
 * Lit la section de relocation .rel.text d'un fichier elf ouvert.
 * Un fichier elf doit auparavant avoir été ouvert à l'aide de la 
 * fonction openEfl. Une erreur est levée sinon.
 * Pas de copie profonde des infos de relocation, ne pas desallouer 
 * le tableau data il est libere par closeElf() !!
 * @param size le nombre d'octets de la section .rel.text, éventuellement 0
 * @param data la table des entrées de relocation, éventuellement null.
 */
void getTextRelocSection(unsigned int * size, Elf32_Rel ** data);

/**
 * Lit la section de relocation .rel.data d'un fichier elf ouvert.
 * Un fichier elf doit auparavant avoir été ouvert à l'aide de la 
 * fonction openEfl. Une erreur est levée sinon.
 * Pas de copie profonde des infos de relocation, ne pas desallouer 
 * le tableau data il est libere par closeElf() !!
 * @param size le nombre d'octets de la section .rel.data, éventuellement 0
 * @param data la table des entrées de relocation, éventuellement null.
 */
void getDataRelocSection(unsigned int * size, Elf32_Rel ** data);



/** Ferme le dernier fichier elf ayant été ouvert. Une erreur est levée 
 *  si aucun fichier n'est ouvert au moment de l'appel. */
void closeElf();

#endif	 /* #define _MINIELFLOADER_ */
