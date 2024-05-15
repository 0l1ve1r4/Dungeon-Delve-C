#include "tiles.h"

Vector2** SetTilePosition(int matrix_length, int tile_size){

    Vector2** TilesPositions = (Vector2**)malloc(sizeof(Vector2*) * matrix_length);
    for (int X = 0; X < matrix_length; X++) 
        TilesPositions[X] = (Vector2*)malloc(sizeof(Vector2) * matrix_length);
    
    for (int Y = 0; Y < matrix_length; Y++)
        for (int X = 0; X < matrix_length; X++)
            TilesPositions[Y][X] = (Vector2){X * tile_size, Y * tile_size};
        
    return TilesPositions;

}

Tile InitTile(int x, int y, bool isBlocking, char *texturePath, int tile_size, char* break_sound){

    Tile tile;

    tile.position = (Vector2){ x, y };
    tile.texture = LoadTexture(texturePath);
    tile.texture.width = tile_size;
    tile.texture.height = tile_size;
    tile.rect = (Rectangle){ x, y, tile.texture.width, tile.texture.height };
    tile.break_sound = LoadSound(break_sound);

    tile.isValid = true;
    tile.blocking = isBlocking;

    return tile;
}


Tile** CreateTileMap(bool blocking, char* tilePath, int spawn_probability, char* break_sound){

    int matrix_length = MAP_LENGTH;
    int tile_size = __TILE_SIZE;

    Vector2** TilesPositions = SetTilePosition(matrix_length, tile_size);
    
    Tile **tiles = (Tile**)malloc(sizeof(Tile*) * matrix_length);
        for (int i = 0; i < matrix_length; i++) 
            tiles[i] = (Tile*)malloc(sizeof(Tile) * matrix_length);
    
    for (int i = 0; i < matrix_length; i++){
        for (int j = 0; j < matrix_length; j++){

            if (rand() % 100 < spawn_probability)
                tiles[i][j] = InitTile(TilesPositions[i][j].x, TilesPositions[i][j].y, 
                            blocking, tilePath, tile_size, break_sound);
            
            }

    free(TilesPositions[i]);
    
    }

    free(TilesPositions);


    return tiles;
}


