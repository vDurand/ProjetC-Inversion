#ifndef __KDTREE_HH__
#define __KDTREE_HH__

#include "table.h"

typedef  struct kdtree *kdtree;

struct kdtree
{
	color_table colorTable;
	struct kdtree *left_son, *right_son;
	axis sortAxis;
	int positionAxis;
};

kdtree create_kdtree(color_table,int);
void   destroy_kdtree(kdtree);

#endif