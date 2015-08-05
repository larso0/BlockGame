/*
 * Grid.h
 *
 *  Created on: 5. aug. 2015
 *      Author: larso
 */

#ifndef GRID_H_
#define GRID_H_

#include "Block.h"

struct _Grid;

typedef struct _Grid Grid;

Grid* CreateGrid();
void DestroyGrid(Grid* grid);

void AddBlock(Grid* grid, Block* block);
void RemoveBlock(Grid* grid, int x, int y);
Block* GetBlock(Grid* grid, int x, int y);

void ForEachBlock(Grid* grid, void (*f)(Block*, void*), void* data);

#endif /* GRID_H_ */
