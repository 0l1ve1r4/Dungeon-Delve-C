#ifndef STRUCTS_H
#define STRUCTS_H

#include "defs.h"

enum { STATE_WAITING, STATE_LOADING, STATE_FINISHED };
typedef enum {
    MENU_START_GAME,
    MENU_OPTIONS,
    MENU_QUIT
} MenuOption;

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
    
    Vector2 position;   // Position of the tile (x, y)
    Texture2D texture;    
    Rectangle rect;
    Sound break_sound;

    char* texturePath;
    bool isValid;
    bool blocking;

} Tile;


// Linked list 
typedef struct MapNode{

    int node_id;
    int node_length;
    
    Tile** tiles; // Matrix    
    struct MapNode* next;
     
} MapNode;


#endif // STRUCTS_H