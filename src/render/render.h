#ifndef RENDER_H
#define RENDER_H

#include "../defs.h"
#include "../structs.h"
#include "../utils/utils.h"

void UpdateMapCollision(Player *player, Tile **tiles, int matrix_length, int TILE_SIZE);
void DrawTileMap(Tile **tiles, Camera2D camera);

void UpdateNodesCollision(Player *player, MapNode* nodes);
void RenderMapNodes(MapNode* nodes, Camera2D camera);


// CAMERA RELATED - FUNCTIONS //
Camera2D InitPlayerCamera(Player *player);
void UpdatePlayerCamera(Camera2D *camera, Player *player, float delta, int width, int height);




#endif