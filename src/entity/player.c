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

#include "player.h"
#include "paths.h"
#include "../render/render.h"

static int last_attack = 0;
static int frame_counter = 0;

Player* InitPlayer(MapNode *Map){
    Player* player = (Player*)malloc(sizeof(Player));

    int spawn_x = (Map->matrix_height * __TILE_SIZE)/2;
    int spawn_y = (Map->matrix_height * __TILE_SIZE)/2;
    Vector2 PLAYER_SPAWN = (Vector2){spawn_x, spawn_y};

    player->entity = InitEntity(
    PLAYER_SPAWN, 
    PLAYER_BASE_HEALTH, 
    PLAYER_BASE_STAMINA, 
    PLAYER_BASE_MANA, 
    PLAYER_BASE_DAMAGE, 
    PLAYER_SPEED,
    PLAYER_SPRITESHEET,
    PLAYER_SPRITESHEET_WIDTH, 
    PLAYER_SPRITESHEET_HEIGHT,
    "res/sounds/global/hit.wav",
    "res/sounds/global/death.wav"
    
    );

    player->entity.isPlayer = true;

    player->walk_sounds = (Sound*)malloc(sizeof(Sound) * COUNT_WALK_SOUNDS);
    for (int i = 0; i < COUNT_WALK_SOUNDS; i++) player->walk_sounds[i] = LoadSound(PlayerSoundPaths[i]);
    
    player->attack_sound = LoadSound(PlayerSoundPaths[ATTACK_1]);
    player->last_animation = FRONT_WALK_ANIMATION;

    player->update = &UpdatePlayer;
    player->draw = &DrawPlayer;
    player->updateCamera = &UpdatePlayerCamera;
    
    return player;
}

#define TOP_LEFT_VERTEX 0
#define TOP_RIGHT_VERTEX 1
#define BOTTOM_LEFT_VERTEX 2
#define BOTTOM_RIGHT_VERTEX 3
uint8_t LAST_COLLISION_TYPE = 0;
void FallBackPlayerToLastPlayerPostionInCaseOfWallCollisionAndUpdateLAST_COLLISION_TYPE(Player *player, MapNode *map) {
    static uint8_t checking = TOP_LEFT_VERTEX;
    static bool hasCollided = false;
    for(uint8_t i=0; i<4; i++) {
        static uint32_t vertexX, vertexY;
        switch (checking) {
            case TOP_LEFT_VERTEX:
                vertexX = player->entity.position.x/16;
                vertexY = player->entity.position.y/16;
                checking = TOP_RIGHT_VERTEX;
                break;
            case TOP_RIGHT_VERTEX:
                vertexX = (player->entity.position.x+8)/16;
                vertexY = player->entity.position.y/16;
                checking = BOTTOM_LEFT_VERTEX;
                break;
            case BOTTOM_LEFT_VERTEX:
                vertexX = player->entity.position.x/16;
                vertexY = (player->entity.position.y+10)/16;
                checking = BOTTOM_RIGHT_VERTEX;
                break;
            case BOTTOM_RIGHT_VERTEX:
                vertexX = (player->entity.position.x+8)/16;
                vertexY = (player->entity.position.y+10)/16;
                break;
        }
        if(map->tile_info[vertexY][vertexX].blocking == true && CheckCollisionRecs((Rectangle){player->entity.position.x, player->entity.position.y, 8, 10}, map->tile_info[vertexY][vertexX].rect)) {
            player->entity.position = player->entity.last_position;
            if (map->tile_info[vertexY][vertexX].isStair) LAST_COLLISION_TYPE = STAIR;
            if (map->tile_info[vertexY][vertexX].isHole)  LAST_COLLISION_TYPE = HOLE;
            hasCollided = true;
        }
    }
    if(!hasCollided) player->entity.last_position = player->entity.position;

    //if arrived here, these values should be reseted
    hasCollided = false;
    checking = TOP_LEFT_VERTEX;
}

uint8_t *UpdatePlayer(Player *player, float deltaTime, unsigned int currentFrame, MapNode *map) {
    player->entity.last_position = player->entity.position;                    // Verify if player is attacking

    if (player->entity.isAttacking){         // If player is attacking, no need to check 
        player->entity.isMoving = false;     // if player is moving, already set to false
    } else {
        isAttacking(player);
        if (!player->entity.isAttacking) updatePlayerPositionIfMoving(player, deltaTime, map);
    }

    if (!player->entity.isMoving && !player->entity.isAttacking) {
        PlayIdleAnimation(player, currentFrame);
    } else {         
        UpdateEntityFrameRec(&player->entity, currentFrame, player->last_animation, PLAYER_SPRITESHEET_WIDTH, PLAYER_SPRITESHEET_HEIGHT);
        player->last_animation = player->last_animation;


        if (player->entity.isAttacking)
            frame_counter++; 

        if (frame_counter >= PLAYER_FRAME_SPEED * 1.5) {
            player->entity.isAttacking = false;  
            frame_counter = 0;
        }

    }
    return &LAST_COLLISION_TYPE;
}

