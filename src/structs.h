#ifndef STRUCTS_H
#define STRUCTS_H

#include "defs.h"

typedef struct {
    
    Vector2 position;   // Position of the player (x, y)
    Texture2D texture;  // Texture to represent the player
    Rectangle frameRec; // Sprite frame rectangle

    int last_animation;
    
    float speed;
    

} Player;

typedef struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;



#endif // STRUCTS_H