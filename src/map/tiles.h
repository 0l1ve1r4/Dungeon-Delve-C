#ifndef TILES_H
#define TILES_H

#include "../defs.h"
#include "../structs.h"
#include "../utils/utils.h"

Vector2** SetTilePosition(int matrix_length, int tile_size);

Tile InitTile(int x, int y, bool isBlocking, char *texturePath, int TILE_SIZE, int probability, char* break_sound);
Tile** CreateTileMap(bool blocking, int matrix_length, int tile_size, char* tilePath, int spawn_probability, char* break_sound);
Tile*** remove_duplicates(Tile*** TileMaps, int matrix_length, uint8_t num_objects, Player *player);

#endif // TILES_H