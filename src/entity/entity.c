// This file is part of DungeonDelveC.
// Copyright (C) 2024 Guilherme Oliveira Santos

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

#include "entity.h"

Entity InitEntity(Vector2 spawn, float health, float stamina, float mana, int damage, float speed){

    Entity entity;
    entity.spawn_point = spawn;
    entity.position = spawn;
    entity.last_position = spawn;
    entity.health = health;
    entity.stamina = stamina;
    entity.mana = mana;
    entity.damage = damage;
    entity.speed = speed;
    entity.isAlive = true;

    return entity;

}

void DrawEntityHealthBar(Entity entity_type, int entity_health, int entity_max_health){

    unsigned int HealBar_Y = entity_type.position.y - 10;
    unsigned int HealthBar_X = entity_type.position.x - (entity_max_health) / __TILE_SIZE / entity_max_health;

    unsigned int HealthBarHeight = HEALTH_BAR_HEIGHT;
    unsigned int HealthBarWidth = entity_max_health * __TILE_SIZE / entity_max_health;
    unsigned int CurrentHealthBarWidth = entity_health * __TILE_SIZE / entity_max_health;

    Rectangle healthBar = (Rectangle){HealthBar_X, HealBar_Y, HealthBarWidth, HealthBarHeight};
    Rectangle fullHealthBar = (Rectangle){HealthBar_X, HealBar_Y, CurrentHealthBarWidth, HealthBarHeight};

    DrawRectangleRec(healthBar, BLACK);
    DrawRectangleRec(fullHealthBar, GREEN);

}

void UpdateEntityPosition(Entity *entity, float deltaX, float deltaY){
    entity->position.x += deltaX * entity->speed;
    entity->position.y += deltaY * entity->speed;
    entity->isMoving = true;
}