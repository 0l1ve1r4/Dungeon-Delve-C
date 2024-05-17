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

#ifndef RENDER_H
#define RENDER_H

#include "../defs.h"
#include "../structs.h"
#include "../utils/utils.h"
#include "../entity/player.h"


void RenderMap(MapNode* nodes, Camera2D camera);
void UpdateMapCollision(Player *player, MapNode *map);

// CAMERA RELATED - FUNCTIONS //
Camera2D InitPlayerCamera(Player *player);
void UpdatePlayerCamera(Camera2D *camera, Player *player, float delta, int width, int height);




#endif