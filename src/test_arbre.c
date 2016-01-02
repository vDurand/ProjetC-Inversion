/**
* @file test_table.c
* @brief test des differents fonctions de table.c
* @author Durand Valentin TP3 Informatique Promo 2018
* @date Decembre 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "arbre.h"

int main(int argc, char *argv[])
{
	color_table cTable;
	kdtree tree;
	char *fichier = argv[1];

	/* Creation image */
	image input = FAIRE_image();
	image_charger(input,fichier);

	/* Creation de la table */
	cTable = create_color_table(input);

	tree = create_kdtree(cTable, 10);

	return 0;
}