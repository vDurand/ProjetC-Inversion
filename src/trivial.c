/**
 * @file trivial.c
 * @brief Inversion d une image par une table de couleur en utilisant une methode triviale
 * @author Durand Valentin TP3 Informatique Promo 2018
 * @date Decembre 2015
 * Avec cette methode on calcule la distance entre chaque pixel de l image et toute les couleurs de la table de couleur successivement
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

    /* Recuperation des noms des fichiers image et table passes en parametres */
	fichierImg = argv[1];
	fichierTable = argv[2];

    /* On initialise un pointer char juste avant .ppm dans le nom de l image */
    end = fichierImg + strlen(fichierImg) - 4;

	/* Creation image */
	img = FAIRE_image();
	image_charger(img,fichierImg);

	/* Creation de la table */
	table = FAIRE_image();
	image_charger(table,fichierTable);

    /* On verifie que la table de couleur a bien une hauteur de 1 */
	assert(image_give_hauteur(table) == 1);

	cTable = create_color_table(table);

    /* On debute un timer pour le temps d execution */
    printf("Beginning inversion with trivial method...\n");
    debut = clock();

	image_debut(img);
	do
    {
    	pix = image_lire_pixel(img);
        closest[red] = cTable->table[red][0];
    	closest[green] = cTable->table[green][0];
    	closest[blue] = cTable->table[blue][0];

        /* On calcule la distance entre une couleur de l image et chaque couleur de la table */
        /* Et on remplace cette couleur par celle dont la distance est la plus faible dans la table */
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

    /* On arrete le timer */
    temps = (double)(clock() - debut) / CLOCKS_PER_SEC;
    printf("Inversion completed successfully in %f s.\n", temps);

    /* On sauvegarde l image resultat */
    strcpy(end, "_resultInversionByTrivial.ppm");
    image_sauvegarder(img, fichierImg);

    printf("Result picture saved : %s\n", fichierImg);

    /* On ouvre l image */
    exec = malloc(strlen(fichierImg) + 12);
    strcpy(exec, "gnome-open ");
    strcat(exec, fichierImg);
    system(exec);
    free(exec);

	destroy_color_table(cTable);

	return 0;
}