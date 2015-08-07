/*
 * BlockRenderer.c
 *
 *  Created on: 7. aug. 2015
 *      Author: larso
 */

#include "BlockRenderer.h"

SDL_Texture* textures[23];

void InitBlockTextures(SDL_Renderer* ren)
{
	SDL_Surface* surface = NULL;

	surface = SDL_LoadBMP("textures/UNKNOWN.bmp");
	textures[UNKNOWN] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/DIRT.bmp");
	textures[DIRT] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/DIRT_SURFACE.bmp");
	textures[DIRT_SURFACE] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/DIRT_SURFACE_GRASS.bmp");
	textures[DIRT_SURFACE_GRASS] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/DIRT_SURFACE_SNOW.bmp");
	textures[DIRT_SURFACE_SNOW] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/DIRT_CEILING.bmp");
	textures[DIRT_CEILING] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/DIRT_CEILING_ICE.bmp");
	textures[DIRT_CEILING_ICE] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/STONE.bmp");
	textures[STONE] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/STONE_SURFACE.bmp");
	textures[STONE_SURFACE] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/STONE_SURFACE_MOSS.bmp");
	textures[STONE_SURFACE_MOSS] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/STONE_SURFACE_SNOW.bmp");
	textures[STONE_SURFACE_SNOW] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/STONE_CEILING.bmp");
	textures[STONE_CEILING] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/STONE_CEILING.bmp");
	textures[STONE_CEILING] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/STONE_CEILING_ICE.bmp");
	textures[STONE_CEILING_ICE] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/ORE_IRON.bmp");
	textures[ORE_IRON] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/WATER.bmp");
	textures[WATER] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/WATER_FALLING_1.bmp");
	textures[WATER_FALLING_1] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/WATER_FALLING_2.bmp");
	textures[WATER_FALLING_2] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/ICE.bmp");
	textures[ICE] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/ICE_SURFACE.bmp");
	textures[ICE_SURFACE] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/ICE_SURFACE_SNOW.bmp");
	textures[ICE_SURFACE_SNOW] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/ICE_CEILING.bmp");
	textures[ICE_CEILING] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/TREE.bmp");
	textures[TREE] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("textures/LEAVES.bmp");
	textures[LEAVES] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
}

void CleanBlockTextures()
{
	int i;
	for(i = 0; i < 23; i++)
	{
		SDL_DestroyTexture(textures[i]);
	}
}

struct _BlockRenderer
{
	SDL_Renderer* ren;
	int block_x, block_y;
	int pixel_x, pixel_y;
};

BlockRenderer* CreateBlockRenderer(SDL_Renderer* ren)
{
	BlockRenderer* bren = malloc(sizeof(BlockRenderer));
	if(bren)
	{
		bren->ren = ren;
		bren->block_x = 0;
		bren->block_y = 0;
		bren->pixel_x = 0;
		bren->pixel_y = 0;
	}
	return bren;
}

void DestroyBlockRenderer(BlockRenderer* bren)
{
	free(bren);
}

void SetBlockOrigin(BlockRenderer* bren, int x, int y)
{
	if(bren)
	{
		bren->block_x = x;
		bren->block_y = y;
	}
}

void SetPixelOrigin(BlockRenderer* bren, int x ,int y)
{
	if(bren)
	{
		bren->pixel_x = x;
		bren->pixel_y = y;
	}
}

void RenderBlock(BlockRenderer* bren, Block* block)
{
	if(bren && block)
	{
		SDL_Rect pos;
		pos.w = pos.h = BLOCK_SIZE;
		pos.x = (bren->block_x + block->x)*BLOCK_SIZE + bren->pixel_x;
		pos.y = (bren->block_y + block->y)*BLOCK_SIZE + bren->pixel_y;
		SDL_RenderCopy(bren->ren, textures[block->type], NULL, &pos);
	}
}

void RenderBlockForAll(Block* block, void* bren)
{
	RenderBlock((BlockRenderer*)bren, block);
}

void RenderBlocks(BlockRenderer* bren, Grid* blocks)
{
	ForEachBlock(blocks, &RenderBlockForAll, (void*)bren);
}
