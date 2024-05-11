#ifndef RENDER_H
#define RENDER_H

#include "../defs.h"
#include "../structs.h"
#include "../utils/utils.h"

Vector2** SetTilePosition(int matrix_length, int tile_size);

Tile InitTile(int x, int y, int isBlocking, char *texturePath, int TILE_SIZE, int probability);
Tile** CreateTileMap(int length, int TILE_SIZE, char* tilePath, int probability);
Tile*** CreateMap(int length, int tile_size);

void DrawTileMap(Tile **tiles, Camera2D camera);
void DrawFullMap(Tile ***tiles, Camera2D camera);


// CAMERA RELATED - FUNCTIONS //
Camera2D InitPlayerCamera(Player *player);
void UpdatePlayerCamera(Camera2D *camera, Player *player, float delta, int width, int height);




#endif