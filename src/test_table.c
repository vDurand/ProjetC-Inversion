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

int main(int argc, char *argv[])
{
	int i;
	color_table cTable;
	char *fichier = argv[1];
	image input = FAIRE_image();
	image_charger(input,fichier);
	cTable = create_color_table(input);
	for (i = 0; i < cTable->count; i++){
		printf("%d | %d | %d\n", cTable->table[0][i], cTable->table[1][i], cTable->table[2][i]);
	}
	return 0;
}