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
    int animFrames; 
    uint32_t nextFrameDataOffset;
    uint8_t currentAnimFrame;      
    uint8_t frameDelay;            
    uint8_t frameCounter;
    float RainingAlpha;
    MapNode* TileMapGraph;
    Color backgroundColor;
} MenuData;

typedef struct {
    Sound changeOptionSound;
    Sound selectOptionSound;
    Sound lightningSound;
    Music backgroundMusic;
} MenuSounds;

typedef enum {
    OPTION_SINGLEPLAYER,
    OPTION_MULTIPLAYER,
    OPTION_OPTIONS,
    OPTION_EXIT
} MenuOption;

MenuData* menu_screen(void);

// ==============================================================
// INITIALIZATION
void InitSounds(void);
void InitData(void);
//================================================================
// UPDATES
void UpdateRaining(void);
void UpdateOptions(void);
void UpdateFrames(Texture2D, Image, Texture2D, Image);
//================================================================
// DRAWS
void UpdateFrameCounters(MenuData* menuDataPtr, Image fireAnim, Image rain);
void DrawBackground(Texture2D logo, Texture2D wall, Texture2D texFireAnim, Texture2D rainTexture);
void DrawOption(const char *text, Rectangle optionRect, Color color);
void DrawAllOptions(int selectedOption);
void DrawWorldSettings(int selectedOption);
void startSinglePlayer(void);
//================================================================
#endif