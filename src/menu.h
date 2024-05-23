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

typedef struct {
    bool isRaining;
    bool isInWorldSettings;
    int MapSize;
    int MapSeed;
    int MaxSeed;
    int MapMaxSize;
    int selectedOption;
    int verticalCenter;
    float RainingAlpha;
    MapNode* TileMapGraph;
    Color backgroundColor;
} MenuData;

typedef struct {
    Texture2D logoTexture;
    Texture2D wallTexture;
    Sound changeOptionSound;
    Sound selectOptionSound;
    Sound lightningSound;
    Image fireAnimImage;
    Image rainAnimImage;
    Texture2D fireAnimTexture;
    Texture2D rainAnimTexture;
    Music backgroundMusic;
} MenuFiles;

#define INIT_MENU_DATA(void) ((MenuData){                       \
    .isRaining = false,                                         \
    .isInWorldSettings = false,                                 \
    .MapSize = 100,                                             \
    .MapSeed = 29072022,                                        \
    .MaxSeed = 99999999,                                        \
    .MapMaxSize = 500,                                          \
    .selectedOption = 0,                                        \
    .verticalCenter = (SCREEN_HEIGHT - 40 * MAX_OPTIONS) / 2,   \
    .RainingAlpha = 0,                                          \
    .TileMapGraph = NULL,                                       \
    .backgroundColor = (Color){1, 1, 26, 255},                  \
})

#define INIT_MENU_FILES(animFrames) ((MenuFiles){               \
    .logoTexture = LoadTexture(LOGO_PATH),                      \
    .wallTexture = LoadTexture(WALL_PATH),                      \
    .logoTexture.width = 200,                                   \
    .logoTexture.height = 200,                                  \
    .changeOptionSound = LoadSound(CHANGE_OPTION_SOUND),        \
    .selectOptionSound = LoadSound(SELECT_OPTION_SOUND),        \
    .lightningSound = LoadSound(LIGHTNING_SOUND),               \
    .fireAnimImage = LoadImageAnim(FIRE_ANIM_PATH, &animFrames),\
    .rainAnimImage = LoadImageAnim(RAIN_ANIM_PATH, &animFrames),\
    .backgroundMusic = LoadMusicStream(BACKGROUND_MENU_MUSIC)   \
})

typedef enum {
    OPTION_SINGLEPLAYER,
    OPTION_MULTIPLAYER,
    OPTION_OPTIONS,
    OPTION_EXIT
    }    MenuOption;


// Updates
MenuData* menu_screen(void);
void UpdateRaining(Sound lightning);
void UpdateOptions(MenuOption* selectedOptionPtr, Sound change_option, Sound select_option);


// Draws

void DrawBackground(Texture2D logo, Texture2D wall, Texture2D texFireAnim, Texture2D texRain, int selectedOption);
void DrawOption(const char *text, Rectangle optionRect, Color color);
void DrawAllOptions(int selectedOption);
void DrawWorldSettings(int selectedOption);
void startSinglePlayer(void);

#endif