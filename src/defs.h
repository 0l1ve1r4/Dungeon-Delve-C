// This file is part of DungeonDelveC.
// Copyright (C) 2024 - 2025 Guilherme Oliveira Santos

// DungeonDelveC is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
#include <unistd.h>
#include <stdint.h>
//
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof(arr[0]))
#define GAME_VERSION "VERSION: 0.1.1"

/* Values witch the game were built */
#define BASE_SCREEN_WIDTH  1400.0
#define BASE_SCREEN_HEIGHT 750.0
#define BASE_FOG_RADIUS    250.0

/* Player Values */
#define SCREEN_WIDTH 1400
#define SCREEN_HEIGHT 750
#define SCALE_FACTOR sqrt((SCREEN_WIDTH * SCREEN_HEIGHT) / (BASE_SCREEN_WIDTH * BASE_SCREEN_HEIGHT))
#define FOG_RADIUS  BASE_FOG_RADIUS * SCALE_FACTOR

#define SCREEN_TITLE "Dungeon Delve C"
#define TARGET_FPS 120
#define __TILE_SIZE 16

#define GLOBAL_FRAME_SPEED 12
#define BACKGROUND_MUSIC "res/sounds/background.mp3"
//
//==============================================================================
#endif