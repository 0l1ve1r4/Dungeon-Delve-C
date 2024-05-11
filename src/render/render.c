#include "render.h"

static int num_matrices = 5;
static int x_gen = 0;

Vector2** SetTilePosition(int matrix_length, int tile_size){

    Vector2** TilesPositions = (Vector2**)malloc(sizeof(Vector2*) * matrix_length);
    for (int X = 0; X < matrix_length; X++) 
        TilesPositions[X] = (Vector2*)malloc(sizeof(Vector2) * matrix_length);
    
    for (int Y = 0; Y < matrix_length; Y++)
        for (int X = 0; X < matrix_length; X++)
            TilesPositions[Y][X] = (Vector2){X * tile_size, Y * tile_size};
        
    return TilesPositions;

}

Tile InitTile(int x, int y, int isBlocking, char *texturePath, int TILE_SIZE, int probability){

    Tile tile;
    tile.position = (Vector2){ 0, 0 };
    tile.isValid = false;

    int random = rand() % 100;
    if (random > probability) return tile;

    tile.position = (Vector2){ x, y };
    tile.texture = LoadTexture(texturePath);
    tile.isValid = true;
    tile.texture.width = TILE_SIZE;
    tile.texture.height = TILE_SIZE;

    tile.rect = (Rectangle){ x, y, tile.texture.width, tile.texture.height };

    tile.blocking = isBlocking;

    return tile;
}


Tile** CreateTileMap(int matrix_length, int tile_size, char* tilePath, int spawn_probability){

    Vector2** TilesPositions = SetTilePosition(matrix_length, tile_size);
    

    Tile **tiles = (Tile**)malloc(sizeof(Tile*) * matrix_length);
    
    for (int i = 0; i < matrix_length; i++) 
        tiles[i] = (Tile*)malloc(sizeof(Tile) * matrix_length);
    
    for (int i = 0; i < matrix_length; i++){
        for (int j = 0; j < matrix_length; j++){
            tiles[i][j] = InitTile(TilesPositions[i][j].x, TilesPositions[i][j].y, 0, tilePath, tile_size, spawn_probability);
        }
    free(TilesPositions[i]);
    }
    free(TilesPositions);


    return tiles;
}


Tile*** CreateMap(int matrix_length, int tile_size){

    Tile*** TileMaps = (Tile***)malloc(sizeof(Tile**) * num_matrices);
    TileMaps[0] = CreateTileMap(matrix_length, tile_size, GRASS_TILE_PATH, 100);
    TileMaps[1] = CreateTileMap(matrix_length, tile_size, BUSH_TILE_PATH, 20);
    TileMaps[2] = CreateTileMap(matrix_length, tile_size, ROCK1_TILE_PATH, 1);
    TileMaps[3] = CreateTileMap(matrix_length, tile_size, ROCK2_TILE_PATH, 1);
    TileMaps[4] = CreateTileMap(matrix_length, tile_size, WOOD_TILE_PATH, 1);
 
    return TileMaps;

};

void DrawTileMap(Tile **tiles, Camera2D camera) {
    // Calculate player position in tile coordinates
    int player_x = camera.target.y / __TILE_SIZE; // Swapping x and y
    int player_y = camera.target.x / __TILE_SIZE; // Swapping x and y

    // Calculate the range of tiles to render around the player
    int start_i = player_x - RENDER_DISTANCE;
    int end_i = player_x + RENDER_DISTANCE;
    int start_j = player_y - RENDER_DISTANCE;
    int end_j = player_y + RENDER_DISTANCE;

    // Ensure start and end indices are within bounds
    start_i = (start_i < 0) ? 0 : start_i;
    start_j = (start_j < 0) ? 0 : start_j;
    end_i = (end_i >= MAP_LENGTH) ? MAP_LENGTH - 1 : end_i;
    end_j = (end_j >= MAP_LENGTH) ? MAP_LENGTH - 1 : end_j;

    // Render tiles within the calculated range
    for (int i = start_i; i <= end_i; i++) {
        for (int j = start_j; j <= end_j; j++) {
            //if (tiles[i][j].isValid)
                DrawTextureRec(tiles[i][j].texture, tiles[i][j].rect, tiles[i][j].position, WHITE);
        }
    }
}



void DrawFullMap(Tile ***tiles, Camera2D camera){
    for (int i = 0; i < num_matrices; i++) DrawTileMap(tiles[i], camera);
}


