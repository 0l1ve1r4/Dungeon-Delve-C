#include "maps.h"


Vector2** SetTilePosition(int matrix_length, int tile_size){

    Vector2** TilesPositions = (Vector2**)malloc(sizeof(Vector2*) * matrix_length);
    for (int X = 0; X < matrix_length; X++) 
        TilesPositions[X] = (Vector2*)malloc(sizeof(Vector2) * matrix_length);
    
    for (int Y = 0; Y < matrix_length; Y++)
        for (int X = 0; X < matrix_length; X++)
            TilesPositions[Y][X] = (Vector2){X * tile_size, Y * tile_size};
        
    return TilesPositions;

}

MapNode* InitMap(int map_lenght){

    int** mapMatrix = (int**)malloc(map_lenght * sizeof(int*));
    Tile** tileMatrix = (Tile**)malloc(map_lenght * sizeof(Tile*));

    for (int i = 0; i < map_lenght; i++){
        mapMatrix[i] = (int*)malloc(map_lenght * sizeof(int));
        tileMatrix[i] = (Tile*)malloc(map_lenght * sizeof(Tile));
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

    generateMap(TileMap);


    return TileMap;

}
