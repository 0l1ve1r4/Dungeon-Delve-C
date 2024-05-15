#include "maps.h"

MapNode* CreateMap(void){

    Tile** grass = CreateTileMap(false, MAP_LENGTH, __TILE_SIZE, GRASS_TILE_PATH, 100, "res/sounds/break_grass.mp3");
    Tile** bush = CreateTileMap(true, MAP_LENGTH, __TILE_SIZE, BUSH_TILE_PATH, 20, "res/sounds/break_grass.mp3");
    Tile** rock1 = CreateTileMap(true, MAP_LENGTH, __TILE_SIZE, ROCK1_TILE_PATH, 1, "res/sounds/break_stone.mp3");
    Tile** rock2 = CreateTileMap(true, MAP_LENGTH, __TILE_SIZE, ROCK2_TILE_PATH, 1, "res/sounds/break_stone.mp3");
    Tile** wood = CreateTileMap(true, MAP_LENGTH, __TILE_SIZE, WOOD_TILE_PATH, 1, "res/sounds/break_wood.mp3");

    MapNode* nodes = createNode(grass, 0, MAP_LENGTH);
    insertNode(nodes, bush, 1, MAP_LENGTH);
    insertNode(nodes, rock1, 2, MAP_LENGTH);
    insertNode(nodes, rock2, 3, MAP_LENGTH);
    insertNode(nodes, wood, 4, MAP_LENGTH);

    return nodes;

}