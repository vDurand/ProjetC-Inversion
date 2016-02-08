/**
* @file recherche.c
* @brief 
* @author Durand Valentin TP3 Informatique Promo 2018
* @date Decembre 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "image.h"
#include "arbre.h"

int main(int argc, char *argv[])
{
	int *pix, threshold;
	int closest[3];
	color_table cTable;
	char *fichierImg, *fichierTable, *end, *exec;
	clock_t debut;
	double temps;
	image img, table, temp;
    kdtree tree;

    if(argc < 3){
    	printf("Please specify the picture and color table as arguments.\n");
    	exit(1);
    }

	fichierImg = argv[1];
	fichierTable = argv[2];

	if(argc == 4)
		threshold = atoi(argv[3]);
	else
		threshold = 10;

  	end = fichierImg + strlen(fichierImg) - 4;

  	if(strcmp(end, ".ppm") != 0){
  		printf("Please specify .ppm pictures as arguments.\n");
  		exit(2);
  	}

	/* Creation image */
	img = FAIRE_image();
	image_charger(img,fichierImg);

	/* Creation de la table */
	table = FAIRE_image();
	image_charger(table,fichierTable);

	if(image_give_hauteur(table) != 1 && image_give_hauteur(img) == 1){
		temp = table;
		table = img;
		img = temp;
	}
	if(image_give_hauteur(table) != 1){
		printf("Please specify a valid color table as argument.\n");
		exit(3);
	}
	/*assert(image_give_hauteur(table) == 1);*/

	cTable = create_color_table(table);
    tree = create_kdtree(cTable, threshold);

    printf("Beginning inversion with a kdtree at a %d threshold...\n", threshold);
    debut = clock();

	image_debut(img);
	do
    {
    	pix = image_lire_pixel(img);
    	kdtree_get_nearest_color(tree, pix, closest);
  		image_ecrire_pixel(img, closest);
    }
  	while(image_pixel_suivant(img));
  	
  	temps = (double)(clock() - debut) / CLOCKS_PER_SEC;
  	printf("Inversion completed successfully in %f s.\n", temps);

  	strcpy(end, "_resultInversionByTree.ppm");
  	image_sauvegarder(img, fichierImg);

  	printf("Result picture saved : %s\n", fichierImg);

  	exec = malloc(strlen(fichierImg) + 12);
  	strcpy(exec, "gnome-open ");
    strcat(exec, fichierImg);
  	system(exec);
  	free(exec);

	destroy_color_table(cTable);

	return 0;
}