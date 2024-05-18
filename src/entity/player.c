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

Player* InitPlayer(MapNode *Map){
    Player* player = (Player*)malloc(sizeof(Player));

    player->health = PLAYER_BASE_HEALTH;
    player->stamina = PLAYER_BASE_STAMINA;
    player->mana = PLAYER_BASE_MANA; 

    int spawn_x = (Map->matrix_height * __TILE_SIZE)/2;
    int spawn_y = (Map->matrix_height * __TILE_SIZE)/2;

    player->spawn_point = (Vector2){spawn_x, spawn_y};;
    player->position = player->spawn_point;
    player->last_position = player->spawn_point;

    player->texture = LoadTexture(PLAYER_SPRITESHEET);
    player->frameRec = (Rectangle){0, 0, (float)player->texture.width/6, (float)player->texture.height/10};
    
    player->walk_1 = LoadSound(PLAYER_WALK_1_SOUND);
    player->walk_2 = LoadSound(PLAYER_WALK_2_SOUND);

    player->last_animation = FRONT_WALK_ANIMATION;
    player->speed = PLAYER_SPEED;

    player->isMoving = false;
    player->isAttacking = false;
    
    return player;
}


void UpdatePlayer(Player *player, float deltaTime, int currentFrame) {

    player->last_position = player->position;

    isMoving(player, deltaTime, currentFrame);
    isAttacking(player);

    if (!player->isMoving && !player->isAttacking) {
        PlayIdleAnimation(player, currentFrame);
        return; 
    }
                
    UpdateFrameRec(player, currentFrame);
    player->last_animation = player->last_animation;

}

void updatePlayerPosition(Player *player, float deltaX, float deltaY, int animation) {
    player->position.x += deltaX;
    player->position.y += deltaY;
    player->last_animation = animation;
    player->isMoving = true;
}

void isMoving(Player *player, float deltaTime, int currentFrame) {
    player->isMoving = false;

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        updatePlayerPosition(player, -player->speed * deltaTime, 0, SIDE_WALK_ANIMATION);
        if (player->texture.width > 0) player->texture.width *= -1;
    } 
    else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        updatePlayerPosition(player, player->speed * deltaTime, 0, SIDE_WALK_ANIMATION);
        if (player->texture.width < 0) player->texture.width *= -1;
    } 

    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        updatePlayerPosition(player, 0, -player->speed * deltaTime, BACK_WALK_ANIMATION);
    } 
    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        updatePlayerPosition(player, 0, player->speed * deltaTime, FRONT_WALK_ANIMATION);
    }

    if (player->isMoving && !IsSoundPlaying(player->walk_1) && !IsSoundPlaying(player->walk_2)) {
        rand() % 2 == 0 ? PlaySound(player->walk_1) : PlaySound(player->walk_2);
    }
}

void isAttacking(Player *player) {
    player->isAttacking = false;

    if (IsKeyDown(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
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
        player->isAttacking = true;
    }
}

void DrawPlayer(Player *player) { // this is buggy
    Rectangle playerRec = (Rectangle){player->position.x, player->position.y, PLAYER_SIZE, PLAYER_SIZE};
    Vector2 playerOrigin = (Vector2){12, 18};
    DrawTexturePro(player->texture, player->frameRec, playerRec, playerOrigin, 0, WHITE);

}

void UpdateFrameRec(Player *player, int currentFrame) {
    if (player->isAttacking) {
        if (currentFrame > 3)
            player->isAttacking = false;
            currentFrame = 1; }
                                    

    player->frameRec.x = (float)currentFrame * (float)player->texture.width / 6;
    player->frameRec.y = (float)player->last_animation * (float)player->texture.height / 10;
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

    player->frameRec.y = (float)idle_animation * (float)player->texture.height / 10;
    player->frameRec.x = (float)currentFrame * (float)player->texture.width / 6;
}
