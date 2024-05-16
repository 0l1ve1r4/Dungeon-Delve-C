#ifndef RENDER_H
#define RENDER_H

#include "../defs.h"
#include "../structs.h"
#include "../utils/utils.h"


void RenderMap(MapNode* nodes, Camera2D camera);
void UpdateMapCollision(Player *player, MapNode *map);

// CAMERA RELATED - FUNCTIONS //
Camera2D InitPlayerCamera(Player *player);
void UpdatePlayerCamera(Camera2D *camera, Player *player, float delta, int width, int height);




#endif