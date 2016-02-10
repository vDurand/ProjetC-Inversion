/**
 * @file arbre.h
 * @author Durand Valentin TP3 Informatique Promo 2018
 * @date Janvier 2016
 * @brief Structures et headers des fonctions pour les kd arbres
 */

#ifndef __KDTREE_HH__
#define __KDTREE_HH__

#include "table.h"

/**
 * @typedef cutting_plane
 * @brief pointeur de structure cutting_plane
 */
typedef struct cutting_plane *cutting_plane;

/** 
 * @struct cutting_plane
 * @brief structure permettant de stocker les donnes du plan de coupe
 * @var cutting_plane::position entier position dans la table de la couleur juste au dessus du plan de coupe
 * @var cutting_plane::value entier valeur au passe le plan de coupe c est a dire la moyenne entre la composante de l axe de coupe de la couleur juste sous le plan et celle juste au dessus
 */
struct cutting_plane
{
	int position;
	int value;
};

/**
 * @typedef kdtree
 * @brief pointeur de structure kdtree
 */
typedef  struct kdtree *kdtree;

/** 
 * @struct kdtree
 * @brief structure permettant de stocker les donnes des noeuds de l arbre
 * @var cutting_plane::colorTable la table de couleur correspondant au noeud
 * @var cutting_plane::left_son pointeur sur le noeud fils gauche
 * @var cutting_plane::right_son pointeur sur le noeud fils droit
 * @var cutting_plane::sortAxis l axe de coupe RGB
 * @var cutting_plane::cuttingPlane pointeur sur structure cutting_plane
 */
struct kdtree
{
	color_table colorTable;
	struct kdtree *left_son, *right_son;
	axis sortAxis;
	cutting_plane cuttingPlane;
};

/**
 * @name    create_kdtree
 * @brief   La fonction cree le kd arbre de tri
 * @param cTable table de couleur a decouper en kd arbre
 * @param seuil le nombre minimum de couleur dans une feuille de l arbre
 * @return kdtree pointer sur la racine de l arbre
 */
kdtree create_kdtree(color_table,int);

/**
 * @name    destroy_kdtree
 * @brief   La fonction supprime le kd arbre et ses fils
 * @param tree l arbre a detruire
 */
void   destroy_kdtree(kdtree);

/**
 * @name    kdtree_get_nearest_color
 * @brief   La fonction cherche la couleur la plus proche dans tout l arbre
 * @param tree la racine de l arbre de recherche
 * @param inputColor la couleur d origine dont on cherche la plus proche
 * @param outputColor la couleur la plus proche trouvee
 */
void   kdtree_get_nearest_color(kdtree,color*, color*);

#endif