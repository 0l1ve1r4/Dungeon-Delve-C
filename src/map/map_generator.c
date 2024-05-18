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

#include "maps.h"
#include "noise.h"
#include "tiles.h"

// function header in tiles.h
Texture2D* InitTiles(void){

    Texture2D* textures = malloc(sizeof(Texture2D) * TILE_TYPE_COUNT);
    
    for (int i = 0; i < TILE_TYPE_COUNT; i++) {
        textures[i] = LoadTexture(TilePaths[i]);
    }

    return textures;

}

void GenerateMap(MapNode* TileMap) {

    TileMap->textures = InitTiles();

    InitWalls(TileMap);
    ClearSpawnPoint(TileMap);
    InitObjects(TileMap);
    InitBorders(TileMap);

    return;
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
                TileMap->tile_info[i][j].blocking = false;
                
            } else {

                int rand_wall = rand() % 10000;
                if (rand_wall < 9000) TileMap->matrix[i][j] = WALL_MID;
                else if (rand_wall < 9500) TileMap->matrix[i][j] = WALL_HOLE_1;
                else if (rand_wall < 9900) TileMap->matrix[i][j] = WALL_HOLE_2;
                else if (rand_wall <= 10000) TileMap->matrix[i][j] = WALL_BANNER;

                TileMap->tile_info[i][j].blocking = true;
            
            }
        }
    }

    // Making sure that the path is clear
    for (int i = 0; i < TileMap->matrix_height; i++) {
        for (int j = 0; j < TileMap->matrix_width; j++) {
            bool Issurrounded = IsSurroundedByFloor(TileMap, i, j);
            if (Issurrounded) {
                TileMap->matrix[i][j] = FLOOR_1;
                TileMap->tile_info[i][j].blocking = false;
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
            TileMap->tile_info[i][j].blocking = false;

        }
    }
}

void InitObjects(MapNode* TileMap) {

    int num_objects = TileMap->matrix_width / 50;

    for (int i = 0; i < num_objects; i++) {

        TileMap->matrix[rand() % TileMap->matrix_width][rand() % TileMap->matrix_height] = HOLE;

        int stair_x = rand() % TileMap->matrix_width;
        int stair_y = rand() % TileMap->matrix_height;
        TileMap->matrix[stair_y][stair_x] = FLOOR_STAIRS;
        TileMap->tile_info[stair_y][stair_x].blocking = false;
        TileMap->tile_info[stair_y][stair_x].isBreakable = false;
    }
}

void InitBorders(MapNode* TileMap) {

    for (int i = 0; i < TileMap->matrix_width; i++) {
        TileMap->matrix[i][0] = WALL_LEFT;
        TileMap->matrix[i][TileMap->matrix_width - 1] = WALL_RIGHT;
        TileMap->tile_info[i][0].isBreakable = false;
        TileMap->tile_info[i][TileMap->matrix_width - 1].blocking = true;

    } for (int j = 0; j < TileMap->matrix_width; j++) {
        TileMap->matrix[0][j] = WALL_MID;
        TileMap->matrix[TileMap->matrix_height - 1][j] = WALL_MID;
        TileMap->tile_info[0][j].isBreakable = false;
        TileMap->tile_info[TileMap->matrix_height - 1][j].blocking = true;
    
    }
}

