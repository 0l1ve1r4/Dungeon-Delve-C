#ifndef PLAYER_H
#define PLAYER_H

#include "../defs.h"
#include "../structs.h"


Player* InitPlayer(void);

void UpdatePlayer(Player *player, float deltaTime, int currentFrame);
bool isMoving(Player *player, float deltaTime, int currentFrame);
bool isAttacking(Player *player);

void DrawPlayer(Player *player);
void UpdateFrameRec(Player *player, int currentFrame);
void PlayIdleAnimation(Player *player, int currentFrame);

#endif // STRUCTS_H