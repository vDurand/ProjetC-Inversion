/**
 * @file arbre.c
 * @author Durand Valentin TP3 Informatique Promo 2018
 * @date Janvier 2016
 * @brief Fonctions pour les kd arbres
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"
#include "arbre.h"

/**
 * private
 * @name    choose_sorting_axis_by_max
 * @brief   La fonction choisi l axe de coupe avec la plus grande difference entre le min et le max
 * @param cTable table de couleur dont on cherche l axe de coupe
 * @return axis l axe de coupe choisi
 */
axis choose_sorting_axis_by_max(color_table cTable)
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

/**
 * private
 * @name    choose_sorting_axis_by_var
 * @brief   La fonction choisi l axe de coupe avec la plus grande variance
 * @param cTable table de couleur dont on cherche l axe de coupe
 * @return axis l axe de coupe choisi
 */
axis choose_sorting_axis_by_var(color_table cTable)
{
	int i, Rsum = 0, Gsum = 0, Bsum = 0, nbcolor;
	double Ravg, Gavg, Bavg;
	axis axisChoice;
	color temp[3];

	nbcolor = color_table_get_nb_color(cTable);

	for(i = 0; i < nbcolor; i++){
		color_table_get_color(cTable, i, temp);
		Rsum += temp[red];
		Gsum += temp[green];
		Bsum += temp[blue];
	}

	/* Moyennes de chaque axe */
	Ravg = Rsum / nbcolor;
	Gavg = Gsum / nbcolor;
	Bavg = Bsum / nbcolor;

	/* Les sum deviennent les sommes des carres des xi - m */
	Rsum = 0;
	Gsum = 0;
	Bsum = 0;

	for(i = 0; i < nbcolor; i++){
		color_table_get_color(cTable, i, temp);
		Rsum += (temp[red] - Ravg) * (temp[red] - Ravg);
		Gsum += (temp[green] - Gavg) * (temp[green] - Gavg);
		Bsum += (temp[blue] - Bavg) * (temp[blue] - Bavg);
	}

	/* Variance de chaque axe */
	Rsum /= nbcolor;
	Gsum /= nbcolor;
	Bsum /= nbcolor;

	/* Choix de l axe en fonction de la plus grande variance */
	if(Rsum > Gsum)
		if(Rsum > Bsum)
			axisChoice = red;
		else
			axisChoice = blue;
	else
		if (Gsum > Bsum)
			axisChoice = green;
		else
			axisChoice = blue;

	return axisChoice;
}

/**
 * private
 * @name    choose_axis_position
 * @brief   La fonction trouve le plan de coupe
 * @param cTable table de couleur dont on cherche le plan de coupe
 * @param sortingAxis l axe de coupe auquel le plan est orthogonal
 * @return int la position dans la table de couleur de la premiere couleur superieure au plan de coupe
 */
int choose_axis_position(color_table cTable, axis sortingAxis)
{
	int temp, i;

	temp = color_table_get_nb_color(cTable)/2-1;
	i = temp+1;

	/* On boucle tant qu on est toujours sur la meme couleur */
	/* afin d avoir des couleurs differentes des 2 cotes du plan de coupe */
	while(i < color_table_get_nb_color(cTable)
		&&
		cTable->table[sortingAxis][temp] == cTable->table[sortingAxis][i])
		i++;

	return i;
}

/**
 * public
 * @name    create_kdtree
 * @brief   La fonction cree le kd arbre de tri
 * @param cTable table de couleur a decouper en kd arbre
 * @param seuil le nombre minimum de couleur dans une feuille de l arbre
 * @return kdtree pointer sur la racine de l arbre
 */
