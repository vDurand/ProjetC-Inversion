/**
 * @file graphdata.c
 * @brief Sauvegarde les temps d execution pour l inversion d une image par methode triviale et kd arbre
 * @author Durand Valentin TP3 Informatique Promo 2018
 * @date Janvier 2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "image.h"
#include "arbre.h"

int get_exec_time_tree(char* fichierImg, char* fichierTable, int threshold)
{
	int *pix;
	int closest[3];
	color_table cTable;
	clock_t debut;
	int temps;
	image img, table, temp;
    kdtree tree;

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

    printf("Beginning inversion of %s with a kdtree at a %d threshold...\n", fichierTable, threshold);
    debut = clock();

	image_debut(img);
	do
    {
    	pix = image_lire_pixel(img);
    	kdtree_get_nearest_color(tree, pix, closest);
  		image_ecrire_pixel(img, closest);
    }
  	while(image_pixel_suivant(img));
  	
  	temps = (int)(clock() - debut);
  	printf("Inversion completed successfully in %d s.\n", temps);

	destroy_kdtree(tree);

	return temps;
}

int get_exec_time_trivial(char* fichierImg, char* fichierTable)
{
	int i, *pix;
	int closest[3];
	color_table cTable;
	clock_t debut;
	int temps;
	image img, table, temp;

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

    printf("Beginning inversion of %s with trivial method...\n", fichierTable);
    debut = clock();

	image_debut(img);
	do
    {
    	pix = image_lire_pixel(img);
    	closest[red] = cTable->table[red][0];
    	closest[green] = cTable->table[green][0];
    	closest[blue] = cTable->table[blue][0];
    	for(i = 1; i < cTable->count; i++){
    		if(sqrt(
    				pow(pix[red]-cTable->table[red][i], 2)
    				+
    				pow(pix[green]-cTable->table[green][i], 2)
    				+
    				pow(pix[blue]-cTable->table[blue][i], 2)
					)
    			<
    			sqrt(
    				pow(pix[red]-closest[red], 2)
    				+
    				pow(pix[green]-closest[green], 2)
    				+
    				pow(pix[blue]-closest[blue], 2)
    				)
				)
    		{
    			closest[red] = cTable->table[red][i];
		    	closest[green] = cTable->table[green][i];
		    	closest[blue] = cTable->table[blue][i];
    		}
  		}
  		image_ecrire_pixel(img, closest);
    }
  	while(image_pixel_suivant(img));
  	
  	temps = (int)(clock() - debut);
  	printf("Inversion completed successfully in %d s.\n", temps);

	destroy_color_table(cTable);

	return temps;
}

int main(int argc, char *argv[])
{
	int threshold, i;
	char *fichierImg, *fichierTable;
	char temp[1024];
	int a = 128, b, c;
	FILE *fp;

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

	fp = fopen("datadump", "w");

	for (i = 0; i < 4; ++i)
	{
		sprintf(temp, "%s_%d.ppm", fichierTable, a);
		b = get_exec_time_tree(fichierImg, temp, threshold);
		c = get_exec_time_trivial(fichierImg, temp);
		fprintf(fp, "%d %d %d\n", a, b, c);
		a *= 2;
	}

	fclose(fp);

	return 0;
}