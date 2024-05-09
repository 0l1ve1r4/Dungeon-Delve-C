#include "player.h"


static int current_animation = 0;

Player* InitPlayer(void){

    Player* player = (Player*)malloc(sizeof(Player));
    player->position = (Vector2){SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
    player->speed = PLAYER_SPEED;
    
    player->texture = LoadTexture("resources/characters/player.png");
    player->frameRec = (Rectangle){0.0f, 0.0f, (float)player->texture.width/6, 
                        (float)player->texture.height/10};

    player->last_animation = FRONT_WALK_ANIMATION;

    return player;
}


void UpdatePlayer(Player *player, float deltaTime, int currentFrame) {

    MovePlayer(player, deltaTime, currentFrame);

    if (!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_A) &&
        !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_D) &&
        !IsKeyDown(KEY_UP) && !IsKeyDown(KEY_W) &&
        !IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_S)) {
        PlayIdleAnimation(player, currentFrame);

        return;
    }

    UpdateFrameRec(player, currentFrame);

    
    player->last_animation = current_animation;
}

void MovePlayer(Player *player, float deltaTime, int currentFrame) {
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        player->position.x -= player->speed * deltaTime;
        current_animation = SIDE_WALK_ANIMATION;
        if (player->texture.width > 0) player->texture.width *= -1;  


    } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        player->position.x += player->speed * deltaTime;
        current_animation = SIDE_WALK_ANIMATION;
        if (player->texture.width < 0) player->texture.width *= -1; 

    } else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        player->position.y -= player->speed * deltaTime;
        current_animation = BACK_WALK_ANIMATION;
    } else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        player->position.y += player->speed * deltaTime;
        current_animation = FRONT_WALK_ANIMATION;
    }
}

void UpdateFrameRec(Player *player, int currentFrame) {
    player->frameRec.x = (float)currentFrame * (float)player->texture.width / 6;
    player->frameRec.y = (float)current_animation * (float)player->texture.height / 10;
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
