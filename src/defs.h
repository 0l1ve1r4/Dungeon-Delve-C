#include "raylib.h"
#include "raymath.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define false 0
#define true 1


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define SCREEN_TITLE "Dungeon Delve C"
#define TARGET_FPS 6000

#define PLAYER_SPEED 200.0f
#define PLAYER_FRAME_SPEED 6

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


#define MAP_LENGTH 100000 // Vector[length x length]