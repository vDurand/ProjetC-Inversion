/**
 * @file table.h
 * @author Durand Valentin TP3 Informatique Promo 2018
 * @date Decembre 2015
 * @brief Structures et headers des fonctions pour les tables de couleurs
 */

#ifndef __TABLE_HH__
#define __TABLE_HH__

/**
 * @typedef axis
 * @brief une axe est une compsante RGB d une couleur
 * 0 pour l’axe rouge, 1 pour le vert, et 2 pour le bleu
 */
typedef enum {red,green,blue} axis;

/**
 * @typedef color
 * @brief chaque valeur de la composante d une couleur est un entier
 */
typedef int color;

/**
 * @typedef boolean
 * @brief booleen vrai faux
 */
typedef enum {false,true} boolean;

/**
 * @typedef color_table
 * @brief pointeur de structure color_table
 */
typedef struct color_table *color_table;

/** 
 * @struct color_table
 * @brief structure permettant de stocker les donnes d une table de couleur
 * @var color_table::table pointeur de pointeur vers un tableau 2D comprennant toutes les couleurs sur leurs 3 axes
 * @var color_table::owner booleen vrai si la table n est pas une sous table faux sinon
 * @var color_table::count nombre de couleur dans la table
 */
struct color_table {
   color**  table;
   boolean  owner;
   int   count;
};

/**
 * @name    create_color_table
 * @brief   La fonction cree une table a partir d’une image composee d’une seule ligne.
 * @param img image a partir de laquelle on cree la table de couleur
 * @return colorTable la table de couleur cree
 * Il faut donc allouer le pointeur, initialiser la longueur et remplir le tableau.
 * Le champ owner est positionne a true dans ce cas.
 */
color_table   create_color_table(image);

/**
 * @name    destroy_color_table
 * @brief   La fonction supprime une table de couleur.
 * @param cTable la table de couleur a supprimer
 * @retval TRUE si libere avec owner
 * @retval FALSE si libere sans owner
 * Le pointeur ne doit etre libere que si owner est positionne a true.
 * La structure contenant la table doit par contre etre liberee dans tous les cas.
 */
boolean       destroy_color_table(color_table);

/**
 * @name    color_table_duplicate
 * @brief   La fonction cree une sous table.
 * @param cTable table de couleur mere
 * @param offset indice de debut de la sous table
 * @param length longueur de la sous table
 * @return subTable la sous table de couleur cree
 * Cette fonction initialise son pointeur a partir de celui de la table principale sans faire d’allocation.
 * Le champ owner doit etre positionne a false.
 */
color_table   color_table_duplicate(color_table,int,int);

/**
 * @name    color_table_get_color
 * @brief   La fonction donne la couleur rgb a une position precise dans la table de couleur.
 * @param cTable table de couleur dans laquel on veut trouver la couleur
 * @param index position dans la table ou on veut la couleur
 * @param foundColor tableau 1D de taille 3 stockant la couleur rgb trouvee
 * @return rien
 */
void          color_table_get_color(color_table,int,color*);

/**
 * @name    color_table_get_nb_color
 * @brief   La fonction donne le nombre de couleurs dans la table de couleur.
 * @param cTable table dont on veut le nombre de couleur
 * @return int le nombre de couleur
 */
int           color_table_get_nb_color(color_table);

/**
 * @name    color_table_sort
 * @brief   La fonction trie les elements d’une table de couleur par ordre croissant en fonction de leurs coodonnees sur un axe
 * @param cTable table de couleur a trier
 * @param sortingAxis axe RGB utilise pour le tri
 * @return rien
 * 0 pour l’axe rouge, 1 pour le vert, et 2 pour le bleu
 */
void          color_table_sort(color_table,axis);

/**
 * @name    color_table_get_min
 * @brief   La fonction retourne la couleur la plus faible pour un axe rgb donné
 * @param cTable table de couleur dont on cherche le minimum
 * @param sortingAxis axe RGB utilise pour chercher le minimum
 * @return la couleur la plus petite trouvee
 */
color         color_table_get_min(color_table,axis);

/**
 * @name    color_table_get_max
 * @brief   La fonction retourne la couleur la plus grande pour un axe rgb donné
 * @param cTable table de couleur dont on cherche le maximum
 * @param sortingAxis axe RGB utilise pour chercher le maximum
 * @return la couleur la plus grande trouvee
 */
color         color_table_get_max(color_table,axis);

#endif