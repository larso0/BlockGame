/*
 * main.c
 *
 *  Created on: 5. aug. 2015
 *      Author: larso
 */
#include <stdio.h>
#include <SDL2/SDL.h>
#include "Block.h"
#include "Grid.h"
#include "BlockRenderer.h"


int main(int argc, char** argv)
{
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("%s\n", SDL_GetError());
		return 1;
	}
	SDL_Window* win = SDL_CreateWindow("World editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE);
	if(!win)
	{
		printf("%s\n", SDL_GetError());
		SDL_Quit();
		return 2;
	}
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(!ren)
	{
		printf("%s\n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		return 3;
	}
	SDL_ShowCursor(SDL_DISABLE);

	Grid* world = CreateGrid();

	InitBlockTextures(ren);
	BlockRenderer* bren = CreateBlockRenderer(ren);

	int height = 480;
	int mouse_x, mouse_y;
	Uint32 mouse_state;
	SDL_Rect cursor;
	cursor.w = cursor.h = BLOCK_SIZE;
	Block cursor_block;
	cursor_block.type = DIRT;

	int running = 1;
	while(running)
	{
		SDL_Event e;
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
			case SDL_QUIT:
				running = 0;
				break;
			case SDL_WINDOWEVENT:
				SDL_GetWindowSize(win, NULL, &height);
				break;
			default:
				break;
			}
		}

		mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);
		cursor.x = (mouse_x <= 4*BLOCK_SIZE) ?
				   mouse_x - (mouse_x % BLOCK_SIZE) :
				   mouse_x - ((mouse_x - 1) % BLOCK_SIZE);
		cursor.y = mouse_y - (mouse_y % BLOCK_SIZE);
		cursor_block.x = (mouse_x <= 4*BLOCK_SIZE) ?
						 mouse_x / BLOCK_SIZE :
						 (mouse_x - 4*BLOCK_SIZE - 1) / BLOCK_SIZE;
		cursor_block.y = mouse_y / BLOCK_SIZE;

		if(mouse_x > 4*BLOCK_SIZE + 1)
		{
			switch(mouse_state)
			{
			case SDL_BUTTON_LEFT:
				AddBlock(world, &cursor_block);
				break;
			case SDL_BUTTON_RIGHT:
				RemoveBlock(world, cursor_block.x, cursor_block.y);
				break;
			}
		}
		else
		{
			if(mouse_state == SDL_BUTTON_LEFT)
			{
				int pos = cursor_block.y*4 + cursor_block.x;
				cursor_block.type = (pos < 23) ? pos : UNKNOWN;
			}
		}

		SDL_SetRenderDrawColor(ren, 127, 127, 127, 255);
		SDL_RenderClear(ren);
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderDrawLine(ren, 4*BLOCK_SIZE, 0, 4*BLOCK_SIZE, height - 1);

		SetPixelOrigin(bren, 0, 0);
		int i = 0;
		Block block;
		for(; i < 22; i++)
		{
			block.type = i;
			block.x = i % 4;
			block.y = i / 4;
			RenderBlock(bren, &block);
		}

		SetPixelOrigin(bren, 4*BLOCK_SIZE + 1, 0);
		RenderBlocks(bren, world);

		if(mouse_x > 4*BLOCK_SIZE + 1)
		{
			RenderBlock(bren, &cursor_block);
		}
		SDL_RenderDrawRect(ren, &cursor);

		SDL_RenderPresent(ren);
	}

	DestroyBlockRenderer(bren);
	CleanBlockTextures();
	DestroyGrid(world);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}
