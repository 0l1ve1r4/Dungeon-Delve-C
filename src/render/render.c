#include "render.h"

static int num_matrices = 5;

Tile InitTile(int x, int y, int isBlocking, char *texturePath, int TILE_SIZE, int probability){

    Tile tile;

    int random = rand() % 100;
    if (random > probability) return tile;

    tile.position = (Vector2){ x, y };
    tile.texture = LoadTexture(texturePath);
    tile.texture.width = TILE_SIZE;
    tile.texture.height = TILE_SIZE;

    tile.rect = (Rectangle){ x, y, tile.texture.width, tile.texture.height };

    tile.blocking = isBlocking;

    return tile;
}

Tile* InitTiles(Vector2 *positions, int length, char *texturePath, int TILE_SIZE){

    Tile *tiles = (Tile*)malloc(sizeof(Tile) * length);

    for (int i = 0; i < length; i++){
        tiles[i] = InitTile(positions[i].x, positions[i].y, 0, texturePath, TILE_SIZE, 100);
    }

    return tiles;

}

Tile** InitMatrixTiles(Vector2** positions, int length, char *texturePath, int TILE_SIZE, int probability){

    Tile **tiles = (Tile**)malloc(sizeof(Tile*) * length);
    
    for (int i = 0; i < length; i++) 
        tiles[i] = (Tile*)malloc(sizeof(Tile) * length);
    
    for (int i = 0; i < length; i++){
        for (int j = 0; j < length; j++){
            tiles[i][j] = InitTile(positions[i][j].x, positions[i][j].y, 0, texturePath, TILE_SIZE, probability);
        }
    }

    return tiles;
}

Tile** CreateTileMap(int length, int TILE_SIZE, char* tilePath, int probability){

    Vector2** TilesPositions = (Vector2**)malloc(sizeof(Vector2*) * length);
    for (int i = 0; i < length; i++) {
        TilesPositions[i] = (Vector2*)malloc(sizeof(Vector2) * length);
    }

    for (int i = 0; i < length; i++){
        for (int j = 0; j < length; j++){
            int pos_x = j * TILE_SIZE;
            int pos_y = i * TILE_SIZE;
            TilesPositions[i][j] = (Vector2){pos_x, pos_y};
        }
    }

    Tile **tiles = InitMatrixTiles(TilesPositions, length, tilePath, TILE_SIZE, probability);

    for (int i = 0; i < length; i++) {
        free(TilesPositions[i]);
    }
    free(TilesPositions);

    return tiles;
}



void DrawTileMap(Tile **tiles){
    for(int i = 0; i < MAP_LENGTH; i++){
        for(int j = 0; j < MAP_LENGTH; j++)
            DrawTextureRec(tiles[i][j].texture, tiles[i][j].rect, tiles[i][j].position, WHITE);
    }
}


Tile*** CreateMap(int length, int tile_size){

    Tile*** TileMaps = (Tile***)malloc(sizeof(Tile**) * num_matrices);

    Tile** GrassTileMap = CreateTileMap(length, tile_size, GRASS_TILE_PATH, 100);
    Tile** BushTileMap = CreateTileMap(length, tile_size, BUSH_TILE_PATH, 5);   
    Tile** Rock1TileMap = CreateTileMap(length, tile_size, ROCK1_TILE_PATH, 1);
    Tile** Rock2TileMap = CreateTileMap(length, tile_size, ROCK2_TILE_PATH, 1);
    Tile** WoodTileMap = CreateTileMap(length, tile_size, WOOD_TILE_PATH, 1);

    TileMaps[0] = GrassTileMap;
    TileMaps[1] = BushTileMap;
    TileMaps[2] = Rock1TileMap;
    TileMaps[3] = Rock2TileMap;
    TileMaps[4] = WoodTileMap;

    // Use the tileMaps vector as needed

    return TileMaps;

};

void DrawFullMap(Tile ***tiles){
    for (int i = 0; i < num_matrices; i++){
        DrawTileMap(tiles[i]);
    }

    // Dark fog


}


