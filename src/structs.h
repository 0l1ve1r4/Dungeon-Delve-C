#ifndef STRUCTS_H
#define STRUCTS_H

#include "defs.h"

typedef struct {
    
    Texture2D texture;
    Vector2 position;
    
    float speed;
} Player;

typedef struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;



#endif // STRUCTS_H