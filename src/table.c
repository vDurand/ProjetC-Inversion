/**
* @file table.c
* @brief Fonctions pour les tables
* @author Durand Valentin TP3 Informatique Promo 2018
* @date Decembre 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "table.h"

color_table   create_color_table(image img)
{
	int i,j;
	int * pix;
	color_table colorTable = malloc (sizeof (struct color_table));

	colorTable->count = image_give_largeur(img);
	colorTable->owner = true;
	colorTable->table = malloc(3 * sizeof(int*));
	for(j = 0; j < 3; j++){
    	colorTable->table[j] = malloc(colorTable->count * sizeof(int));
  	}

	i = 0;
	image_debut(img);
	do
    {
    	pix = image_lire_pixel(img);
    	for(j = 0; j < 3; j++){
    		colorTable->table[j][i] = pix[j];
  		}
		i++;
    }
  	while(image_pixel_suivant(img));

  	return colorTable;
}

boolean       destroy_color_table(color_table cTable)
{
	int i;

  	cTable->count = 0;
  	if(cTable->owner){
  		for(i = 0; i < 3; i++){
	    	free(cTable->table[i]);
	  	}
	  	free(cTable->table);
	  	free(cTable);
  		return true;
  	}
  	for(i = 0; i < 3; i++){
    	cTable->table[i] = NULL;
  	}
  	free(cTable->table);
  	free(cTable);
  	return false;
}

color_table   color_table_duplicate(color_table cTable, int offset, int length)
{
	color_table subTable = malloc (sizeof (struct color_table));
	subTable->table = malloc(3 * sizeof(int*));
	subTable->table[red] = &cTable->table[red][offset];
	subTable->table[green] = &cTable->table[green][offset];
	subTable->table[blue] = &cTable->table[blue][offset];
	subTable->count = length;
	subTable->owner = false;
	return subTable;
}

void          color_table_get_color(color_table cTable, int index, color* foundColor)
{
	foundColor[red] = cTable->table[red][index];
	foundColor[green] = cTable->table[green][index];
	foundColor[blue] = cTable->table[blue][index];
}

int           color_table_get_nb_color(color_table cTable)
{
	return cTable->count;
}

void          color_table_sort(color_table cTable, axis sortingAxis)
{
	int i, j, k;
	long temp;

	for(i = 0; i < cTable->count; i++){
		for(j = cTable->count-1; j>i; j--){
			if(cTable->table[sortingAxis][j] < cTable->table[sortingAxis][j-1]){
				for (k = 0;k < 3; ++k){
					temp = cTable->table[k][j];
					cTable->table[k][j] = cTable->table[k][j-1];
					cTable->table[k][j-1] = temp;
				}
			}
		}
	}
}