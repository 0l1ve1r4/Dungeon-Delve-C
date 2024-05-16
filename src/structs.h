#ifndef STRUCTS_H
#define STRUCTS_H

#include "defs.h"

typedef struct {
    
    Vector2 spawn_point;
    Vector2 position;   // Position of the player (x, y)
    Vector2 last_position;
    Texture2D texture;  // Texture to represent the player
    Rectangle frameRec; // Sprite frame rectangle
    Sound walk;

    int last_animation;
    int current_animation;
    int speed;
    
    bool isMoving;
    bool isAttacking;

} Player;

typedef struct {
    
    Rectangle rect;
    bool blocking;
    bool isBreakable;


} Tile;


// Linked list 
typedef struct MapNode{

    int node_id;
    int matrix_width;
    int matrix_height;
    
    int** matrix;

    Vector2** positions;
    Tile** tile_info;
    Texture2D* textures;

} MapNode;


#endif // STRUCTS_H