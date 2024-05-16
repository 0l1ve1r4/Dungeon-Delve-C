#ifndef MAPS_H
#define MAPS_H

#include "../defs.h"
#include "../structs.h"

Vector2** SetTilePosition(int matrix_length, int tile_size);
MapNode* InitMap(int map_size);

void generateMap(MapNode* TileMap);
void generateWalls(MapNode* TileMap);
void generateBorders(MapNode* TileMap);
void printMap(int** map, int WIDTH, int HEIGHT);


#endif // MAP_H