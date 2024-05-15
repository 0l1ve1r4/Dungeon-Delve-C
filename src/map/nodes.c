#include "nodes.h"

MapNode* createNode(Tile** tiles, int node_id, int node_length){ 

    MapNode* node = (MapNode*)malloc(sizeof(MapNode));
    if (!node) debug_log("Error creating node", "ERROR");

    node->node_id = node_id;
    node->node_length = node_length;
    node->tiles = tiles;
    node->next = NULL;

    return node;

}

void insertNode(MapNode* nodes, Tile** tiles, int node_id, int node_length){

    MapNode* new_node = createNode(tiles, node_id, node_length);

    while (nodes->next != NULL){
        nodes = nodes->next;
    }

    nodes->next = new_node;

}

void printNodes(MapNode* nodes){

    while (nodes != NULL){

        printf("Node ID: %d\n", nodes->node_id);
        printf("Texture Path: %s\n", nodes->tiles[0][0].texturePath);

    nodes = nodes->next;
    
}

}