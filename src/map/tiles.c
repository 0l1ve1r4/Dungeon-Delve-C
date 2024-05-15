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

Tile InitTile(int x, int y, bool isBlocking, char *texturePath, int TILE_SIZE, int probability, char* break_sound){


    Tile tile;
    tile.isValid = false;

    int random = rand() % 100;
    if (random > probability) return tile;

    tile.position = (Vector2){ 0, 0 };
    tile.texturePath = texturePath;



    tile.position = (Vector2){ x, y };
    tile.texture = LoadTexture(texturePath);
    tile.isValid = true;
    tile.texture.width = TILE_SIZE;
    tile.texture.height = TILE_SIZE;

    tile.rect = (Rectangle){ x, y, tile.texture.width, tile.texture.height };
    tile.break_sound = LoadSound(break_sound);

    tile.blocking = isBlocking;

    return tile;
}


Tile** CreateTileMap(bool blocking, int matrix_length, int tile_size, char* tilePath, int spawn_probability, char* break_sound){

    Vector2** TilesPositions = SetTilePosition(matrix_length, tile_size);
    

    Tile **tiles = (Tile**)malloc(sizeof(Tile*) * matrix_length);
    
    for (int i = 0; i < matrix_length; i++) 
        tiles[i] = (Tile*)malloc(sizeof(Tile) * matrix_length);
    
    for (int i = 0; i < matrix_length; i++){
        for (int j = 0; j < matrix_length; j++){
            tiles[i][j] = InitTile(TilesPositions[i][j].x, TilesPositions[i][j].y, 
                        blocking, tilePath, tile_size, spawn_probability, break_sound);
        }
    free(TilesPositions[i]);
    }
    free(TilesPositions);


    return tiles;
}


Tile*** remove_duplicates(Tile*** TileMaps, int matrix_length, uint8_t num_objects, Player *player){
    
    uint16_t spawn_x = player->spawn_point.x / __TILE_SIZE;
    uint16_t spawn_y = player->spawn_point.y / __TILE_SIZE;

    for (int i = 0; i < matrix_length; i++)
        for (int j = 0; j < matrix_length; j++)
            for (int k = 0; k < num_objects - 1; k++){
                if (TileMaps[k][spawn_x][spawn_y].isValid){
                    TileMaps[k][spawn_x][spawn_y].isValid = false; // Avoid collision in the spawn point
                }
                
                if (TileMaps[k][i][j].isValid)
                    for (int l = k + 1; l < num_objects; l++)
                        if (TileMaps[l][i][j].isValid){
                            TileMaps[l][i][j].isValid = false;
                        }
            }
    return TileMaps;
}