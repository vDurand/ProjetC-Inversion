/**
* @file trivial.c
* @brief 
* @author Durand Valentin TP3 Informatique Promo 2018
* @date Decembre 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "image.h"
#include "table.h"

int main(int argc, char *argv[])
{
	int i, *pix;
	int closest[3];
	color_table cTable;
	char *fichierImg, *fichierTable, *end, *exec;
    clock_t debut;
    double temps;
	image img, table;

	assert(argc == 3);

	fichierImg = argv[1];
	fichierTable = argv[2];

    end = fichierImg + strlen(fichierImg) - 4;

	/* Creation image */
	img = FAIRE_image();
	image_charger(img,fichierImg);

	/* Creation de la table */
	table = FAIRE_image();
	image_charger(table,fichierTable);

	assert(image_give_hauteur(table) == 1);

	cTable = create_color_table(table);

    printf("Beginning inversion with trivial method...\n");
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

    temps = (double)(clock() - debut) / CLOCKS_PER_SEC;
    printf("Inversion completed successfully in %f s.\n", temps);

    strcpy(end, "_resultInversionByTrivial.ppm");
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