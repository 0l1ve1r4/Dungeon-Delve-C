// This file is part of DungeonDelveC.
// Copyright (C) 2024 - 2025 Guilherme Oliveira Santos

// DungeonDelveC is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef PLAYER_H
#define PLAYER_H
//
#include "entity.h"
//
#define PLAYER_BASE_HEALTH 5
#define PLAYER_BASE_STAMINA 5
#define PLAYER_BASE_MANA 5
#define PLAYER_BASE_DAMAGE 1
//
#define PLAYER_SPRITESHEET "res/characters/player.png"
#define PLAYER_SPRITESHEET_WIDTH 6
#define PLAYER_SPRITESHEET_HEIGHT 10
//
#define PLAYER_SPEED 100.0f
#define PLAYER_FRAME_SPEED 20
//
#define FRONT_IDLE_ANIMATION 0
#define SIDE_IDLE_ANIMATION 1
#define BACK_IDLE_ANIMATION 2
//
#define FRONT_WALK_ANIMATION 3
#define SIDE_WALK_ANIMATION 4
#define BACK_WALK_ANIMATION 5
//
#define FRONT_ATTACK_ANIMATION 6
#define SIDE_ATTACK_ANIMATION 7
#define BACK_ATTACK_ANIMATION 8
//
#define DEAD_ANIMATION 9
//
#define RENDER_DISTANCE 14
#define PLAYER_SIZE (__TILE_SIZE * 2)

Player* InitPlayer(MapNode *Map);

void updatePlayerPositionIfMoving(Player *player, float deltaTime, MapNode *map);
void isAttacking(Player *player);
void updatePlayerPosition(Player *player, float deltaX, float deltaY, unsigned int animation);
void FallBackPlayerToLastPlayerPostionInCaseOfWallCollisionAndUpdateLAST_COLLISION_TYPE(Player *player, MapNode *map);

void DrawPlayer(Player *player);
uint8_t *UpdatePlayer(Player *player, float deltaTime, unsigned int currentFrame, MapNode *map);
void UpdateEnemyFrameRec(Player *player, int currentFrame);
void PlayIdleAnimation(Player *player, unsigned int currentFrame);

#endif // PLAYER_H
