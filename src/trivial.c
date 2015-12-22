/**
* @file trivial.c
* @brief 
* @author Durand Valentin TP3 Informatique Promo 2018
* @date Decembre 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "table.h"

int main(int argc, char *argv[])
{
	int i;
	color_table cTable;
	char *fichierImg, *fichierTable;
	image img, table;

	assert(argc == 3);

	*fichierImg = argv[1];
	*fichierTable = argv[2];

	/* Creation image */
	image img = FAIRE_image();
	image_charger(img,fichierImg);

	/* Creation de la table */
	image table = FAIRE_image();
	image_charger(table,fichierTable);
	cTable = create_color_table(table);

	destroy_color_table(cTable);

	return 0;
}