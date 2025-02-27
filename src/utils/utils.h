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

#ifndef UTILS_H
#define UTILS_H

#include "../defs.h"
#include "../structs.h"
#include "../entity/player.h"
#include "../menu.h"

#include <time.h>
#include <sys/types.h>
#include <unistd.h>

void debug_log(char *message, char* escape_code);

// GAME INFO - FUNCTIONS //
void GetGameInfo(Player* player,  MenuData* MapInfo);
void ShowControls(void);
void InitRandomSeed(void* value);
void DrawFog(Camera2D camera, int radius);
void UpdateFrameValues(int* current_frame, int* frame_counter);

unsigned long mix(unsigned long a, unsigned long b, unsigned long c);
#endif