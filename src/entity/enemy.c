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

#include "enemy.h"


static float last_time_attacked = 0;
static float last_collision_time = 0;

Enemy* InitEnemy(int spawn_x, int spawn_y){

    Enemy *enemy = (Enemy*)malloc(sizeof(Enemy));
    
    Vector2 spawn = (Vector2){spawn_x, spawn_y};

    enemy->entity = InitEntity(spawn, ENEMY_BASE_HEALTH,
    ENEMY_BASE_STAMINA, ENEMY_BASE_MANA,
    ENEMY_BASE_DAMAGE, ENEMY_BASE_SPEED
    
    );

    enemy->texture = LoadTexture(ENEMY_SPRITESHEET);
    enemy->texture.width *= -1;
    int rand_ghost_x = rand() % 5;
    int rand_ghost_y = rand() % 2;


    enemy->frameRec = (Rectangle){0, 0, enemy->texture.width/5, enemy->texture.height/2};
    enemy->frameRec.x = (float)rand_ghost_x * (float)enemy->texture.width / 5;
    enemy->frameRec.y = (float)rand_ghost_y * (float)enemy->texture.height / 2;
    enemy->isMoving = false;
    enemy->isAttacking = false;

    return enemy;

}

/// ====================================================================================================

void UpdateEnemiesMap(MapNode *TileMap, float deltaTime, int currentFrame, Player* player) {
    for (int i = 0; i < TileMap->num_enemies ; i++) {
        UpdateEnemy(TileMap->enemies[i], player, deltaTime, currentFrame);

    }
}

void UpdateEnemy(Enemy *enemy, Player* player, float deltaTime, int currentFrame) {

    if (enemy->entity.isAlive == false) return;

    enemy->entity.last_position = enemy->entity.position;

    isMoving(enemy, player, deltaTime, currentFrame);

    if (!enemy->isMoving) return; 
    
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
        }

        else{
            if (GetTime() - last_collision_time < 1) return;

            updatePlayerHealth(player);
        }
    
    }
}

void isMoving(Enemy *enemy, Player* player, float deltaTime, int currentFrame) {
    enemy->isMoving = false;

    if (enemy->entity.position.x < player->entity.position.x) {
        UpdateEntityPosition(&enemy->entity, enemy->entity.speed * deltaTime, 0);
        handleCollision(enemy, player, deltaTime, -1, 0);
    } 
    else if (enemy->entity.position.x > player->entity.position.x) {
        UpdateEntityPosition(&enemy->entity, -enemy->entity.speed * deltaTime, 0);
        handleCollision(enemy, player, deltaTime, 1, 0);
    }

    if (enemy->entity.position.y < player->entity.position.y) {
        UpdateEntityPosition(&enemy->entity, 0, enemy->entity.speed * deltaTime);
        handleCollision(enemy, player, deltaTime, 0, -1);
    } 
    else if (enemy->entity.position.y > player->entity.position.y) {
        UpdateEntityPosition(&enemy->entity, 0, -enemy->entity.speed * deltaTime);
        handleCollision(enemy, player, deltaTime, 0, 1);
    }
}

void DrawEnemyMap(MapNode *TileMap) {
    for (int i = 0; i < TileMap->num_enemies ; i++) {
        DrawEnemy(TileMap->enemies[i]);
    }
}

void DrawEnemy(Enemy *enemy) { // this is buggy

    if (enemy->entity.health <= 0){ 
        if (enemy->entity.isAlive == false) {
            return;
        } else {
            enemy->entity.isAlive = false;
        }
        UnloadTexture(enemy->texture);
    return;

    }

    Rectangle destRec = (Rectangle){enemy->entity.position.x, enemy->entity.position.y, 12, __TILE_SIZE};
    Vector2 origin = (Vector2){1, 10};

    DrawEntityHealthBar(enemy->entity, enemy->entity.health, ENEMY_BASE_HEALTH);
    DrawTexturePro(enemy->texture, enemy->frameRec, destRec, origin, 0, WHITE);

}
