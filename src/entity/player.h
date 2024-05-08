#ifndef PLAYER_H
#define PLAYER_H

#include "../defs.h"
#include "../structs.h"


Player* InitPlayer(void);

// Function prototypes
void UpdatePlayer(Player *player, float deltaTime, int currentFrame);
void MovePlayer(Player *player, float deltaTime, int currentFrame);
void UpdateFrameRec(Player *player, int currentFrame);
void PlayIdleAnimation(Player *player, int currentFrame);

#endif // STRUCTS_H