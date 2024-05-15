#ifndef DEFS_H
#define DEFS_H

//==============================================================================
// INCLUDES
//
#include "raylib.h"
#include "raymath.h"
#include "structs.h"
// 
// STANDARD LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>    
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>                        // POSIX threads
#include <stdatomic.h>                      // C11 atomic data types
//
//
//
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 650
#define SCREEN_TITLE "Dungeon Delve C"
#define TARGET_FPS 120
//
//==============================================================================
// Player definitions
//
#define FOG_RADIUS  200   
#define PLAYER_SPEED 100.0f
#define PLAYER_FRAME_SPEED 10
//
#define FRONT_IDLE_ANIMATION 0
#define SIDE_IDLE_ANIMATION 1
#define BACK_IDLE_ANIMATION 2
//
#define FRONT_WALK_ANIMATION 3
#define SIDE_WALK_ANIMATION 4
#define BACK_WALK_ANIMATION 5
//
#define FRONT_ATTACK_ANIMATION 6
#define SIDE_ATTACK_ANIMATION 7
#define BACK_ATTACK_ANIMATION 8
//
#define DEAD_ANIMATION 9
//
//
#define MAP_LENGTH 50 // SQUARE MATRIX
#define __TILE_SIZE 16
#define RENDER_DISTANCE 13
//
//==============================================================================
// MAIN FUNCTIONS
MapNode* menu_screen(void);



#endif