void updatePlayerPosition(Player *player, float deltaX, float deltaY, unsigned int animation) {
    UpdateEntityPosition(&player->entity, deltaX, deltaY);
    player->last_animation = animation;
}

void updatePlayerPositionIfMoving(Player *player, float deltaTime, MapNode *map) {
    player->entity.isMoving = false;

    float player_speed = player->entity.speed * deltaTime;

    bool LEFT = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A);
    bool RIGHT = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D);
    bool UP = IsKeyDown(KEY_UP) || IsKeyDown(KEY_W);
    bool DOWN = IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S);


    if ((LEFT || RIGHT) && (UP || DOWN)) player_speed /= 1.5;

    player->entity.texture.width > 0 && LEFT ? player->entity.texture.width *= -1 : 0;
    player->entity.texture.width < 0 && RIGHT ? player->entity.texture.width *= -1 : 0;
    
    if (LEFT) updatePlayerPosition(player, -player_speed, 0, SIDE_WALK_ANIMATION);
    FallBackPlayerToLastPlayerPostionInCaseOfWallCollisionAndUpdateLAST_COLLISION_TYPE(player, map);
    if (RIGHT) updatePlayerPosition(player, player_speed, 0, SIDE_WALK_ANIMATION);
    FallBackPlayerToLastPlayerPostionInCaseOfWallCollisionAndUpdateLAST_COLLISION_TYPE(player, map);
    if (UP) updatePlayerPosition(player, 0, -player_speed, BACK_WALK_ANIMATION);
    FallBackPlayerToLastPlayerPostionInCaseOfWallCollisionAndUpdateLAST_COLLISION_TYPE(player, map);
    if (DOWN) updatePlayerPosition(player, 0, player_speed, FRONT_WALK_ANIMATION);
    FallBackPlayerToLastPlayerPostionInCaseOfWallCollisionAndUpdateLAST_COLLISION_TYPE(player, map);
    PlaySound(player->walk_sounds[rand() % 3]);
}

void isAttacking(Player *player) {

    // Update Stamina //
    if (GetTime() - last_attack >= 5.0 && player->entity.stamina < PLAYER_BASE_STAMINA) 
        player->entity.stamina += 1.0;

    if (player->entity.stamina <= 0 || GetTime() - last_attack < 1.0){
        player->entity.isAttacking = false;
        return;
    }

    // Verify if player is attacking //
    else if (IsKeyDown(KEY_SPACE)) {
        switch (player->last_animation) {
            case SIDE_WALK_ANIMATION:
                player->last_animation = SIDE_ATTACK_ANIMATION;
                break;
            case BACK_WALK_ANIMATION:
                player->last_animation = BACK_ATTACK_ANIMATION;
                break;
            case FRONT_WALK_ANIMATION:
                player->last_animation = FRONT_ATTACK_ANIMATION;
                break;
        }

        player->entity.isAttacking = true;
        player->entity.stamina -= 1;
        last_attack = GetTime();        
        return;
    }
    
}

void DrawPlayer(Player *player) { 
    DrawEntity(player->entity, PLAYER_SIZE, 8, 18, PLAYER_BASE_HEALTH);
    #ifdef DEBUG
    DrawRectangleLines(player->entity.position.x, player->entity.position.y, 8, 10, GREEN);
    #endif /* ifndef DEBUG */
}

void PlayIdleAnimation(Player *player, unsigned int currentFrame) {
    unsigned int idle_animation = 0;

    switch (player->last_animation) {
        case SIDE_WALK_ANIMATION:
            idle_animation = SIDE_IDLE_ANIMATION;
            break;
        case BACK_WALK_ANIMATION:
            idle_animation = BACK_IDLE_ANIMATION;
            break;
        case FRONT_WALK_ANIMATION:
            idle_animation = FRONT_IDLE_ANIMATION;
            break;
    }
    UpdateEntityFrameRec(&player->entity, currentFrame, idle_animation, PLAYER_SPRITESHEET_WIDTH, PLAYER_SPRITESHEET_HEIGHT);
}
