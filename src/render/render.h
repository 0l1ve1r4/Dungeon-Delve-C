#ifndef RENDER_H
#define RENDER_H

#include "../defs.h"
#include "../structs.h"
#include "../utils/utils.h"


Tile InitTile(int x, int y, int isBlocking, char *texturePath, int TILE_SIZE);
Tile* InitTiles(Vector2 *positions, int length, char *texturePath, int TILE_SIZE);
Tile** InitMatrixTiles(Vector2** positions, int length, char *texturePath, int TILE_SIZE);
Tile** CreateGrassTiles(int length, int TILE_SIZE);

void DrawTiles(Tile *tiles, int length);

// CAMERA RELATED - FUNCTIONS //
Camera2D InitPlayerCamera(Player *player);
void UpdatePlayerCamera(Camera2D *camera, Player *player, float delta, int width, int height);




#endif