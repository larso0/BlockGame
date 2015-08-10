/*
 * Block.h
 *
 *  Created on: 5. aug. 2015
 *      Author: larso
 */

#ifndef BLOCK_H_
#define BLOCK_H_

typedef enum
{
    UNKNOWN,

    DIRT,
    DIRT_SURFACE, DIRT_SURFACE_GRASS, DIRT_SURFACE_SNOW,
    DIRT_CEILING, DIRT_CEILING_ICE,

    STONE,
    STONE_SURFACE, STONE_SURFACE_MOSS, STONE_SURFACE_SNOW,
    STONE_CEILING, STONE_CEILING_ICE,

    ORE_IRON,

    WATER,
    WATER_FALLING,

    ICE,
    ICE_SURFACE, ICE_SURFACE_SNOW,
    ICE_CEILING,

    TREE,
    LEAVES
} BlockType;

typedef struct
{
    BlockType type;
    int x, y;
} Block;

#endif /* BLOCK_H_ */
