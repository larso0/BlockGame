/*
 * Chunk.c
 *
 *  Created on: 12. aug. 2015
 *      Author: larso
 */

#include "Chunk.h"
#include "Grid.h"
#include <stdlib.h>

struct _Chunk
{
	int w, h;
	Grid* blocks;
};

Chunk* CreateChunk(int w, int h)
{
	Chunk* chunk = malloc(sizeof(Chunk));
	if(chunk)
	{
		chunk->w = w;
		chunk->h = h;
		chunk->blocks = CreateGrid();
	}
	return chunk;
}

void DestroyChunk(Chunk* chunk)
{
	if(chunk)
	{
		DestroyGrid(chunk->blocks);
		free(chunk);
	}
}

int LoadChunk(Chunk* dst, FILE* file)
{
	if(!dst)
	{
		fprintf(stderr, "Destination chunk is NULL.\n");
		return -1;
	}
	if(!file)
	{
		fprintf(stderr, "File pointer is NULL.\n");
		return -2;
	}
	int tmp = fscanf(file, "%d %d\n", &dst->w, &dst->h);
	if(tmp < 2)
	{
		fprintf(stderr, "Wrong file format. Need width and height for chunk.\n");
		return -3;
	}
	int ret = 0;
	char c;
	tmp = fscanf(file, "%c", &c);
	while(tmp != EOF)
	{
		if(c == ':')
		{
			Block block;
			tmp = fscanf(file, "%d %d %d\n", &(block.x), &(block.y), (int*)&(block.type));
			if(tmp < 3)
			{
				fprintf(stderr, "Wrong file format. Need x and y coordinate and block type for block.\n");
				return -4;
			}
			if(block.x < 0 || block.x >= dst->w ||
			   block.y < 0 || block.y >= dst->h)
			{
				fprintf(stderr, "Warning: Skipping block outside of chunk.\n");
				ret = 1;
			}
			else if(block.type < UNKNOWN || block.type > LEAVES)
			{
				fprintf(stderr, "Warning: Skipping block with block type that doesn't exist.\n");
				ret = 1;
			}
			else
			{
				AddBlock(dst->blocks, &block);
			}
		}
		else if(c == '.')
		{
			fscanf(file, "\n");
			break;
		}
		else
		{
			fprintf(stderr, "Wrong file format. Use ':' before each block and '.' when done.\n");
			return -5;
		}
		tmp = fscanf(file, "%c", &c);
	}
	return ret;
}

void RenderChunk(Chunk* chunk, BlockRenderer* bren, int x, int y)
{
	if(chunk && bren)
	{
		SDL_Point tmp;
		GetBlockOrigin(bren, &tmp);
		SetBlockOrigin(bren, tmp.x + x, tmp.y + y);
		RenderBlocks(bren, chunk->blocks);
		SetBlockOrigin(bren, tmp.x, tmp.y);
	}
}
