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
    if ( ax < bx )
        return true;
    if ( bx < ax )
        return false;
    if ( ay < by )
        return true;
    if ( by < ay )
        return false;
    return false;
}

bool PointEquals(int ax, int ay, int bx, int by)
{
    return ax == bx && ay == by;
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

GridNode* RemoveBlockRec(GridNode* root, int x, int y)
{
    if(root)
    {
        if(PointEquals(x, y, root->block.x, root->block.y))
        {
            if(root->left == NULL)
            {
                GridNode* tmp = root->right;
                free(root);
                return tmp;
            }
            else if(root->right == NULL)
            {
                GridNode* tmp = root->left;
                free(root);
                return tmp;
            }
            GridNode* tmp = root;
            while(tmp->left) tmp = tmp->left;
            root->block.x = tmp->block.x;
            root->block.y = tmp->block.y;
            root->block.type = tmp->block.type;
            root->right = RemoveBlockRec(root->right, tmp->block.x, tmp->block.y);
        }
        else if(PointLessThan(x, y, root->block.x, root->block.y))
        {
            root->left = RemoveBlockRec(root->left, x, y);
        }
        else
        {
            root->right = RemoveBlockRec(root->right, x, y);
        }
    }
    return root;
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
