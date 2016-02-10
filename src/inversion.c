/**
 * @file inversion.c
 * @brief Inversion d une image par une table de couleur en un kd arbre
 * @author Durand Valentin TP3 Informatique Promo 2018
 * @date Janvier 2016
 * On decoupe la table de couleur dans un arbre afin de reduire le nombre de couleur a comparer
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

    /* Verification qu on a au moins 2 arguments */
    if(argc < 3){
    	printf("Please specify the picture and color table as arguments.\n");
    	exit(1);
    }

    /* Recuperation des noms des fichiers image et table passes en parametres */
	fichierImg = argv[1];
	fichierTable = argv[2];

	/* Le 3e argument optionel est le seuil de recherche */
	if(argc == 4)
		threshold = atoi(argv[3]);
	else
		threshold = 10;

	/* On initialise un pointer char juste avant .ppm dans le nom de l image */
  	end = fichierImg + strlen(fichierImg) - 4;

  	/* On verifie que l image est bien au format ppm */
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

	/* Inversion table et image si arguments inverses */
	if(image_give_hauteur(table) != 1 && image_give_hauteur(img) == 1){
		temp = table;
		table = img;
		img = temp;
	}

	/* Verification que la table a bien une hauteur de 1 */
	if(image_give_hauteur(table) != 1){
		printf("Please specify a valid color table as argument.\n");
		exit(3);
	}

	cTable = create_color_table(table);
    tree = create_kdtree(cTable, threshold);

    /* On debute un timer pour le temps d execution */
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

  	/* On arrete le timer */
  	temps = (double)(clock() - debut) / CLOCKS_PER_SEC;
  	printf("Inversion completed successfully in %f s.\n", temps);

  	/* On sauvegarde l image resultat */
  	strcpy(end, "_resultInversionByTree.ppm");
  	image_sauvegarder(img, fichierImg);

  	printf("Result picture saved : %s\n", fichierImg);

  	/* On ouvre l image */
  	exec = malloc(strlen(fichierImg) + 12);
  	strcpy(exec, "gnome-open ");
    strcat(exec, fichierImg);
  	system(exec);
  	free(exec);

  	/* On nettoie */
	destroy_kdtree(tree);

	return 0;
}