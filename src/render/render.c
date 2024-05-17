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

#include "render.h"
#include "../map/maps.h"

void RenderMap(MapNode* nodes, Camera2D camera){
    
    int player_x = camera.target.y / __TILE_SIZE; 
    int player_y = camera.target.x / __TILE_SIZE;

    int start_i = player_x - RENDER_DISTANCE;
    int end_i = player_x + RENDER_DISTANCE;
    int start_j = player_y - RENDER_DISTANCE;
    int end_j = player_y + RENDER_DISTANCE;

    start_i = (start_i < 0) ? 0 : start_i;
    start_j = (start_j < 0) ? 0 : start_j;
    end_i = (end_i >= nodes->matrix_height) ? nodes->matrix_height - 1 : end_i;
    end_j = (end_j >= nodes->matrix_height) ? nodes->matrix_height - 1 : end_j;


    for (int i = start_i; i <= end_i; i++) {
        for (int j = start_j; j <= end_j; j++) {            
            
            int id = nodes->matrix[i][j];
            DrawTextureEx(nodes->textures[id], nodes->positions[i][j], 0, 1, WHITE);
            


        }
    }
}

void UpdateMapCollision(Player *player, MapNode *map){

    Rectangle player_rect = (Rectangle){player->position.x, player->position.y, 10, 11};



    for (int X = 0; X < map->matrix_height; X++)
        for (int Y = 0; Y < map->matrix_width; Y++){

            if (map->tile_info[X][Y].blocking == false) continue;
    

            if (CheckCollisionRecs(player_rect, map->tile_info[X][Y].rect)){             
                player->position = player->last_position;
            
            }

                }
            }




