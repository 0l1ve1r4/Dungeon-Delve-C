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

static MenuData* menuDataPtr;
static MenuFiles* menuFilesPtr;



const char *defaultOptions[MAX_OPTIONS] = {"SINGLEPLAYER", "MULTIPLAYER", "OPTIONS", "EXIT"};

MenuData* menu_screen(void) {

    int animFrames = 0; 
    uint32_t nextFrameDataOffset = 0;
    uint8_t currentAnimFrame = 0;      
    uint8_t frameDelay = 10;            
    uint8_t frameCounter = 0;

    menuDataPtr = &INIT_MENU_DATA();
 

    ///===================================================================================================
    


    Texture2D logo = LoadTexture(LOGO_PATH);
    Texture2D wall = LoadTexture(WALL_PATH);

    logo.width = 200;
    logo.height = 200;

    Sound change_option = LoadSound(CHANGE_OPTION_SOUND);
    Sound select_option = LoadSound(SELECT_OPTION_SOUND);
    Sound lightning = LoadSound(LIGHTNING_SOUND);

    SetSoundVolume(change_option, 0.1f);
    SetSoundVolume(select_option, 0.1f);
    
    Image fireAnim = LoadImageAnim(FIRE_ANIM_PATH, &animFrames);
    Image rain = LoadImageAnim(RAIN_ANIM_PATH, &animFrames);

    Texture2D texFireAnim = LoadTextureFromImage(fireAnim);
    Texture2D texRain = LoadTextureFromImage(rain);

    Music music = LoadMusicStream(BACKGROUND_MENU_MUSIC);
    SetMusicVolume(music, 0.5f);

    PlayMusicStream(music);

    while (1) {  
        //==============================================================================
        // Update
        // 
        frameCounter++;
        if (frameCounter >= frameDelay) {
            currentAnimFrame = (currentAnimFrame + 1) % animFrames;
            nextFrameDataOffset = fireAnim.width * fireAnim.height * 4 * currentAnimFrame;
            UpdateTexture(texFireAnim, ((unsigned char *)fireAnim.data) + nextFrameDataOffset);
            UpdateTexture(texRain, ((unsigned char *)rain.data) + nextFrameDataOffset);
            frameCounter = 0;
        }
        //
        //
        UpdateMusicStream(music);
        UpdateRaining(lightning);
        UpdateOptions(&menuDataPtr->selectedOption, change_option, select_option);
        //
        //==============================================================================
        // Draw
        //
        //
        BeginDrawing();
        //
        // Draw background
        DrawBackground(logo, wall, texFireAnim, texRain, menuDataPtr->selectedOption);
        //
        // Rain effect
        DrawCircleGradient(menuDataPtr->verticalCenter+300, 500, 1000, Fade(WHITE, 0.f), Fade(WHITE, menuDataPtr->RainingAlpha));
        //
        //
        // Check what part of the menu to draw
        if (menuDataPtr->isInWorldSettings) DrawWorldSettings(menuDataPtr->selectedOption);
        else if (!menuDataPtr->isInWorldSettings) DrawAllOptions(menuDataPtr->selectedOption);
        //
        // Draw fog
        DrawCircleGradient(menuDataPtr->verticalCenter+300, 0, 1000, Fade(menuDataPtr->backgroundColor, 0.f), Fade(menuDataPtr->backgroundColor, 10.0f));    
        //
        EndDrawing();

    if (menuDataPtr->TileMapGraph != NULL) return menuDataPtr;

    }

    CloseWindow();

    return 0;
}


