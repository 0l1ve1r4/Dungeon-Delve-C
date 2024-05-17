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

#ifndef MENU_H
#define MENU_H

#include "defs.h"
#include "map/maps.h"
#include "utils/utils.h"

#define BACKGROUND_COLOR {1, 1, 26, 255}
#define MAP_MAX_SIZE 500
#define MAX_SEED 99999999

#define LOGO_PATH "res/static/background.png"
#define WALL_PATH "res/static/wall.png"
#define FIRE_ANIM_PATH "res/static/fire.gif"
#define RAIN_ANIM_PATH "res/static/rain.gif"

#define BACKGROUND_MENU_MUSIC "res/sounds/menu_background.mp3"
#define CHANGE_OPTION_SOUND "res/static/change_option.mp3"
#define SELECT_OPTION_SOUND "res/static/select.mp3"
#define LIGHTNING_SOUND "res/static/lightning.mp3"

#define MAX_OPTIONS 4
#define MAX_INPUT_CHARS 9

typedef enum {
    OPTION_SINGLEPLAYER,
    OPTION_MULTIPLAYER,
    OPTION_OPTIONS,
    OPTION_EXIT
    }    MenuOption;


// Updates

void UpdateRaining(Sound lightning);
void UpdateOptions(MenuOption* selectedOptionPtr, Sound change_option, Sound select_option);


// Draws

void DrawBackground(Texture2D logo, Texture2D wall, Texture2D texFireAnim, Texture2D texRain, int selectedOption);
void DrawOption(const char *text, Rectangle optionRect, Color color);
void DrawAllOptions(int selectedOption);
void DrawWorldSettings(int selectedOption);
void startSinglePlayer(void);

#endif