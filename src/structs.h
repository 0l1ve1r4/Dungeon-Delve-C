#ifndef STRUCTS_H
#define STRUCTS_H

#include "defs.h"

typedef struct {
    
    Vector2 position;   // Position of the player (x, y)
    Vector2 last_position;
    Texture2D texture;  // Texture to represent the player
    Rectangle frameRec; // Sprite frame rectangle

    int last_animation;
    
    float speed;
    

} Player;

typedef struct {
    
    Vector2 position;   // Position of the tile (x, y)
    Texture2D texture;    
    Rectangle rect;
    
    bool isValid;
    bool blocking;

} Tile;





#endif // STRUCTS_H