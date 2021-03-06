/**
 * @file table.c
 * @author Durand Valentin TP3 Informatique Promo 2018
 * @date Decembre 2015
 * @brief Fonctions pour les tables de couleurs
 */

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "table.h"

/**
 * public
 * @name    create_color_table
 * @brief   La fonction cree une table a partir d’une image composee d’une seule ligne.
 * @param img image a partir de laquelle on cree la table de couleur
 * @return colorTable la table de couleur cree
 * Il faut donc allouer le pointeur, initialiser la longueur et remplir le tableau.
 * Le champ owner est positionne a true dans ce cas.
 */
color_table create_color_table(image img)
{
	int i,j;
	int * pix;
	color_table colorTable = malloc (sizeof (struct color_table));

	assert(image_give_largeur(img)>0);

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

/**
 * public
 * @name    destroy_color_table
 * @brief   La fonction supprime une table de couleur.
 * @param cTable la table de couleur a supprimer
 * @retval TRUE si libere avec owner
 * @retval FALSE si libere sans owner
 * Le pointeur ne doit etre libere que si owner est positionne a true.
 * La structure contenant la table doit par contre etre liberee dans tous les cas.
 */
boolean destroy_color_table(color_table cTable)
{
	int i;

	assert(cTable != NULL);

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

/**
 * public
 * @name    color_table_duplicate
 * @brief   La fonction cree une sous table.
 * @param cTable table de couleur mere
 * @param offset indice de debut de la sous table
 * @param length longueur de la sous table
 * @return subTable la sous table de couleur cree
 * Cette fonction initialise son pointeur a partir de celui de la table principale sans faire d’allocation.
 * Le champ owner doit etre positionne a false.
 */
color_table color_table_duplicate(color_table cTable, int offset, int length)
{
	color_table subTable = malloc (sizeof (struct color_table));

	assert(cTable != NULL);
	assert(offset >= 0);
	assert(length > 0);
	assert(length+offset <= cTable->count);

	subTable->table = malloc(3 * sizeof(int*));
	
	subTable->table[red] = &cTable->table[red][offset];
	subTable->table[green] = &cTable->table[green][offset];
	subTable->table[blue] = &cTable->table[blue][offset];

	subTable->count = length;
	subTable->owner = false;

	return subTable;
}

/**
 * public
 * @name    color_table_get_color
 * @brief   La fonction donne la couleur rgb a une position precise dans la table de couleur.
 * @param cTable table de couleur dans laquel on veut trouver la couleur
 * @param index position dans la table ou on veut la couleur
 * @param foundColor tableau 1D de taille 3 stockant la couleur rgb trouvee
 * @return rien
 */
void color_table_get_color(color_table cTable, int index, color* foundColor)
{
	assert(cTable != NULL);
	assert(index >= 0);
	assert(index <= cTable->count-1);
	assert(foundColor != NULL);

	foundColor[red] = cTable->table[red][index];
	foundColor[green] = cTable->table[green][index];
	foundColor[blue] = cTable->table[blue][index];
}

/**
 * public
 * @name    color_table_get_nb_color
 * @brief   La fonction donne le nombre de couleurs dans la table de couleur.
 * @param cTable table dont on veut le nombre de couleur
 * @return int le nombre de couleur
 */
int color_table_get_nb_color(color_table cTable)
{
	return cTable->count;
}

/**
 * public
 * @name    color_table_sort
 * @brief   La fonction trie les elements d’une table de couleur par ordre croissant en fonction de leurs coodonnees sur un axe
 * @param cTable table de couleur a trier
 * @param sortingAxis axe RGB utilise pour le tri
 * @return rien
 */
void color_table_sort(color_table cTable, axis sortingAxis)
{
	int i, j, k;
	long temp;

	assert(cTable != NULL);
	assert(sortingAxis >= 0 && sortingAxis < 3);

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

/**
 * public
 * @name    color_table_get_min
 * @brief   La fonction retourne la couleur la plus faible pour un axe rgb donné
 * @param cTable table de couleur dont on cherche le minimum
 * @param sortingAxis axe RGB utilise pour chercher le minimum
 * @return la couleur la plus petite trouvee
 */
color color_table_get_min(color_table cTable, axis sortingAxis)
{
	int i, min;

	min = cTable->table[sortingAxis][0];
	for (i = 1; i < cTable->count; ++i){
		if(cTable->table[sortingAxis][i] < min)
			min = cTable->table[sortingAxis][i];
	}

	return min;
}

/**
 * public
 * @name    color_table_get_max
 * @brief   La fonction retourne la couleur la plus grande pour un axe rgb donné
 * @param cTable table de couleur dont on cherche le maximum
 * @param sortingAxis axe RGB utilise pour chercher le maximum
 * @return la couleur la plus grande trouvee
 */
color color_table_get_max(color_table cTable, axis sortingAxis)
{
	int i, max;

	max = cTable->table[sortingAxis][0];
	for (i = 1; i < cTable->count; ++i){
		if(cTable->table[sortingAxis][i] > max)
			max = cTable->table[sortingAxis][i];
	}

	return max;
}