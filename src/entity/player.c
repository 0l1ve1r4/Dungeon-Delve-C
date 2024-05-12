#include "player.h"


static int current_animation = 0;
static bool is_attacking = false;

Player* InitPlayer(void){
    Player* player = (Player*)malloc(sizeof(Player));
    Vector2 spawn_point = (Vector2){MAP_LENGTH/2 * __TILE_SIZE, MAP_LENGTH/2 * __TILE_SIZE};

    player->spawn_point = spawn_point;
    player->position = spawn_point;
    player->last_position = spawn_point;

    player->texture = LoadTexture("res/characters/player.png");
    player->frameRec = (Rectangle){0.0f, 0.0f, (float)player->texture.width/6, (float)player->texture.height/10};
    player->walk = LoadSound("res/sounds/walk.mp3");

    player->last_animation = FRONT_WALK_ANIMATION;
    player->speed = PLAYER_SPEED;
    
    return player;
}


void UpdatePlayer(Player *player, float deltaTime, int currentFrame) {

    player->last_position = player->position;

    bool move = isMoving(player, deltaTime, currentFrame);
    bool attack = isAttacking(player);

    if (!move && !attack) {
        PlayIdleAnimation(player, currentFrame);
        return;
    
    }

    UpdateFrameRec(player, currentFrame);

    
    player->last_animation = current_animation;
}

bool isMoving(Player *player, float deltaTime, int currentFrame) {
    bool move = false; 



    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        player->position.x -= player->speed * deltaTime;
        current_animation = SIDE_WALK_ANIMATION;
        if (player->texture.width > 0) player->texture.width *= -1;  
        move = true; 
    
    } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        player->position.x += player->speed * deltaTime;
        current_animation = SIDE_WALK_ANIMATION;
        if (player->texture.width < 0) player->texture.width *= -1; 
        move = true; 
    
    } else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
        player->position.y -= player->speed * deltaTime;
        current_animation = BACK_WALK_ANIMATION;
        move = true; 
    
    } else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
        player->position.y += player->speed * deltaTime;
        current_animation = FRONT_WALK_ANIMATION;
        move = true; 
    }

    //if (move && !IsSoundPlaying(player->walk)) {
    //    PlaySound(player->walk);
    //}

    return move;
}


bool isAttacking(Player *player) {
    
    bool attack = false;
    
    if (IsKeyDown(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {

        attack = true;
    
        if (player->last_animation == SIDE_WALK_ANIMATION || player->last_animation == SIDE_WALK_ANIMATION) {
            current_animation = SIDE_ATTACK_ANIMATION;
        
        } else if (player->last_animation == BACK_WALK_ANIMATION || player->last_animation == BACK_WALK_ANIMATION) {
            current_animation = BACK_ATTACK_ANIMATION;
        
        } else if (player->last_animation == FRONT_WALK_ANIMATION || player->last_animation == FRONT_WALK_ANIMATION) {
            current_animation = FRONT_ATTACK_ANIMATION;
        }

        is_attacking = true;

}

    return attack;
    
}

void DrawPlayer(Player *player) {
    
    /// THIS CODE IS FULL OF MAGIC NUMBERS, BAD PRACTICE, BUT I KNOW, I KNOW, I WILL FIX IT LATER

    uint8_t player_size = __TILE_SIZE * 2.2;
    Rectangle playerRec = (Rectangle){player->position.x, player->position.y, player_size, player_size};
    Vector2 playerOrigin = (Vector2){9, 14};


    DrawTexturePro(player->texture, player->frameRec, playerRec, playerOrigin, 0, WHITE);
    DrawRectangleLines(player->position.x, player->position.y, __TILE_SIZE+1, __TILE_SIZE+1, RED);
}

void UpdateFrameRec(Player *player, int currentFrame) {
    

    if (is_attacking) {
        player->frameRec.y = (float)current_animation * (float)player->texture.height / 10;
        player->frameRec.x = (float)currentFrame * (float)player->texture.width / 6;
        is_attacking = false;
        return;
    }
    
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
