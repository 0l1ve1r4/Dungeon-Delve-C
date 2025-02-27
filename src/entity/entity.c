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

#include "entity.h"

Entity InitEntity(Vector2 spawn, float health, float stamina, float mana, int damage, float speed,
char* texture_path, int texture_width, int texture_height, char* damage_sound_path, char* death_sound_path){

    Entity entity;
    entity.texture = LoadTexture(texture_path);
    entity.frameRec = (Rectangle){0, 0, 0, 0};
    entity.frameRec.width = entity.texture.width/texture_width;
    entity.frameRec.height = entity.texture.height/texture_height;
    entity.take_damage_sound = LoadSound(damage_sound_path);
    entity.death_sound = LoadSound(death_sound_path);

    entity.spawn_point = spawn;
    entity.position = spawn;
    entity.last_position = spawn;
    entity.health = health;
    entity.stamina = stamina;
    entity.mana = mana;
    entity.damage = damage;
    entity.speed = speed;
    entity.isAlive = true;
    entity.isAttacking = false;
    entity.isMoving = false;

    return entity;

}

void isEntityAlive(Entity* entity){
    if (entity->health <= 0){
        entity->isAlive = false;
        PlaySound(entity->death_sound);
    }
}

void DrawEntityHealthBar(Entity entity_type, int entity_health, int entity_max_health){
    unsigned int HealBar_Y = entity_type.position.y - 10;
    unsigned int HealthBar_X = entity_type.position.x - (entity_max_health/3);

    unsigned int barHeight = HEALTH_BAR_HEIGHT;
    unsigned int barWidth = entity_max_health * __TILE_SIZE / entity_max_health;
    
    int CurrentHealthBarWidth = entity_health * __TILE_SIZE / entity_max_health;

    Rectangle healthBar = (Rectangle){HealthBar_X, HealBar_Y, barWidth, barHeight};
    Rectangle fullHealthBar = (Rectangle){HealthBar_X, HealBar_Y, CurrentHealthBarWidth, barHeight};

    DrawRectangleRec(healthBar, BLACK);
    DrawRectangleRec(fullHealthBar, GREEN);

    if (entity_type.isPlayer){
        unsigned int staminaBar_Y = HealBar_Y - 5;        
        int CurrentHealthBarWidth = entity_health * __TILE_SIZE / entity_max_health;

        Rectangle staminaBar = (Rectangle){HealthBar_X, staminaBar_Y, barWidth, barHeight};
        Rectangle fullstaminaBar = (Rectangle){HealthBar_X, staminaBar_Y, CurrentHealthBarWidth, barHeight};

        DrawRectangleRec(staminaBar, BLACK);
        DrawRectangleRec(fullstaminaBar, YELLOW);      
    }

}

void DrawPlayerBars(Entity entity_type, int entity_health, int entity_max_health){
    unsigned int HealBar_Y = entity_type.position.y - 10;
    unsigned int HealthBar_X = entity_type.position.x - (entity_max_health/3);

    unsigned int barHeight = HEALTH_BAR_HEIGHT;
    unsigned int barWidth = entity_max_health * __TILE_SIZE / entity_max_health;
    
    int CurrentHealthBarWidth = entity_health * __TILE_SIZE / entity_max_health;

    Rectangle healthBar = (Rectangle){HealthBar_X, HealBar_Y, barWidth, barHeight};
    Rectangle fullHealthBar = (Rectangle){HealthBar_X, HealBar_Y, CurrentHealthBarWidth, barHeight};

    DrawRectangleRec(healthBar, BLACK);
    DrawRectangleRec(fullHealthBar, GREEN);

    if (entity_type.isPlayer){
        unsigned int staminaBar_Y = HealBar_Y - 6.0;        
        int CurrentHealthBarWidth = entity_type.stamina * __TILE_SIZE / entity_max_health;

        Rectangle staminaBar = (Rectangle){HealthBar_X, staminaBar_Y, barWidth, barHeight};
        Rectangle fullstaminaBar = (Rectangle){HealthBar_X, staminaBar_Y, CurrentHealthBarWidth, barHeight};

        DrawRectangleRec(staminaBar, BLACK);
        DrawRectangleRec(fullstaminaBar, YELLOW);      
    }

    if (entity_type.isPlayer){
        unsigned int staminaBar_Y = HealBar_Y - 2.5;        
        int CurrentHealthBarWidth = entity_type.mana * __TILE_SIZE / entity_max_health;

        Rectangle staminaBar = (Rectangle){HealthBar_X, staminaBar_Y, barWidth, barHeight};
        Rectangle fullstaminaBar = (Rectangle){HealthBar_X, staminaBar_Y, CurrentHealthBarWidth, barHeight};

        DrawRectangleRec(staminaBar, BLACK);
        DrawRectangleRec(fullstaminaBar, BLUE);      
    }

}

void UpdateEntityPosition(Entity *entity, float deltaX, float deltaY){
    entity->position.x += deltaX;
    entity->position.y += deltaY;
    entity->isMoving = true;
}

void UpdateEntityFrameRec(Entity *entity, unsigned int currentFrame_x, unsigned int currentFrame_y,
                            int spriteSheetWidth, int spriteSheetHeight){  
                                
    entity->frameRec.x = (float)currentFrame_x * (float)entity->texture.width / spriteSheetWidth;
    entity->frameRec.y = (float)currentFrame_y * (float)entity->texture.height / spriteSheetHeight;
}

void DrawEntity(Entity entity, int entity_size, int entity_origin_x, int entity_origin_y, int base_health){
    if (!entity.isAlive) return;

    Rectangle entityRec = (Rectangle){entity.position.x, entity.position.y, entity_size, entity_size};
    Vector2 entityOrigin = (Vector2){entity_origin_x, entity_origin_y};

    if (entity.isPlayer) {
        DrawPlayerBars(entity, entity.health, base_health);
    }

    else {
        DrawEntityHealthBar(entity, entity.health, base_health);
    }
    
    
    DrawTexturePro(entity.texture, entity.frameRec, entityRec, entityOrigin, 0, WHITE);

    #ifdef DEBUG
    DrawRectangleLines(entityRec.x, entityRec.y, entity_size/2, entity_size/2, RED);
    #endif /* ifndef DEBUG */
}
