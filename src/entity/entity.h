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

#ifndef ENTITY_H
#define ENTITY_H

#include "../defs.h"
#include "../structs.h"

#define HEALTH_BAR_HEIGHT 2

Entity InitEntity(Vector2 spawn, float health, float stamina, float mana, int damage, float speed,
char* texture_path, int texture_width, int texture_height, char* damage_sound_path, char* death_sound_path);

void isEntityAlive(Entity* entity);
void DrawEntityHealthBar(Entity entity_type, int entity_health, int entity_max_health);
void UpdateEntityPosition(Entity *entity, float deltaX, float deltaY);
void UpdateEntityFrameRec(Entity *entity, unsigned int currentFrame_x, unsigned int currentFrame_y, int spriteSheetWidth, int spriteSheetHeight);
void DrawEntity(Entity entity, int entity_size, int entity_origin_x, int entity_origin_y, int base_health);



#endif // ENTITY_H