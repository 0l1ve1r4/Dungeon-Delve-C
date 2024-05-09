#ifndef RENDER_H
#define RENDER_H

#include "../defs.h"
#include "../structs.h"
#include "../utils/utils.h"


Tile InitTile(int x, int y, int isBlocking, char *texturePath, int TILE_SIZE, int probability);
Tile InitRandomTile(int x, int y, int isBlocking, char *spritesheetPath, int TILE_SIZE_MULTIPLIER, 
                    int num_sprites_width, int num_sprites_height);

Tile* InitTiles(Vector2 *positions, int length, char *texturePath, int TILE_SIZE);
Tile** InitMatrixTiles(Vector2** positions, int length, char *texturePath, int TILE_SIZE, int probability);
Tile** CreateTileMap(int length, int TILE_SIZE, char* tilePath, int probability);

Tile*** CreateMap(int length, int tile_size);

void DrawTileMap(Tile **tiles);
void DrawFullMap(Tile ***tiles);

// CAMERA RELATED - FUNCTIONS //
Camera2D InitPlayerCamera(Player *player);
void UpdatePlayerCamera(Camera2D *camera, Player *player, float delta, int width, int height);




#endif