/*
 * Chunk.h
 *
 *  Created on: 12. aug. 2015
 *      Author: larso
 */

#ifndef SRC_CHUNK_H_
#define SRC_CHUNK_H_

#include <stdio.h>
#include "BlockRenderer.h"

struct _Chunk;
typedef struct _Chunk Chunk;

Chunk* CreateChunk(int w, int h);
void DestroyChunk(Chunk* chunk);

int LoadChunk(Chunk* dst, FILE* file);
void SaveChunk(Chunk* src, FILE* file);

void RenderChunk(Chunk* chunk, BlockRenderer* bren, int x, int y);

#endif /* SRC_CHUNK_H_ */
