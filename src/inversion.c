/**
* @file recherche.c
* @brief 
* @author Durand Valentin TP3 Informatique Promo 2018
* @date Decembre 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "arbre.h"

int main(int argc, char *argv[])
{
	int *pix;
	int closest[3];
	color_table cTable;
	char *fichierImg, *fichierTable;
	image img, table;
    kdtree tree;

	assert(argc == 3);

	fichierImg = argv[1];
	fichierTable = argv[2];

	/* Creation image */
	img = FAIRE_image();
	image_charger(img,fichierImg);

	/* Creation de la table */
	table = FAIRE_image();
	image_charger(table,fichierTable);

	assert(image_give_hauteur(table) == 1);

	cTable = create_color_table(table);
    tree = create_kdtree(cTable, 10);

	image_debut(img);
	do
    {
    	pix = image_lire_pixel(img);
    	kdtree_get_nearest_color(tree, pix, closest);
  		image_ecrire_pixel(img, closest);
    }
  	while(image_pixel_suivant(img));

  	image_sauvegarder(img, "resultat-arbre.ppm");
  	system("gnome-open resultat-arbre.ppm");

	destroy_color_table(cTable);

	return 0;
}