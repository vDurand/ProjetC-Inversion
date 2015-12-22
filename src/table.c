/**
* @file table.c
* @brief 
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
  	cTable->table = NULL;
  	free(cTable);
  	return false;
}

color_table   color_table_duplicate(color_table cTable, int offset, int length)
{
	color_table subTable = malloc (sizeof (struct color_table));
	subTable->table = cTable->table;
	subTable->table[0] = &cTable->table[0][offset];
	subTable->table[1] = &cTable->table[1][offset];
	subTable->table[2] = &cTable->table[2][offset];
	subTable->count = length;
	subTable->owner = false;
	return subTable;
}
/*
void          color_table_get_color(color_table cTable, int a, color* b)
{

}

int           color_table_get_nb_color(color_table cTable)
{

}

void          color_table_sort(color_table cTable, axis a){

}*/