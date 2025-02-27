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

#include "maps.h"
#include "noise.h"
#include "tiles.h"
#include "../entity/enemy.h"

// function header in tiles.h
Texture2D* InitTiles(void){

    Texture2D* textures = malloc(sizeof(Texture2D) * TILE_TYPE_COUNT);
    
    for (int i = 0; i < TILE_TYPE_COUNT; i++) textures[i] = LoadTexture(TilePaths[i]);
    
    return textures;
}

void GenerateMap(MapNode* TileMap) {

    TileMap->textures = InitTiles();

    InitWalls(TileMap);
    ClearSpawnPoint(TileMap);
    InitObjects(TileMap);
    InitBorders(TileMap);

    TileMap->num_enemies =  TileMap->matrix_width / 20;
    TileMap->enemies = malloc(sizeof(Enemy*) * (size_t)TileMap->num_enemies );

    int rand_x, rand_y;

    for (int i = 0; i < TileMap->num_enemies ; i++) {
        rand_x = rand() % TileMap->matrix_width;
        rand_y = rand() % TileMap->matrix_height;

        TileMap->enemies[i] = (Enemy*)InitEnemy(rand_x, rand_y);
    }
    
    GetTileInfo(TileMap);

    return;
}

// Get the tile info for each tile based on the generated matrix map
void GetTileInfo(MapNode *TileMap){
    for (int i = 0; i < TileMap->matrix_height; i++) {
        for (int j = 0; j < TileMap->matrix_width; j++) {
            
            if (TileMap->matrix[i][j] == FLOOR_STAIRS)
                TileMap->tile_info[i][j].isStair = true;

            else
                TileMap->tile_info[i][j].isStair = false;

            if (TileMap->matrix[i][j] == HOLE) TileMap->tile_info[i][j].isHole = true;
            else 
                TileMap->tile_info[i][j].isHole = false;
            

            // Everything that is not a floor, must be blocking, check tiles.h for the values
            if (TileMap->matrix[i][j] <= FLOOR_8)
                TileMap->tile_info[i][j].blocking = false; 
            else
                TileMap->tile_info[i][j].blocking = true; 
        }
    }
}

void InitWalls(MapNode* TileMap) { // Fill the map with Perlin noise
  
    for (int i = 0; i < TileMap->matrix_height; i++) {
        for (int j = 0; j < TileMap->matrix_width; j++) {

            int y_seed = rand() % 23;
            int x_seed = rand() % 43;

            if (perlin2d((double)i / y_seed, (double)j / x_seed) < 0.5) {

                int floor = rand() % 30;
                if(floor > 8 || floor == 0) floor = FLOOR_1;
                
                TileMap->matrix[i][j] = floor;
                
            } else {

                int rand_wall = rand() % 10000;
                if (rand_wall < 9000) TileMap->matrix[i][j] = WALL_MID;
                else if (rand_wall < 9500) TileMap->matrix[i][j] = WALL_HOLE_1;
                else if (rand_wall < 9900) TileMap->matrix[i][j] = WALL_HOLE_2;
                else if (rand_wall <= 10000) TileMap->matrix[i][j] = WALL_BANNER;
            
            }
        }
    }

    // Making sure that the path is clear
    for (int i = 0; i < TileMap->matrix_height; i++) {
        for (int j = 0; j < TileMap->matrix_width; j++) {
            bool Issurrounded = IsSurroundedByFloor(TileMap, i, j);
            if (Issurrounded) {
                TileMap->matrix[i][j] = FLOOR_1;
            }
        }
    }
}

bool IsSurroundedByFloor(MapNode *TileMap, int i, int j) {
    bool isTopFloor = i - 1 >= 0 && TileMap->matrix[i - 1][j] == FLOOR_1;
    bool isBottomFloor = i + 1 < TileMap->matrix_height && TileMap->matrix[i + 1][j] == FLOOR_1;
    bool isLeftFloor = j - 1 >= 0 && TileMap->matrix[i][j - 1] == FLOOR_1;
    bool isRightFloor = j + 1 < TileMap->matrix_width && TileMap->matrix[i][j + 1] == FLOOR_1;

    return (isTopFloor && isBottomFloor) || (isLeftFloor && isRightFloor);
}


void ClearSpawnPoint(MapNode* TileMap){

    int spawn_x = TileMap->matrix_width / 2;
    int spawn_y = TileMap->matrix_height / 2;

    for (int i = spawn_y -1; i <= spawn_y + 1; i++) {
        for (int j = spawn_x - 1; j <= spawn_x + 1; j++){
            TileMap->matrix[i][j] = FLOOR_1;

        }
    }
}

void InitObjects(MapNode* TileMap) {

    int num_objects = TileMap->matrix_width / 10;

    for (int i = 0; i < num_objects; i++) {

        TileMap->matrix[rand() % TileMap->matrix_width][rand() % TileMap->matrix_height] = HOLE;

        int stair_x = rand() % TileMap->matrix_width;
        int stair_y = rand() % TileMap->matrix_height;
        TileMap->matrix[stair_y][stair_x] = FLOOR_STAIRS;
    }
}

void InitBorders(MapNode* TileMap) {

    for (int i = 0; i < TileMap->matrix_width; i++) {
        TileMap->matrix[i][0] = WALL_LEFT;
        TileMap->matrix[i][TileMap->matrix_width - 1] = WALL_RIGHT;

    } for (int j = 0; j < TileMap->matrix_width; j++) {
        TileMap->matrix[0][j] = WALL_MID;
        TileMap->matrix[TileMap->matrix_height - 1][j] = WALL_MID;
    
    }
}

