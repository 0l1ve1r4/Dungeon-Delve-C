#ifndef PLAYER_H
#define PLAYER_H

#include "../defs.h"
#include "../structs.h"


Player* InitPlayer(MapNode *Map);


void isMoving(Player *player, float deltaTime, int currentFrame);
void isAttacking(Player *player);
void DrawPlayer(Player *player);
void UpdatePlayer(Player *player, float deltaTime, int currentFrame);
void UpdateFrameRec(Player *player, int currentFrame);
void PlayIdleAnimation(Player *player, int currentFrame);

#endif // PLAYER_H