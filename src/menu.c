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

#include "menu.h"
#include "entity/player.h"
#include "entity/enemy.h"
#include "render/render.h"

static MenuData* menuData;
static MenuSounds* menuSounds;
 
const char *defaultOptions[MAX_OPTIONS] = {
    "SINGLEPLAYER", 
    "MULTIPLAYER", 
    "OPTIONS", 
    "EXIT"
};

const char *difficultyOptions[MAX_OPTIONS] = {
    "PYTHON 'DEV'",  
    "JAVA LOVER", 
    "C ENTHUSIAST",
    "I CODE IN ASSEMBLY"
};

const char* worldOptions[MAX_OPTIONS] = {
    "MAP SIZE", 
    "MAP SEED", 
    "BACK", 
    "START GAME"
};


MenuData* menu_screen(void) {


    InitData(); // Menu Variables
    InitSounds(); // Menu Sounds/Music
        
    Texture2D logoTexture = LoadTexture(LOGO_PATH); logoTexture.width = 200; logoTexture.height = 200;
    Texture2D wallTexture = LoadTexture(WALL_PATH); wallTexture.width = 32; wallTexture.height = 32;
    
    Image fireImage = LoadImageAnim(FIRE_ANIM_PATH, &menuData->animFrames); Texture2D fireTexture = LoadTextureFromImage(fireImage);
    Image rainImage = LoadImageAnim(RAIN_ANIM_PATH, &menuData->animFrames); Texture2D rainTexture = LoadTextureFromImage(rainImage);

    PlayMusicStream(menuSounds->backgroundMusic);

    while (1) {  
        UpdateFrames(fireTexture, fireImage, rainTexture, rainImage);
        UpdateMusicStream(menuSounds->backgroundMusic);
        UpdateRaining();
        UpdateOptions();
        //==============================================================================
        // Draw

        BeginDrawing();

        DrawBackground(logoTexture, wallTexture, fireTexture, rainTexture);

        if (menuData->isInWorldSettings) DrawWorldSettings(menuData->selectedOption);
        else if (!menuData->isInWorldSettings) DrawAllOptions(menuData->selectedOption);

        DrawCircleGradient(menuData->verticalCenter+300, 0, 1000, Fade(menuData->backgroundColor, 0.f), Fade(menuData->backgroundColor, 10.0f));    
        //
        EndDrawing();

    if (menuData->TileMapGraph != NULL) return menuData;

    }

    return (void*)(uintptr_t) menuData->TileMapGraph;
}

void InitData(void){
    menuData = (MenuData*)malloc(sizeof(MenuData));
    menuData->isRaining = false;
    menuData->isInWorldSettings = false;
    menuData->MapSize = 100;
    menuData->MapSeed = 29072022;
    menuData->MaxSeed = 99999999;
    menuData->MapMaxSize = 500;
    menuData->selectedOption = 0;
    menuData->verticalCenter = (SCREEN_HEIGHT - 40 * MAX_OPTIONS) / 2;
    menuData->animFrames = 0; 
    menuData->nextFrameDataOffset = 0;
    menuData->currentAnimFrame = 0;      
    menuData->frameDelay = 10;            
    menuData->frameCounter = 0;
    menuData->RainingAlpha = 0;
    menuData->TileMapGraph = NULL;
    menuData->backgroundColor = (Color){1, 1, 26, 255};
}

void InitSounds(void){
    menuSounds = (MenuSounds*)malloc(sizeof(MenuSounds));
    menuSounds->changeOptionSound = LoadSound(CHANGE_OPTION_SOUND),        
    menuSounds->selectOptionSound = LoadSound(SELECT_OPTION_SOUND);        
    menuSounds->lightningSound = LoadSound(LIGHTNING_SOUND);               
    menuSounds->backgroundMusic = LoadMusicStream(BACKGROUND_MENU_MUSIC);   
    SetSoundVolume(menuSounds->selectOptionSound, 0.1f);
    SetSoundVolume(menuSounds->changeOptionSound, 0.1f);  
    SetMusicVolume(menuSounds->backgroundMusic, 0.5f);
}

void UpdateFrames(Texture2D fireTexture, Image fireImage, Texture2D rainTexture, Image rainImage){
    menuData->frameCounter++;
    if (menuData->frameCounter >= menuData->frameDelay) {
        menuData->currentAnimFrame = (menuData->currentAnimFrame + 1) % menuData->animFrames;
        menuData->nextFrameDataOffset = fireImage.width * fireImage.height * 4 * menuData->currentAnimFrame;
            UpdateTexture(fireTexture, ((unsigned char *)fireImage.data) + menuData->nextFrameDataOffset);
            UpdateTexture(rainTexture, ((unsigned char *)rainImage.data) + menuData->nextFrameDataOffset);
            menuData->frameCounter = 0;
        }
}


