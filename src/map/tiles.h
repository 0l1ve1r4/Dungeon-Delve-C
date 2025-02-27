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

#ifndef TILES_H
#define TILES_H

#include "../defs.h" // Texture2D

enum TileType {
    VOID_TILE,
    FLOOR_1,
    FLOOR_2,
    FLOOR_3,
    FLOOR_4,
    FLOOR_5,
    FLOOR_6,
    FLOOR_7,
    FLOOR_8,
    WALL_LEFT,
    WALL_MID,
    WALL_RIGHT,
    HOLE,
    FLOOR_STAIRS,
    WALL_HOLE_1,
    WALL_HOLE_2,
    WALL_BANNER,

    
    TILE_TYPE_COUNT //Insert before this

};

const char* TilePaths[TILE_TYPE_COUNT] = {
    "res/frames/void_tile.png",
    "res/frames/floor_1.png",
    "res/frames/floor_2.png",
    "res/frames/floor_3.png",
    "res/frames/floor_4.png",
    "res/frames/floor_5.png",
    "res/frames/floor_6.png",
    "res/frames/floor_7.png",
    "res/frames/floor_8.png",
    "res/frames/wall_left.png",
    "res/frames/wall_mid.png",
    "res/frames/wall_right.png",
    "res/frames/hole.png",
    "res/frames/floor_stairs.png",
    "res/frames/wall_hole_1.png",
    "res/frames/wall_hole_2.png",
    "res/frames/wall_banner.png"
};

Texture2D* InitTiles(void); // Implemented in map_generator.c

#endif // TILES_H