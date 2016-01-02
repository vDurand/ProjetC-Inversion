/**
* @file arbre.c
* @brief 
* @author Durand Valentin TP3 Informatique Promo 2018
* @date Decembre 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "arbre.h"

axis choose_sorting_axis(color_table cTable)
{
	axis axisChoice;
	axisChoice = (
				 color_table_get_max(cTable, red) - color_table_get_min(cTable, red)
				 >
				 color_table_get_max(cTable, green) - color_table_get_min(cTable, green)
				 ) 	
				 ? red : green;
	if(
		color_table_get_max(cTable, blue) - color_table_get_min(cTable, blue)
		>
		color_table_get_max(cTable, axisChoice) - color_table_get_min(cTable, axisChoice)
		)
		{axisChoice = blue;}
	return axisChoice;
}

int choose_axis_position(color_table cTable, axis sortingAxis)
{
	int positionAxis;
	positionAxis = color_table_get_nb_color(cTable)/2-1;
	while(cTable->table[sortingAxis][positionAxis] == cTable->table[sortingAxis][++positionAxis]);
	return positionAxis;
}

kdtree create_kdtree(color_table cTable, int seuil)
{
	color_table rightTable, leftTable;
	kdtree tree = malloc (sizeof (struct kdtree));
	
	tree->sortAxis = choose_sorting_axis(cTable);

	color_table_sort(cTable, tree->sortAxis);
	
	tree->colorTable = cTable;
	tree->positionAxis = choose_axis_position(cTable, tree->sortAxis);
	if(tree->positionAxis >= seuil || (color_table_get_nb_color(cTable) - tree->positionAxis) >= seuil){
		rightTable = color_table_duplicate(
										  cTable,
										  tree->positionAxis,
										  color_table_get_nb_color(cTable) - tree->positionAxis
										  );
		leftTable = color_table_duplicate(cTable, 0, tree->positionAxis);
		tree->right_son = create_kdtree(rightTable, seuil);
		tree->left_son = create_kdtree(leftTable, seuil);
	}
	return tree;
}
/*
void destroy_kdtree(kdtree){
	
}*/