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

	surface = SDL_LoadBMP("../textures/UNKNOWN.bmp");
	textures[UNKNOWN] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/DIRT.bmp");
	textures[DIRT] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/DIRT_SURFACE.bmp");
	textures[DIRT_SURFACE] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/DIRT_SURFACE_GRASS.bmp");
	textures[DIRT_SURFACE_GRASS] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/DIRT_SURFACE_SNOW.bmp");
	textures[DIRT_SURFACE_SNOW] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/DIRT_CEILING.bmp");
	textures[DIRT_CEILING] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/DIRT_CEILING_ICE.bmp");
	textures[DIRT_CEILING_ICE] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/STONE.bmp");
	textures[STONE] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/STONE_SURFACE.bmp");
	textures[STONE_SURFACE] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/STONE_SURFACE_MOSS.bmp");
	textures[STONE_SURFACE_MOSS] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/STONE_SURFACE_SNOW.bmp");
	textures[STONE_SURFACE_SNOW] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/STONE_CEILING.bmp");
	textures[STONE_CEILING] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/STONE_CEILING.bmp");
	textures[STONE_CEILING] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/STONE_CEILING_ICE.bmp");
	textures[STONE_CEILING_ICE] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/ORE_IRON.bmp");
	textures[ORE_IRON] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/WATER.bmp");
	textures[WATER] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/WATER_FALLING.bmp");
	textures[WATER_FALLING] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/ICE.bmp");
	textures[ICE] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/ICE_SURFACE.bmp");
	textures[ICE_SURFACE] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/ICE_SURFACE_SNOW.bmp");
	textures[ICE_SURFACE_SNOW] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/ICE_CEILING.bmp");
	textures[ICE_CEILING] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/TREE.bmp");
	textures[TREE] = surface ? SDL_CreateTextureFromSurface(ren, surface) : NULL;
	SDL_FreeSurface(surface);
	surface = SDL_LoadBMP("../textures/LEAVES.bmp");
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
	SDL_Rect* window;
	SDL_Rect* block_window;
	SDL_Point origin;
	SDL_Point block_origin;
};

BlockRenderer* CreateBlockRenderer(SDL_Renderer* ren)
{
	BlockRenderer* bren = malloc(sizeof(BlockRenderer));
	if(bren)
	{
		bren->ren = ren;
		bren->window = NULL;
		bren->block_window = NULL;
		bren->origin.x = 0;
		bren->origin.y = 0;
		bren->block_origin.x = 0;
		bren->block_origin.y = 0;
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
		bren->block_origin.x = x;
		bren->block_origin.y = y;
	}
}

void SetOrigin(BlockRenderer* bren, int x ,int y)
{
	if(bren)
	{
		bren->origin.x = x;
		bren->origin.y = y;
	}
}

void SetBlockWindow(BlockRenderer* bren, SDL_Rect* window)
{
	if(bren) bren->block_window = window;
}

void SetWindow(BlockRenderer* bren, SDL_Rect* window)
{
	if(bren) bren->window = window;
}

void RenderBlock(BlockRenderer* bren, Block* block)
{
	if(bren && block)
	{
		SDL_Rect srcrect, dstrect;
		dstrect.w = dstrect.h = BLOCK_SIZE;
		dstrect.x = block->x + bren->block_origin.x;
		dstrect.y = block->y + bren->block_origin.y;
		if(bren->block_window && (
		   dstrect.x < bren->block_window->x ||
		   dstrect.x >= bren->block_window->x + bren->block_window->w ||
		   dstrect.y < bren->block_window->y ||
		   dstrect.y >= bren->block_window->y + bren->block_window->h))
		{
			return;
		}
		dstrect.x = dstrect.x*BLOCK_SIZE + bren->origin.x;
		dstrect.y = dstrect.y*BLOCK_SIZE + bren->origin.y;

		srcrect.x = srcrect.y = 0;
		srcrect.w = srcrect.h = BLOCK_SIZE;

		if(bren->window)
		{
			int tmp = bren->window->x + bren->window->w;
			if(dstrect.x < bren->window->x)
			{
				srcrect.x = bren->window->x - dstrect.x;
				srcrect.w -= srcrect.x;
				if(srcrect.w < 1) return;
			}
			else if(dstrect.x > tmp - BLOCK_SIZE)
			{
				srcrect.w -= tmp - dstrect.x;
				if(srcrect.w < 1) return;
			}

			tmp = bren->window->y + bren->window->h;
			if(dstrect.y < bren->window->y)
			{
				srcrect.y = bren->window->y - dstrect.y;
				srcrect.h -= srcrect.y;
				if(srcrect.h < 1) return;
			}
			else if(dstrect.y > tmp - BLOCK_SIZE)
			{
				srcrect.h -= tmp - dstrect.y;
				if(srcrect.h < 1) return;
			}
		}
		SDL_RenderCopy(bren->ren, textures[block->type], &srcrect, &dstrect);
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
