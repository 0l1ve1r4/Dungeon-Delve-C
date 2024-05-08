#ifndef PLAYER_H
#define PLAYER_H

#include "../defs.h"
#include "../structs.h"


Player* InitPlayer(void);

void UpdatePlayer(Player *player, float delta, int currentFrame);
void play_idle_animation(Player *player, int currentFrame);
void play_animation(Player *player, float side, float animation_id, int currentFrame);

// CAMERA RELATED - FUNCTIONS //

Camera2D CreateCamera(Player* player_ptr);
void get_mouse_zoom(Camera2D *camera_ptr);
void UpdateCameraCenter(Camera2D *camera_ptr, Player *player_ptr);

#endif // STRUCTS_H