// This file is part of DungeonDelveC.
// Copyright (C) 2024 Guilherme Oliveira Santos

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

#ifndef STRUCTS_H
#define STRUCTS_H

#include "defs.h"

typedef struct {
    
    Vector2 spawn_point;    // Spawn point of the player (Used to remove collision with the player)
    Vector2 position;       // Position of the current loop of the player
    Vector2 last_position;  // Used to store the last position of the player for collision detection
    Texture2D texture;      // Texture to represent the player
    Rectangle frameRec;     // Sprite frame rectangle (Used to animate the player)
    
    Sound walk_1;           // Sound of the player walking
    Sound walk_2;           // Sound of the player walking

    int last_animation;     // Last animation of the player
    int current_animation;  // Current animation of the player
    int speed;              // Speed of the player
    
    bool isMoving;          // Boolean to check if the player is moving
    bool isAttacking;       // Boolean to check if the player is attacking

} Player;

typedef struct {
    
    Rectangle rect;         // Rectangle of the tile (Used for collision detection)
    bool blocking;          // Used to check if the tile can block entities
    bool isBreakable;       // Used to check if the tile can be broken


} Tile;

typedef struct MapNode{

    int node_id;            // ID of the node, will be used in the future to identify new maps when the player uses a stair  
    int matrix_width;       // Width of the matrix
    int matrix_height;      // Height of the matrix 
                            // The height and width are the same because the map is a square
    int** matrix;           // Matrix is used to store the map layout (0:void, (1-8): floor, (9-11): wall, etc.)

    Vector2** positions;    // Positions of the each tile in the map, calculated with: (x * tile_size, y * tile_size)
    Tile** tile_info;       // Tile info is used to store the tile information (blocking, breakable, etc.)
    Texture2D* textures;    // Textures of the tiles

} MapNode;


#endif // STRUCTS_H