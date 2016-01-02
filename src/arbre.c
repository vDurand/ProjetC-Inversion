/**
* @file arbre.c
* @brief 
* @author Durand Valentin TP3 Informatique Promo 2018
* @date Decembre 2015
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
	int temp, i;
	temp = color_table_get_nb_color(cTable)/2-1;
	i = temp+1;
	while(i < color_table_get_nb_color(cTable)
		&&
		cTable->table[sortingAxis][temp] == cTable->table[sortingAxis][i])
		i++;
	return i;
}

kdtree create_kdtree(color_table cTable, int seuil)
{
	color_table rightTable, leftTable;
	kdtree tree = malloc (sizeof (struct kdtree));
	
	tree->sortAxis = choose_sorting_axis(cTable);

	color_table_sort(cTable, tree->sortAxis);
	
	tree->colorTable = cTable;
	tree->cuttingPlane.position = choose_axis_position(cTable, tree->sortAxis);
	tree->cuttingPlane.value = (cTable->table[tree->sortAxis][choose_axis_position(cTable, tree->sortAxis)]
								+ cTable->table[tree->sortAxis][choose_axis_position(cTable, tree->sortAxis)-1])
								/2;
	if(tree->cuttingPlane.position >= seuil || (color_table_get_nb_color(cTable) - tree->cuttingPlane.position) >= seuil){
		rightTable = color_table_duplicate(
										  cTable,
										  tree->cuttingPlane.position,
										  color_table_get_nb_color(cTable) - tree->cuttingPlane.position
										  );
		leftTable = color_table_duplicate(cTable, 0, tree->cuttingPlane.position);
		tree->right_son = create_kdtree(rightTable, seuil);
		tree->left_son = create_kdtree(leftTable, seuil);
	}
	else{
		tree->cuttingPlane.position = -1;
		tree->cuttingPlane.value = -1;
		tree->sortAxis = -1;
	}
	return tree;
}

void destroy_kdtree(kdtree tree){
	if(tree == NULL)
		return;
	destroy_kdtree(tree->right_son);
	destroy_kdtree(tree->left_son);
	destroy_color_table(tree->colorTable);
	free(tree);
}

double get_distance_between_colors(color *a, color *b)
{
	return sqrt(
				pow(a[red]-b[red], 2)
				+
				pow(a[green]-b[green], 2)
				+
				pow(a[blue]-b[blue], 2)
				);		
}

void search_nearest_color_in_node(kdtree tree, color *inputColor, color *outputColor)
{
	int i;
	color temp[3];

	color_table_get_color(tree->colorTable, 0, outputColor);
	for(i = 1; i < color_table_get_nb_color(tree->colorTable); i++){
		color_table_get_color(tree->colorTable, i, temp);
		if(get_distance_between_colors(inputColor, temp)
			<
			get_distance_between_colors(inputColor, outputColor)
			)
		{
			outputColor[0] = temp[0];
			outputColor[1] = temp[1];
			outputColor[2] = temp[2];
		}
	}
}

void kdtree_get_nearest_color(kdtree tree, color *inputColor, color *outputColor)
{
	color colorOnPlane[3];
	if(tree->left_son == NULL){
		search_nearest_color_in_node(tree, inputColor, outputColor);
		return;
	}

	if(inputColor[tree->sortAxis] <= tree->cuttingPlane.value)
		kdtree_get_nearest_color(tree->left_son, inputColor, outputColor);

	if(inputColor[tree->sortAxis] > tree->cuttingPlane.value)
		kdtree_get_nearest_color(tree->right_son, inputColor, outputColor);

	colorOnPlane[red] = inputColor[red];
	colorOnPlane[green] = inputColor[green];
	colorOnPlane[blue] = inputColor[blue];
	colorOnPlane[tree->sortAxis] = tree->cuttingPlane.value;
	if(get_distance_between_colors(inputColor, colorOnPlane) < get_distance_between_colors(inputColor, outputColor)){
		search_nearest_color_in_node(tree, inputColor, outputColor);
	}
}