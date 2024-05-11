#include "render.h"

static __uint8_t num_matrices = 5;

Vector2** SetTilePosition(int matrix_length, int tile_size){

    Vector2** TilesPositions = (Vector2**)malloc(sizeof(Vector2*) * matrix_length);
    for (int X = 0; X < matrix_length; X++) 
        TilesPositions[X] = (Vector2*)malloc(sizeof(Vector2) * matrix_length);
    
    for (int Y = 0; Y < matrix_length; Y++)
        for (int X = 0; X < matrix_length; X++)
            TilesPositions[Y][X] = (Vector2){X * tile_size, Y * tile_size};
        
    return TilesPositions;

}

Tile InitTile(int x, int y, bool isBlocking, char *texturePath, int TILE_SIZE, int probability){

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


Tile** CreateTileMap(bool blocking, int matrix_length, int tile_size, char* tilePath, int spawn_probability){

    Vector2** TilesPositions = SetTilePosition(matrix_length, tile_size);
    

    Tile **tiles = (Tile**)malloc(sizeof(Tile*) * matrix_length);
    
    for (int i = 0; i < matrix_length; i++) 
        tiles[i] = (Tile*)malloc(sizeof(Tile) * matrix_length);
    
    for (int i = 0; i < matrix_length; i++){
        for (int j = 0; j < matrix_length; j++){
            tiles[i][j] = InitTile(TilesPositions[i][j].x, TilesPositions[i][j].y, blocking, tilePath, tile_size, spawn_probability);
        }
    free(TilesPositions[i]);
    }
    free(TilesPositions);


    return tiles;
}


Tile*** CreateMap(int matrix_length, int tile_size){

    __uint8_t num_objects = num_matrices - 1;

    Tile*** TileMap = (Tile***)malloc(sizeof(Tile**) * num_matrices); 
    Tile*** TileObjects = (Tile***)malloc(sizeof(Tile**) * num_objects); // Just colisions

    TileMap[0] = CreateTileMap(false, matrix_length, tile_size, GRASS_TILE_PATH, 100);

    TileObjects[0] = CreateTileMap(true, matrix_length, tile_size, BUSH_TILE_PATH, 20);
    TileObjects[1] = CreateTileMap(true, matrix_length, tile_size, ROCK1_TILE_PATH, 1);
    TileObjects[2] = CreateTileMap(true, matrix_length, tile_size, ROCK2_TILE_PATH, 1);
    TileObjects[3] = CreateTileMap(true, matrix_length, tile_size, WOOD_TILE_PATH, 1);
 
    TileObjects = remove_duplicates(TileObjects, matrix_length, num_objects);

    for (int i = 1; i < num_matrices; i++)
        TileMap[i] = TileObjects[i - 1];


    return TileMap;

};

Tile*** remove_duplicates(Tile*** TileMaps, int matrix_length, __uint8_t num_objects){
    
    for (int i = 0; i < matrix_length; i++)
        for (int j = 0; j < matrix_length; j++)
            for (int k = 0; k < num_objects - 1; k++){
                
                if (TileMaps[k][0][0].isValid){
                    TileMaps[k][0][0].isValid = false; // Avoid collisionin the spawn point
                }
                
                if (TileMaps[k][i][j].isValid)
                    for (int l = k + 1; l < num_objects; l++)
                        if (TileMaps[l][i][j].isValid)
                            TileMaps[l][i][j].isValid = false;

            }
    return TileMaps;
}

void UpdateMapCollision(Player *player, Tile ***tiles, int matrix_length, int TILE_SIZE){

    Rectangle player_rect = (Rectangle){player->position.x, player->position.y, TILE_SIZE-2, TILE_SIZE-5};

    for (int i = 1; i < num_matrices; i++){
            for (int j = 0; j < matrix_length; j++){
                for (int k = 0; k < matrix_length; k++){
                    if (tiles[i][j][k].isValid){
                        if (CheckCollisionRecs(player_rect, tiles[i][j][k].rect)){
                            player->position = player->last_position;
                        }
                    }
                }
            }
            
            


                
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



void DrawFullMap(Tile ***tiles, Camera2D camera){
    for (int i = 0; i < num_matrices; i++) DrawTileMap(tiles[i], camera);
}