kdtree create_kdtree(color_table cTable, int seuil)
{
	color_table rightTable, leftTable;
	kdtree tree = malloc (sizeof (struct kdtree));
	cutting_plane cplane = malloc (sizeof (struct cutting_plane));
	
	tree->sortAxis = choose_sorting_axis_by_var(cTable);

	color_table_sort(cTable, tree->sortAxis);
	
	tree->colorTable = cTable;

	/* Position de la premiere couleur au dessus du plan de coupe */
	cplane->position = choose_axis_position(cTable, tree->sortAxis);

	/* Valeur ou passe le plan de coupe */
	/* Equivaut a la moyenne entre la composante de l axe de coupe */
	/* de la couleur juste en dessous du plan et celle juste au dessus */
	cplane->value = (cTable->table[tree->sortAxis][cplane->position]
					+ cTable->table[tree->sortAxis][cplane->position-1])
					/2;

	tree->cuttingPlane = cplane;

	/* On coupe si le nombre de couleurs au dessus du plan de coupe */
	/* et le nombre de couleur en dessous sont tous deux superieur au seuil */
	if(tree->cuttingPlane->position >= seuil || (color_table_get_nb_color(cTable) - tree->cuttingPlane->position) >= seuil){
		rightTable = color_table_duplicate(
										  cTable,
										  tree->cuttingPlane->position,
										  color_table_get_nb_color(cTable) - tree->cuttingPlane->position
										  );
		leftTable = color_table_duplicate(cTable, 0, tree->cuttingPlane->position);
		tree->right_son = create_kdtree(rightTable, seuil);
		tree->left_son = create_kdtree(leftTable, seuil);
	}
	else{
		tree->cuttingPlane->position = -1;
		tree->cuttingPlane->value = -1;
		tree->sortAxis = -1;
	}

	return tree;
}

/**
 * public
 * @name    destroy_kdtree
 * @brief   La fonction supprime le kd arbre et ses fils
 * @param tree l arbre a detruire
 */
void destroy_kdtree(kdtree tree){
	if(tree == NULL)
		return;
	destroy_kdtree(tree->right_son);
	destroy_kdtree(tree->left_son);
	destroy_color_table(tree->colorTable);
	free(tree->cuttingPlane);
	free(tree);
}

/**
 * private
 * @name    get_distance_between_colors
 * @brief   La fonction calcul la distance entre 2 couleurs
 * @param a une couleur sous forme d un pointer vers tableau des 3 composantes
 * @param b une couleur sous forme d un pointer vers tableau des 3 composantes
 * @return double la distance entre a et b
 */
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

/**
 * private
 * @name    search_nearest_color_in_node
 * @brief   La fonction cherche la couleur la plus proche dans un noeud
 * @param tree le noeud dans lequel on fait la recherche
 * @param inputColor la couleur d origine dont on cherche la plus proche
 * @param outputColor la couleur la plus proche trouvee
 */
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

/**
 * public
 * @name    kdtree_get_nearest_color
 * @brief   La fonction cherche la couleur la plus proche dans tout l arbre
 * @param tree la racine de l arbre de recherche
 * @param inputColor la couleur d origine dont on cherche la plus proche
 * @param outputColor la couleur la plus proche trouvee
 */
void kdtree_get_nearest_color(kdtree tree, color *inputColor, color *outputColor)
{
	color colorOnPlane[3];

	/* On est dans une feuille donc on cherche la couleur la plus proche */
	if(tree->left_son == NULL){
		search_nearest_color_in_node(tree, inputColor, outputColor);
		return;
	}

	/* La couleur cherchee est sous le plan de coupe donc on cherche dans le fils gauche */
	if(inputColor[tree->sortAxis] <= tree->cuttingPlane->value)
		kdtree_get_nearest_color(tree->left_son, inputColor, outputColor);

	/* La couleur cherchee est au dessus du plan de coupe donc on cherche dans le fils droit */
	if(inputColor[tree->sortAxis] > tree->cuttingPlane->value)
		kdtree_get_nearest_color(tree->right_son, inputColor, outputColor);

	/* On projette la couleur recherchee sur le plan de coupe */
	colorOnPlane[red] = inputColor[red];
	colorOnPlane[green] = inputColor[green];
	colorOnPlane[blue] = inputColor[blue];
	colorOnPlane[tree->sortAxis] = tree->cuttingPlane->value;

	/* Si la distance entre la projection et la couleur cherchee est inferieure */
	/* a la distance entre la couleur trouvee dans la feuille et la couleur cherchee */
	/* alors c est que la sphere autour de la couleur cherchee intersecte la plan de coupe */
	/* donc on recherche a nouveau dans ce noeud non coupe */
	if(get_distance_between_colors(inputColor, colorOnPlane) < get_distance_between_colors(inputColor, outputColor)){
		search_nearest_color_in_node(tree, inputColor, outputColor);
	}
}