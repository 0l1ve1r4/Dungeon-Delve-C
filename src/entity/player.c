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

#include "player.h"
#include "paths.h"

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

    player->walk_sounds = (Sound*)malloc(sizeof(Sound) * COUNT_WALK_SOUNDS);
    for (int i = 0; i < COUNT_WALK_SOUNDS; i++) player->walk_sounds[i] = LoadSound(PlayerSoundPaths[i]);
    
    player->attack_sound = LoadSound(PlayerSoundPaths[ATTACK_1]);
    player->last_animation = FRONT_WALK_ANIMATION;
    
    return player;
}

void UpdatePlayer(Player *player, float deltaTime, int currentFrame) {
    player->entity.last_position = player->entity.position;

    isPlayerMoving(player, deltaTime, currentFrame);
    isAttacking(player);

    if (!player->entity.isMoving && !player->entity.isAttacking) {
        PlayIdleAnimation(player, currentFrame);
        return; 
    }
                
    UpdateEntityFrameRec(&player->entity, currentFrame, player->last_animation, 
    PLAYER_SPRITESHEET_WIDTH, PLAYER_SPRITESHEET_HEIGHT);
    player->last_animation = player->last_animation;
}

void updatePlayerPosition(Player *player, float deltaX, float deltaY, int animation) {
    UpdateEntityPosition(&player->entity, deltaX, deltaY);
    player->last_animation = animation;
}

void isPlayerMoving(Player *player, float deltaTime, int currentFrame) {
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
    if (RIGHT) updatePlayerPosition(player, player_speed, 0, SIDE_WALK_ANIMATION);
    if (UP) updatePlayerPosition(player, 0, -player_speed, BACK_WALK_ANIMATION);
    if (DOWN) updatePlayerPosition(player, 0, player_speed, FRONT_WALK_ANIMATION);
    PlaySound(player->walk_sounds[rand() % 3]);
}

void isAttacking(Player *player) {
    if (IsKeyDown(KEY_SPACE)) {
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
        if (!IsSoundPlaying(player->attack_sound)) PlaySound(player->attack_sound);
        
        return;
    }
    else player->entity.isAttacking = false;
}

void DrawPlayer(Player *player) { 
    DrawEntity(player->entity, PLAYER_SIZE, 12, 18, PLAYER_BASE_HEALTH);
}

void PlayIdleAnimation(Player *player, int currentFrame) {
    int idle_animation = 0;

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