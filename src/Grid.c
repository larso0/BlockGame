/*
 * Grid.c
 *
 *  Created on: 5. aug. 2015
 *      Author: larso
 */

#include "Grid.h"
#include <stdlib.h>
#include <stdbool.h>

typedef struct _GridNode
{
    Block block;
    struct _GridNode* left;
    struct _GridNode* right;
} GridNode;

struct _Grid
{
    GridNode* root;
};

bool PointLessThan(int ax, int ay, int bx, int by)
{
	return (ax < bx) ? true : ((ax == bx) ? (ay < by) : false);
}

bool PointEquals(int ax, int ay, int bx, int by)
{
    return (ax == bx) && (ay == by);
}

GridNode* CreateGridNode(Block* block)
{
    GridNode* node = malloc(sizeof(GridNode));
    if(node)
    {
        node->block.type = block->type;
        node->block.x = block->x;
        node->block.y = block->y;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

Grid* CreateGrid()
{
    Grid* grid = malloc(sizeof(Grid));
    if(grid)
    {
        grid->root = NULL;
    }
    return grid;
}

void DestroyGridRec(GridNode* root)
{
    if(root)
    {
        DestroyGridRec(root->left);
        DestroyGridRec(root->right);
        free(root);
    }
}

void DestroyGrid(Grid* grid)
{
    DestroyGridRec(grid->root);
    free(grid);
}

void AddBlockRec(GridNode* root, Block* block)
{
    if(PointLessThan(block->x, block->y, root->block.x, root->block.y))
    {
        if(root->left) AddBlockRec(root->left, block);
        else root->left = CreateGridNode(block);
    }
    else if(!PointEquals(block->x, block->y, root->block.x, root->block.y))
    {
        if(root->right) AddBlockRec(root->right, block);
        else root->right = CreateGridNode(block);
    }
}

void AddBlock(Grid* grid, Block* block)
{
    if(grid && block)
    {
        if(grid->root) AddBlockRec(grid->root, block);
        else grid->root = CreateGridNode(block);
    }
}

GridNode* RemoveBlockRec(GridNode* n, int x, int y)
{
	if(n == NULL) return NULL;
	if(PointEquals(x, y, n->block.x, n->block.y))
	{
		if(! (n->left || n->right))
		{
			free(n);
			return NULL;
		}
		else if(! n->left)
		{
			GridNode* tmp = n->right;
			free(n);
			return tmp;
		}
		else if(! n->right)
		{
			GridNode* tmp = n->left;
			free(n);
			return tmp;
		}
		else
		{
			GridNode* tmp = n->right;
			while(tmp->left) tmp = tmp->left;
			n->block.type = tmp->block.type;
			n->block.x = tmp->block.x;
			n->block.y = tmp->block.y;
			n->right = RemoveBlockRec(n->right, tmp->block.x, tmp->block.y);
			return n;
		}
	}
	else if(PointLessThan(x, y, n->block.x, n->block.y))
	{
		n->left = RemoveBlockRec(n->left, x, y);
		return n;
	}
	else
	{
		n->right = RemoveBlockRec(n->right, x, y);
		return n;
	}
}

void RemoveBlock(Grid* grid, int x, int y)
{
    if(grid)
    {
    	grid->root = RemoveBlockRec(grid->root, x, y);
    }
}

Block* GetBlock(Grid* grid, int x, int y)
{
    Block* block = NULL;
    if(grid)
    {
        GridNode* tmp = grid->root;
        while(tmp)
        {
            if(PointEquals(x, y, tmp->block.x, tmp->block.y))
            {
                block = &tmp->block;
                tmp = NULL;
            }
            else if(PointLessThan(x, y, tmp->block.x, tmp->block.y))
            {
                tmp = tmp->left;
            }
            else
            {
                tmp = tmp->right;
            }
        }
    }
    return block;
}

void ForEachBlockRec(GridNode* root, void(*f)(Block*, void*), void* data)
{
    if(root)
    {
        ForEachBlockRec(root->left, f, data);
        f(&root->block, data);
        ForEachBlockRec(root->right, f, data);
    }
}

void ForEachBlock(Grid* grid, void (*f)(Block*, void*), void* data)
{
    if(grid)
    {
        ForEachBlockRec(grid->root, f, data);
    }
}
