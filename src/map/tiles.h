#ifndef TILES_H
#define TILES_H

#include "../defs.h"
#include "../structs.h"
#include "../utils/utils.h"

#define GRASS_TILE_PATH "res/tiles/plains/grass.png"
#define BUSH_TILE_PATH "res/tiles/plains/bush.png"
#define ROCK1_TILE_PATH "res/tiles/plains/rock1.png"
#define ROCK2_TILE_PATH "res/tiles/plains/rock2.png"
#define WOOD_TILE_PATH "res/tiles/plains/wood.png"

#define GRASS_TILE_SOUND "res/sounds/break_grass.mp3"
#define BUSH_TILE_SOUND "res/sounds/break_grass.mp3"
#define ROCK1_TILE_SOUND "res/sounds/break_stone.mp3"
#define ROCK2_TILE_SOUND "res/sounds/break_stone.mp3"
#define WOOD_TILE_SOUND "res/sounds/break_wood.mp3"

enum TileSpawnProbability {
    GRASS_SPAWN = 100,
    BUSH_SPAWN = 20,
    ROCK1_SPAWN = 1,
    ROCK2_SPAWN = 1,
    WOOD_SPAWN = 1
};  

enum isTyleBreakable {
    GRASS_BREAK = false,
    BUSH_BREAK  = true,
    ROCK1_BREAK  = true,
    ROCK2_BREAK  = true,
    WOOD_BREAK  = true,
};


Vector2** SetTilePosition(int matrix_length, int tile_size);

Tile InitTile(int x, int y, bool isBlocking, char *texturePath, int tile_size, char* break_sound);
Tile** CreateTileMap(bool blocking, char* tilePath, int spawn_probability, char* break_sound);


#endif // TILES_H