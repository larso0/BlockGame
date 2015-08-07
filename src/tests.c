/*
 * main.c
 *
 *  Created on: 5. aug. 2015
 *      Author: larso
 */

#include <stdio.h>
#include "Grid.h"
#include "Block.h"

void PrintBlock(Block* block, void* data)
{
    printf("(%d, %d) ", block->x, block->y);
    switch(block->type)
    {
    case DIRT_SURFACE_GRASS:
        printf(": DIRT_SURFACE_GRASS\n");
        break;
    default:
        printf(": OTHER_TYPE");
    }
}

int main(int argc, char** argv)
{
    Grid* grid = CreateGrid();

    Block block;
    block.type = DIRT_SURFACE_GRASS;
    block.x = 10;
    block.y = 10;

    AddBlock(grid, &block);

    block.x++;
    AddBlock(grid, &block);

    block.y--;
    block.x--;
    AddBlock(grid, &block);

    block.x = 15;
    block.y = -1;
    AddBlock(grid, &block);

    block.x++;
    block.y--;
    AddBlock(grid, &block);

    ForEachBlock(grid, &PrintBlock, NULL);

    DestroyGrid(grid);

    return 0;
}
