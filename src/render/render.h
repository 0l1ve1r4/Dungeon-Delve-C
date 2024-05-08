#ifndef RENDER_H
#define RENDER_H

#include "../defs.h"
#include "../structs.h"


// CAMERA RELATED - FUNCTIONS //
Camera2D InitPlayerCamera(Player *player);
void UpdatePlayerCamera(Camera2D *camera, Player *player, float delta, int width, int height);

// GAME INFO - FUNCTIONS //
void GetGameInfo(Player* player);
void ShowControls(void);


#endif