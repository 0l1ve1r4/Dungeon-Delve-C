#include "render.h"

Tile InitTile(int x, int y, int isBlocking, char *texturePath, int TILE_SIZE){

    Tile tile;

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
        tiles[i] = InitTile(positions[i].x, positions[i].y, 0, texturePath, TILE_SIZE);
    }

    debug_log("Tiles initialized\n", "INFO");

    return tiles;

}

Tile** InitMatrixTiles(Vector2** positions, int length, char *texturePath, int TILE_SIZE){

    Tile **tiles = (Tile**)malloc(sizeof(Tile*) * length);
    for (int i = 0; i < length; i++) {
        tiles[i] = (Tile*)malloc(sizeof(Tile) * length);
    }

    for (int i = 0; i < length; i++){
        for (int j = 0; j < length; j++){
            tiles[i][j] = InitTile(positions[i][j].x, positions[i][j].y, 0, texturePath, TILE_SIZE);
        }
    }

    debug_log("Tiles initialized\n", "INFO");

    return tiles;
}

Tile** CreateGrassTiles(int length, int TILE_SIZE){

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

    Tile **tiles = InitMatrixTiles(TilesPositions, length, "resources/grass.png", TILE_SIZE);

    for (int i = 0; i < length; i++) {
        free(TilesPositions[i]);
    }
    free(TilesPositions);

    return tiles;
}


void DrawTiles(Tile *tiles, int length){

    for (int i = 0; i < length; i++){
        DrawTexture(tiles[i].texture, tiles[i].position.x, tiles[i].position.y, WHITE);
    }


}
