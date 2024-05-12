#include "raylib.h"
#include "raymath.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>    
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>

#define false 0
#define true 1


#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 650
#define SCREEN_TITLE "Dungeon Delve C"
#define TARGET_FPS 120

//==============================================================================
// Player definitions
//==============================================================================

#define PLAYER_TILE_VISIBILITY  200   
#define PLAYER_SPEED 100.0f
#define PLAYER_FRAME_SPEED 10

#define FRONT_IDLE_ANIMATION 0
#define SIDE_IDLE_ANIMATION 1
#define BACK_IDLE_ANIMATION 2

#define FRONT_WALK_ANIMATION 3
#define SIDE_WALK_ANIMATION 4
#define BACK_WALK_ANIMATION 5

#define FRONT_ATTACK_ANIMATION 6
#define SIDE_ATTACK_ANIMATION 7
#define BACK_ATTACK_ANIMATION 8

#define DEAD_ANIMATION 9


#define MAP_LENGTH 100 // Vector[length x length]
#define __TILE_SIZE 16
#define __PLAYER_SIZE 32
#define RENDER_DISTANCE 13


// TILES PATHS //
#define GRASS_TILE_PATH "res/tiles/grass.png"
#define BUSH_TILE_PATH "res/tiles/bush.png"
#define ROCK1_TILE_PATH "res/tiles/rock1.png"
#define ROCK2_TILE_PATH "res/tiles/rock2.png"
#define WOOD_TILE_PATH "res/tiles/wood.png"