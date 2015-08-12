/*
 * BlockRenderer.h
 *
 *  Created on: 7. aug. 2015
 *      Author: larso
 */

#ifndef SRC_BLOCKRENDERER_H_
#define SRC_BLOCKRENDERER_H_

#include <SDL2/SDL.h>
#include "Block.h"
#include "Grid.h"

#define BLOCK_SIZE 16

struct _BlockRenderer;
typedef struct _BlockRenderer BlockRenderer;

void InitBlockTextures(SDL_Renderer* ren);
void CleanBlockTextures();

BlockRenderer* CreateBlockRenderer(SDL_Renderer* ren);
void DestroyBlockRenderer(BlockRenderer* bren);

void SetBlockOrigin(BlockRenderer* bren, int x, int y);
void GetBlockOrigin(BlockRenderer* bren, SDL_Point* dst);
void SetOrigin(BlockRenderer* bren, int x ,int y);
void GetOrigin(BlockRenderer* bren, SDL_Point* dst);

void SetBlockWindow(BlockRenderer* bren, SDL_Rect* window);
void GetBlockWindow(BlockRenderer* bren, SDL_Rect* dst);
void SetWindow(BlockRenderer* bren, SDL_Rect* window);
void GetWindow(BlockRenderer* bren, SDL_Rect* dst);

void RenderBlock(BlockRenderer* bren, Block* block);
void RenderBlocks(BlockRenderer* bren, Grid* blocks);

#endif /* SRC_BLOCKRENDERER_H_ */
