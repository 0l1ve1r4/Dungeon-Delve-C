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

#ifndef MAPS_H
#define MAPS_H
//
#include "../defs.h"
#include "../structs.h"
//
//====== maps.c ====================================================================================//
//
Vector2** SetTilePosition(int matrix_length, int tile_size);
MapNode* InitMap(int MapSize);
//
//====== map_generator.c ===========================================================================//
//
void GenerateMap(MapNode* TileMap);
//
void InitWalls(MapNode* TileMap);
bool IsSurroundedByFloor(MapNode *TileMap, int i, int j);
void ClearSpawnPoint(MapNode* TileMap);
void InitObjects(MapNode* TileMap);
void InitBorders(MapNode* TileMap);
void GetTileInfo(MapNode *TileMap);
//
//==================================================================================================//
//
#endif // MAP_H