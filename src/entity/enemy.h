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

#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"

#define throwEnemyBackSpeed 250
#define ENEMY_BASE_HEALTH 5
#define ENEMY_BASE_STAMINA 3
#define ENEMY_BASE_MANA 3
#define ENEMY_BASE_SPEED 20
#define ENEMY_BASE_DAMAGE 1
#define ENEMY_SIZE (__TILE_SIZE * 2)
#define ENEMY_SPRITESHEET "res/characters/Flight.png"
#define ENEMY_SPRITESHEET_WIDTH 8
#define ENEMY_SPRITESHEET_HEIGHT 1

Enemy* InitEnemy(int spawn_x, int spawn_y);
void UpdateEnemiesMap(MapNode *TileMap, float deltaTime, unsigned int currentFrame, Player* player) ;
void UpdateEnemy(Enemy *enemy, Player* player, float deltaTime, unsigned int currentFrame);
void throwEnemyBack(Enemy *enemy, float deltaTime, int directionX, int directionY);
bool isCollision(Enemy *enemy, Player* player);
void handleCollision(Enemy *enemy, Player* player, float deltaTime, int directionX, int directionY);
void isMoving(Enemy *enemy, Player* player, float deltaTime);
void DrawEnemyMap(MapNode *TileMap) ;
void DrawEnemy(Enemy *enemy);
void UpdateFrameRec(Enemy *enemy, int currentFrame) ;

#endif // ENEMY_H