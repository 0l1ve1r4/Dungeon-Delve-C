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

Vector2** SetTilePosition(int matrix_length, int tile_size){

    Vector2** TilesPositions = (Vector2**)malloc((size_t)matrix_length * sizeof(Vector2*));
    for (int X = 0; X < matrix_length; X++) 
        TilesPositions[X] = (Vector2*)malloc((size_t)matrix_length * sizeof(Vector2));
    
    for (int Y = 0; Y < matrix_length; Y++)
        for (int X = 0; X < matrix_length; X++)
            TilesPositions[Y][X] = (Vector2){X * tile_size, Y * tile_size};
        
    return TilesPositions;

}

MapNode* InitMap(int map_lenght){

    int** mapMatrix = (int**)malloc((size_t)map_lenght * sizeof(int*));
    Tile** tileMatrix = (Tile**)malloc((size_t)map_lenght * sizeof(Tile*));

    for (int i = 0; i < map_lenght; i++){
        mapMatrix[i] = (int*)malloc((size_t)map_lenght * sizeof(int));
        tileMatrix[i] = (Tile*)malloc((size_t)map_lenght * sizeof(Tile));
    }

    MapNode* TileMap = (MapNode*)malloc(sizeof(MapNode));
    
    TileMap->node_id = 0;
    TileMap->matrix = mapMatrix;
    TileMap->matrix_width = map_lenght;
    TileMap->matrix_height = map_lenght;
    TileMap->positions = SetTilePosition(map_lenght, __TILE_SIZE);
    TileMap->tile_info = tileMatrix;

    for (int Y = 0; Y < map_lenght; Y++){
        for (int X = 0; X < map_lenght; X++){
            int pos_x = TileMap->positions[Y][X].x;
            int pos_y = TileMap->positions[Y][X].y;
            
            Rectangle rect = (Rectangle){pos_x, pos_y, __TILE_SIZE, __TILE_SIZE};
            TileMap->tile_info[Y][X].rect = rect;

        }
    }

    GenerateMap(TileMap);

    return TileMap;

}
