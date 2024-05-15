#ifndef NODES_H
#define NODES_H

#include "../defs.h"
#include "../structs.h"
#include "../utils/utils.h"
#include "tiles.h"

MapNode* createNode(Tile** tiles, int node_id, int node_length);
void insertNode(MapNode* nodes, Tile** tiles, int node_id, int node_length);
void printNodes(MapNode* nodes);

#endif // NODES_H