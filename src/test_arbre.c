/**
* @file test_table.c
* @brief test des differents fonctions de table.c
* @author Durand Valentin TP3 Informatique Promo 2018
* @date Decembre 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "arbre.h"

void printTree(kdtree t){
	int i;
	if(t == NULL)
      return;
    printf("%d : %d\n-----\n",color_table_get_nb_color(t -> colorTable), t -> sortAxis);
    for (i = 0; i < color_table_get_nb_color(t -> colorTable); ++i)
    {
    	printf("%d | %d | %d\n", t -> colorTable->table[0][i], t -> colorTable->table[1][i], t -> colorTable->table[2][i]);
    }
 	printf("-----\nl:");
    printTree(t -> left_son);
    printf("r:");
    printTree(t ->right_son);
    printf("\n");
}

int main(int argc, char *argv[])
{
	color_table cTable;
	kdtree tree;
	char *fichier = argv[1];

	/* Creation image */
	image input = FAIRE_image();
	image_charger(input,fichier);

	/* Creation de la table */
	cTable = create_color_table(input);

	tree = create_kdtree(cTable, 3);

	printTree(tree);

	return 0;
}