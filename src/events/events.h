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

#ifndef EVENTS_H
#define EVENTS_H

#include "../render/render.h"
#include "../map/maps.h"
#include "../menu.h"

int PauseEvent(void);
void LoadingWindow(void);

void StartPlayerOnNewMap(Player* player, int collisionType, MenuData* MapInfo,  MapNode* TileMap);
void handleOptionSelection(MenuData* menuData, MenuSounds* menuSounds);
void handleWorldSettings(MenuData* menuData, MenuSounds* menuSounds);
void handleDifficultySettings(MenuData* menuData, MenuSounds* menuSounds);
void UpdateOptions(MenuData* menuData, MenuSounds* menuSounds);


#endif // EVENTS_H
