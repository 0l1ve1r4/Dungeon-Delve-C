#include "player.h"

Player* InitPlayer(void){

    Player* player = (Player*)malloc(sizeof(Player));
    player->position = (Vector2){SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
    player->speed = 0;

    player->texture = LoadTexture("src/resources/minion.png");
    player->texture.width = 64;
    player->texture.height = 64;

    return player;
}

void UpdatePlayer(Player *player, float deltaTime, int currentFrame){

        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) player->position.x -= PLAYER_HOR_SPD*deltaTime;
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) player->position.x += PLAYER_HOR_SPD*deltaTime;
        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) player->position.y -= PLAYER_HOR_SPD*deltaTime;
        if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) player->position.y += PLAYER_HOR_SPD*deltaTime;

}