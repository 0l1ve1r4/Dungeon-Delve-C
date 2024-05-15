#include "maps.h"

MapNode* CreateMap(void){

    Tile** grass = CreateTileMap(GRASS_BREAK, GRASS_TILE_PATH, GRASS_SPAWN, GRASS_TILE_SOUND);
    Tile** bush = CreateTileMap(BUSH_BREAK, BUSH_TILE_PATH, BUSH_SPAWN, BUSH_TILE_SOUND);
    Tile** rock1 = CreateTileMap(ROCK1_BREAK, ROCK1_TILE_PATH, ROCK1_SPAWN, ROCK1_TILE_SOUND);
    Tile** rock2 = CreateTileMap(ROCK2_BREAK, ROCK2_TILE_PATH, ROCK2_SPAWN, ROCK2_TILE_SOUND);
    Tile** wood = CreateTileMap(WOOD_BREAK, WOOD_TILE_PATH, WOOD_SPAWN, WOOD_TILE_SOUND);

    MapNode* nodes = createNode(grass, 0, MAP_LENGTH);
    insertNode(nodes, bush, 1, MAP_LENGTH);
    insertNode(nodes, rock1, 2, MAP_LENGTH);
    insertNode(nodes, rock2, 3, MAP_LENGTH);
    insertNode(nodes, wood, 4, MAP_LENGTH);

    removeDuplicatesSprites(nodes);

    return nodes;

}

void removeDuplicatesSprites(MapNode* map){

    MapNode* current = map->next; // Skip the first node (floor tiles)
    MapNode* next = current->next;
    
    
    uint16_t spawn_x = map->node_length / 2;
    uint16_t spawn_y = map->node_length / 2;



    while(next != NULL){

        current->tiles[spawn_x][spawn_y].isValid = false;

        for (int i = 0; i < map->node_length; i++)
            for (int j = 0; j < map->node_length; j++)
                if (current->tiles[i][j].isValid && next->tiles[i][j].isValid)
                    next->tiles[i][j].isValid = false;
                            
    current = current->next;
    next = current->next;
    
    }

    return;

}

/*
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
}*/