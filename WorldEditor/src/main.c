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

	int mouse_x, mouse_y;
	int camera_x = 0, camera_y = 0;
	Uint32 mouse_state;
	SDL_Rect cursor;
	cursor.w = cursor.h = BLOCK_SIZE;
	Block cursor_block;
	cursor_block.type = DIRT;
	SDL_Rect window;
	window.x = 4*BLOCK_SIZE + 1;
	window.y = 0;
	window.h = 480;
	window.w = 640 - window.x;

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
				SDL_GetWindowSize(win, &window.w, &window.h);
				window.w -= window.x;
				break;
			case SDL_KEYDOWN:
				switch(e.key.keysym.scancode)
				{
				case SDL_SCANCODE_LEFT:
					camera_x++;
					break;
				case SDL_SCANCODE_RIGHT:
					camera_x--;
					break;
				case SDL_SCANCODE_UP:
					camera_y++;
					break;
				case SDL_SCANCODE_DOWN:
					camera_y--;
					break;
				default:
					break;
				}
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
		cursor_block.x -= camera_x;
		cursor_block.y -= camera_y;

		if(mouse_x > 4*BLOCK_SIZE + 1)
		{
			switch(mouse_state)
			{
			case SDL_BUTTON_LEFT:
				AddBlock(world, &cursor_block);
				break;
			case SDL_BUTTON_RIGHT:
			case SDL_BUTTON_RMASK:
				RemoveBlock(world, cursor_block.x, cursor_block.y);
				break;
			}
		}
		else
		{
			if(mouse_state == SDL_BUTTON_LEFT)
			{
				int pos = (cursor_block.y + camera_y)*4 + cursor_block.x + camera_x;
				if(pos < 23) cursor_block.type = pos;
			}
		}

		SDL_SetRenderDrawColor(ren, 127, 127, 127, 255);
		SDL_RenderClear(ren);
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		SDL_RenderDrawLine(ren, 4*BLOCK_SIZE, 0, 4*BLOCK_SIZE, window.h - 1);

		SetBlockOrigin(bren, 0, 0);
		SetOrigin(bren, 0, 0);
		SetWindow(bren, NULL);
		int i = 0;
		Block block;
		for(; i < 22; i++)
		{
			block.type = i;
			block.x = i % 4;
			block.y = i / 4;
			RenderBlock(bren, &block);
		}

		SetBlockOrigin(bren, camera_x, camera_y);
		SetOrigin(bren, 4*BLOCK_SIZE + 1, 0);
		SetWindow(bren, &window);
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
