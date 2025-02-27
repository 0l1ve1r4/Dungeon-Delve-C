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

#ifndef PATHS_H
#define PATHS_H

enum PlayerSoundType {
    WALK_1,
    WALK_2,
    WALK_3,
    COUNT_WALK_SOUNDS,
    
    ATTACK_1,
    COUNT_ATTACK_SOUNDS,
    
    SOUNDS_COUNTS //Insert before this

};

char* PlayerSoundPaths[SOUNDS_COUNTS] = {
    "res/sounds/player/walk_1.wav",
    "res/sounds/player/walk_2.wav",
    "res/sounds/player/walk_3.wav",
    "res/sounds/player/attack.wav"
};

#endif // PATHS_H