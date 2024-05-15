#include "render.h"

void UpdateMapCollision(Player *player, Tile **tiles, int matrix_length, int TILE_SIZE){

    Rectangle player_rect = (Rectangle){player->position.x, player->position.y, TILE_SIZE-2, TILE_SIZE-5};

    for (int X = 0; X < matrix_length; X++)
        for (int Y = 0; Y < matrix_length; Y++){

            if (tiles[X][Y].blocking == false) continue;

            if (tiles[X][Y].isValid){
                if (CheckCollisionRecs(player_rect, tiles[X][Y].rect)){
                    player->position = player->last_position;
                    if (player->isAttacking) {
                        tiles[X][Y].isValid = false;
                        PlaySound(tiles[X][Y].break_sound);
                }
            }
        }
    }
}

void UpdateNodesCollision(Player *player, MapNode* nodes){

    MapNode* current = nodes;
    while (current != NULL){
        UpdateMapCollision(player, current->tiles, nodes->node_length, __TILE_SIZE);
        current = current->next;
    }


}


void DrawTileMap(Tile **tiles, Camera2D camera) {

    int player_x = camera.target.y / __TILE_SIZE; 
    int player_y = camera.target.x / __TILE_SIZE;

    int start_i = player_x - RENDER_DISTANCE;
    int end_i = player_x + RENDER_DISTANCE;
    int start_j = player_y - RENDER_DISTANCE;
    int end_j = player_y + RENDER_DISTANCE;

    // Ensure start and end indices are within bounds
    start_i = (start_i < 0) ? 0 : start_i;
    start_j = (start_j < 0) ? 0 : start_j;
    end_i = (end_i >= MAP_LENGTH) ? MAP_LENGTH - 1 : end_i;
    end_j = (end_j >= MAP_LENGTH) ? MAP_LENGTH - 1 : end_j;

    for (int i = start_i; i <= end_i; i++) {
        for (int j = start_j; j <= end_j; j++) {            
            if (tiles[i][j].isValid)
                DrawTextureRec(tiles[i][j].texture, tiles[i][j].rect, tiles[i][j].position, WHITE);
        }
    }
}


void RenderMapNodes(MapNode* nodes, Camera2D camera){
    MapNode* current = nodes;
    while (current != NULL){
        DrawTileMap(current->tiles, camera);
        current = current->next;
    }
}