void UpdateOptions(){

        if (IsKeyPressed(KEY_DOWN)) {
            menuData->selectedOption = (menuData->selectedOption + 1) % MAX_OPTIONS;
            PlaySound(menuSounds->changeOptionSound);

        } else if (IsKeyPressed(KEY_UP)) {
            menuData->selectedOption = (menuData->selectedOption - 1 + MAX_OPTIONS) % MAX_OPTIONS;
            PlaySound(menuSounds->changeOptionSound);
        }

        if (IsKeyPressed(KEY_ENTER) && !menuData->isInWorldSettings) {
            PlaySound(menuSounds->selectOptionSound);
            switch (menuData->selectedOption) {
                
                case OPTION_SINGLEPLAYER:
                    menuData->isInWorldSettings = true;
                    break;

                case OPTION_MULTIPLAYER:
                    menuData->isInWorldSettings = true;
                    break;
                
                case OPTION_OPTIONS:
                    // Implement options logic
                    break;
                
                case OPTION_EXIT:
                    usleep(500000); // Sleep for 0.5 second
                    CloseWindow();
                    break;
            }
        }

        else if (IsKeyPressed(KEY_ENTER) && menuData->isInWorldSettings) {
            PlaySound(menuSounds->selectOptionSound);
            switch (menuData->selectedOption) {
                case 0:
                    menuData->MapSize += menuData->MapSize >= menuData->MapMaxSize ? -menuData->MapMaxSize : 50;
                    break;
                
                case 1:
                    menuData->MapSeed = rand() % menuData->MaxSeed;
                    break;
                
                case 2:
                    menuData->isInWorldSettings = false;
                    break;
                
                case 3:
                    startSinglePlayer();
                    break;
            }
        }
    
}

void UpdateRaining(){

    if (menuData->RainingAlpha > 0.0f && menuData->isRaining) {
        menuData->RainingAlpha -= 0.1f;
        return;
    }

    else menuData->isRaining = false;

    if ( (rand()%10000 < 10) && !menuData->isRaining && !IsSoundPlaying(menuSounds->lightningSound)) {
            PlaySound(menuSounds->lightningSound);        
            menuData->isRaining = true;
            menuData->RainingAlpha = 3.0f;
    }
}

void DrawBackground(Texture2D logoTexture, Texture2D wallTexture, Texture2D fireTexture, Texture2D rainTexture){


        ClearBackground((Color)menuData->backgroundColor);

        int fire_y = (menuData->selectedOption - 1.3) * 60;

        DrawTexture(rainTexture, menuData->verticalCenter-250, 0, WHITE);
        DrawTexture(logoTexture, menuData->verticalCenter+240, 10, WHITE);
        DrawTexture(fireTexture, menuData->verticalCenter+130, menuData->verticalCenter + fire_y, WHITE);
        DrawTexture(fireTexture, menuData->verticalCenter+480, menuData->verticalCenter + fire_y, WHITE);

        for (int i = SCREEN_HEIGHT/ 2 + 290; i < SCREEN_HEIGHT; i += __TILE_SIZE)
            for (int j = 0; j < SCREEN_WIDTH; j += __TILE_SIZE)
                DrawTexture(wallTexture, j, i, WHITE);        

        DrawText("Developed by Guilherme Santos", SCREEN_HEIGHT/2 + 100, SCREEN_HEIGHT - 20, 20, WHITE);
        DrawText(GAME_VERSION, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 20, 20, WHITE);

        DrawCircleGradient(menuData->verticalCenter+300, 500, 1000, Fade(WHITE, 0.f), Fade(WHITE, menuData->RainingAlpha));

}

void DrawOption(const char *text, Rectangle optionRect, Color color) {

    Color background_rect_color = BLACK;
    Rectangle background_rect = {optionRect.x - 2, optionRect.y - 2, optionRect.width + 5, optionRect.height + 5};
    
    if (color.r == RED.r && color.g == RED.g && color.b == RED.b && color.a == RED.a) //3,57,108
        background_rect_color = ColorFromNormalized((Vector4){3.0f, 0.57f, 0.108f, 1.0f});


    DrawRectangleRec(background_rect, background_rect_color);
    DrawRectangleRec(optionRect, color);
    DrawText(text, optionRect.x + 10, optionRect.y + 10, 30, WHITE);
}

void DrawAllOptions(int selectedOption){
    for (int i = 0; i < MAX_OPTIONS; i++) {
        Vector2 rectPos = {SCREEN_WIDTH / 2 - 200, menuData->verticalCenter + 60 * i};
        Rectangle optionRect = {rectPos.x, rectPos.y, 400, 40};
        
        Color color = i == selectedOption ? RED : ColorFromNormalized((Vector4){0.44f, 0.44f, 0.44f, 1.0f});
        DrawOption(defaultOptions[i], optionRect, color);
    }
}

void DrawWorldSettings(int selectedOption){
    char option_1[20], option_2[20];
    sprintf(option_1, "MAP SIZE: %i", menuData->MapSize);
    sprintf(option_2, "MAP SEED: %i", menuData->MapSeed);

    const char *drawWorldOptions[MAX_OPTIONS] = {option_1, option_2, "BACK", "START GAME"};

    for (int i = 0; i < MAX_OPTIONS; i++) {
        Vector2 rectPos = {SCREEN_WIDTH / 2 - 200, menuData->verticalCenter + 60 * i};
        Rectangle optionRect = {rectPos.x, rectPos.y, 400, 40};

        Color color = i == selectedOption ? RED : ColorFromNormalized((Vector4){0.44f, 0.44f, 0.44f, 1.0f});
        DrawOption(drawWorldOptions[i], optionRect, color);
    }
}

void startSinglePlayer(void){
    InitRandomSeed((void*)(uintptr_t)menuData->MapSeed);
    menuData->TileMapGraph = InitMap(menuData->MapSize);
    menuData->TileMapGraph->updateEnemies = &UpdateEnemiesMap;
    menuData->TileMapGraph->updateCollisions = &UpdateMapCollision;
    menuData->TileMapGraph->drawEnemies = &DrawEnemyMap;
    menuData->TileMapGraph->drawMap = &RenderMap;
}