void UpdateOptions(MenuOption* selectedOptionPtr, Sound change_option, Sound select_option){

        MenuOption selectedOption = *selectedOptionPtr;

        if (IsKeyPressed(KEY_DOWN)) {
            selectedOption = (selectedOption + 1) % MAX_OPTIONS;
            PlaySound(change_option);

        } else if (IsKeyPressed(KEY_UP)) {
            selectedOption = (selectedOption - 1 + MAX_OPTIONS) % MAX_OPTIONS;
            PlaySound(change_option);
        }

        if (IsKeyPressed(KEY_ENTER) && !menuDataPtr->isInWorldSettings) {
            PlaySound(select_option);
            switch (selectedOption) {
                
                case OPTION_SINGLEPLAYER:
                    menuDataPtr->isInWorldSettings = true;
                    break;

                case OPTION_MULTIPLAYER:
                    menuDataPtr->isInWorldSettings = true;
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

        else if (IsKeyPressed(KEY_ENTER) && menuDataPtr->isInWorldSettings) {
            PlaySound(select_option);
            switch (selectedOption) {
                case 0:
                    menuDataPtr->MapSize += menuDataPtr->MapSize >= menuDataPtr->MapMaxSize ? -menuDataPtr->MapMaxSize : 50;
                    break;
                
                case 1:
                    menuDataPtr->MapSeed = rand() % menuDataPtr->MaxSeed;
                    break;
                
                case 2:
                    menuDataPtr->isInWorldSettings = false;
                    break;
                
                case 3:
                    startSinglePlayer();
                    break;
            }
        }
    
        *selectedOptionPtr = selectedOption;
}

void UpdateRaining(Sound lightning){

    if (menuDataPtr->RainingAlpha > 0.0f) menuDataPtr->RainingAlpha -= 0.1f;
    else menuDataPtr->isRaining = false;


    if (rand()%10000 < 10 && !menuDataPtr->isRaining && !IsSoundPlaying(lightning)) {
            PlaySound(lightning);        
            menuDataPtr->isRaining = true;
            menuDataPtr->RainingAlpha = 3.0f;
        }

}

void DrawBackground(Texture2D logo, Texture2D wall, Texture2D texFireAnim, Texture2D texRain, int selectedOption){


        ClearBackground((Color)menuDataPtr->backgroundColor);

        int fire_y = (selectedOption - 1.3) * 60;

        DrawTexture(texRain, menuDataPtr->verticalCenter-250, 0, WHITE);
        DrawTexture(logo, menuDataPtr->verticalCenter+240, 10, WHITE);
        DrawTexture(texFireAnim, menuDataPtr->verticalCenter+130, menuDataPtr->verticalCenter + fire_y, WHITE);
        DrawTexture(texFireAnim, menuDataPtr->verticalCenter+480, menuDataPtr->verticalCenter + fire_y, WHITE);

        for (int i = SCREEN_HEIGHT/ 2 + 290; i < SCREEN_HEIGHT; i += __TILE_SIZE)
            for (int j = 0; j < SCREEN_WIDTH; j += __TILE_SIZE)
                DrawTexture(wall, j, i, WHITE);        

        DrawText("Developed by Guilherme Santos", SCREEN_HEIGHT/2 + 100, SCREEN_HEIGHT - 20, 20, WHITE);
        DrawText(GAME_VERSION, SCREEN_WIDTH - 200, SCREEN_HEIGHT - 20, 20, WHITE);

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
        Vector2 rectPos = {SCREEN_WIDTH / 2 - 200, menuDataPtr->verticalCenter + 60 * i};
        Rectangle optionRect = {rectPos.x, rectPos.y, 400, 40};
        

        Color color = i == selectedOption ? RED : ColorFromNormalized((Vector4){0.44f, 0.44f, 0.44f, 1.0f});
        DrawOption(defaultOptions[i], optionRect, color);
    }
}

void DrawWorldSettings(int selectedOption){
    char option_1[20], option_2[20];
    sprintf(option_1, "MAP SIZE: %i", menuDataPtr->MapSize);
    sprintf(option_2, "MAP SEED: %i", menuDataPtr->MapSeed);

    const char *drawWorldOptions[MAX_OPTIONS] = {option_1, option_2, "BACK", "START GAME"};

    for (int i = 0; i < MAX_OPTIONS; i++) {
        Vector2 rectPos = {SCREEN_WIDTH / 2 - 200, menuDataPtr->verticalCenter + 60 * i};
        Rectangle optionRect = {rectPos.x, rectPos.y, 400, 40};

        Color color = i == selectedOption ? RED : ColorFromNormalized((Vector4){0.44f, 0.44f, 0.44f, 1.0f});
        DrawOption(drawWorldOptions[i], optionRect, color);
    }
}

void startSinglePlayer(void){
    InitRandomSeed((void*)menuDataPtr->MapSeed);
    menuDataPtr->TileMapGraph = InitMap(menuDataPtr->MapSize);
    menuDataPtr->TileMapGraph->updateEnemies = &UpdateEnemiesMap;
    menuDataPtr->TileMapGraph->updateCollisions = &UpdateMapCollision;
    menuDataPtr->TileMapGraph->drawEnemies = &DrawEnemyMap;
    menuDataPtr->TileMapGraph->drawMap = &RenderMap;
}