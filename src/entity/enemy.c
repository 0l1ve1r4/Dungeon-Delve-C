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

#include "enemy.h"

static float last_time_attacked = 0;
static float last_collision_time = 0;

Enemy* InitEnemy(int spawn_x, int spawn_y){

    Enemy *enemy = (Enemy*)malloc(sizeof(Enemy));
    
    Vector2 spawn = (Vector2){spawn_x, spawn_y};

    enemy->entity = InitEntity(spawn, 
    ENEMY_BASE_HEALTH,
    ENEMY_BASE_STAMINA,
    ENEMY_BASE_MANA,
    ENEMY_BASE_DAMAGE, 
    ENEMY_BASE_SPEED,
    ENEMY_SPRITESHEET,
    ENEMY_SPRITESHEET_WIDTH, 
    ENEMY_SPRITESHEET_HEIGHT,
    "res/sounds/global/hit.wav",
    "res/sounds/global/death.wav"

    );

    enemy->Y_frame = 0;
    enemy->entity.isMoving = false;
    enemy->entity.isAttacking = false;

    return enemy;

}

/// ====================================================================================================

void UpdateEnemiesMap(MapNode *TileMap, float deltaTime, unsigned int currentFrame, Player* player) {
    for (int i = 0; i < TileMap->num_enemies ; i++) {
        UpdateEnemy(TileMap->enemies[i], player, deltaTime, currentFrame);

    }
}

void UpdateEnemy(Enemy *enemy, Player* player, float deltaTime, unsigned int currentFrame) {
    
    if (!enemy->entity.isAlive) return;
    
    if (enemy->entity.health <= 0){ 
        UnloadTexture(enemy->entity.texture);   // Unload the texture (make sure that you dont draw it anymore)
        PlaySound(enemy->entity.death_sound);   // Play the death sound
        enemy->entity.isAlive = false;
        enemy->Y_frame = 1;                     // Change the 'y' axis to the death animation
    
    }

    enemy->entity.last_position = enemy->entity.position;

    isMoving(enemy, player, deltaTime);

    if (!enemy->entity.isMoving) return;

    UpdateEntityFrameRec(&enemy->entity, currentFrame, enemy->Y_frame, ENEMY_SPRITESHEET_WIDTH, ENEMY_SPRITESHEET_HEIGHT);     
}

void updatePlayerHealth(Player* player) {
    float time = GetTime();
    if (time - last_time_attacked < 1) return;

    last_time_attacked = time;

    if (player->entity.health <= 0) {
        if (player->entity.health < 0) player->entity.health = 0;
        
        player->entity.isAlive = false;
        printf("Player is dead\n");
        return;
    }


    player->entity.health -= 1;
    PlaySound(player->entity.take_damage_sound);
    
}

void throwEnemyBack(Enemy *enemy, float deltaTime, int directionX, int directionY) {
    UpdateEntityPosition(&enemy->entity, directionX * throwEnemyBackSpeed * deltaTime, 
    directionY * throwEnemyBackSpeed * deltaTime);
}

bool isCollision(Enemy *enemy, Player* player) {
    return CheckCollisionRecs((Rectangle){enemy->entity.position.x, enemy->entity.position.y, __TILE_SIZE, __TILE_SIZE}, 
    (Rectangle){player->entity.position.x, player->entity.position.y, __TILE_SIZE, __TILE_SIZE});
}

void handleCollision(Enemy *enemy, Player* player, float deltaTime, int directionX, int directionY) {
    if (isCollision(enemy, player)) {
        if (player->entity.isAttacking){
            throwEnemyBack(enemy, deltaTime, directionX, directionY);
            enemy->entity.health -= 1;
            PlaySound(enemy->entity.take_damage_sound);
        }

        else{
            if (GetTime() - last_collision_time < 1) return;

            updatePlayerHealth(player);
        }
    }
}

void isMoving(Enemy *enemy, Player* player, float deltaTime) {
    enemy->entity.isMoving = true;

    bool LEFT = enemy->entity.position.x < player->entity.position.x;
    bool RIGHT = enemy->entity.position.x > player->entity.position.x;
    bool UP = enemy->entity.position.y < player->entity.position.y;
    bool DOWN = enemy->entity.position.y > player->entity.position.y;

    enemy->entity.texture.width < 0 && LEFT ? enemy->entity.texture.width *= -1 : 0;
    enemy->entity.texture.width > 0 && RIGHT ? enemy->entity.texture.width *= -1 : 0;

    if (LEFT || RIGHT || UP || DOWN) enemy->entity.isMoving = true;
    else enemy->entity.isMoving = false;

    if (LEFT){
        UpdateEntityPosition(&enemy->entity, enemy->entity.speed * deltaTime, 0);
        handleCollision(enemy, player, deltaTime, -1, 0);
    }

    if (RIGHT){
        UpdateEntityPosition(&enemy->entity, -enemy->entity.speed * deltaTime, 0);
        handleCollision(enemy, player, deltaTime, 1, 0);
    }

    if (UP){
        UpdateEntityPosition(&enemy->entity, 0, enemy->entity.speed * deltaTime);
        handleCollision(enemy, player, deltaTime, 0, -1);
    }

    if (DOWN){
        UpdateEntityPosition(&enemy->entity, 0, -enemy->entity.speed * deltaTime);
        handleCollision(enemy, player, deltaTime, 0, 1);
    }
}

void DrawEnemyMap(MapNode *TileMap) {
    for (int i = 0; i < TileMap->num_enemies ; i++) {
        DrawEntity(TileMap->enemies[i]->entity, ENEMY_SIZE, 8, 12, ENEMY_BASE_HEALTH);
    }
}
