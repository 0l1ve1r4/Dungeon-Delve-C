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

static bool world_settings = false;
static bool isRaining = false;
static int MAP_SIZE = 100;
static int MAP_SEED = 29072022;
static int verticalCenter = (SCREEN_HEIGHT - 40 * MAX_OPTIONS) / 2;
static float isRainingAlpha = 0.0f;
static MapNode* TileMapGraph = NULL;

const char *defaultOptions[MAX_OPTIONS] = {"SINGLEPLAYER", "MULTIPLAYER", "OPTIONS", "EXIT"};

MapNode* menu_screen(void) {

    int animFrames = 0; 
    uint32_t nextFrameDataOffset = 0;
    uint8_t currentAnimFrame = 0;      
    uint8_t frameDelay = 10;            
    uint8_t frameCounter = 0;

    MenuOption selectedOption = 0;
    MenuOption* selectedOptionPtr = &selectedOption;

    Texture2D logo = LoadTexture(LOGO_PATH);
    Texture2D wall = LoadTexture(WALL_PATH);

    logo.width = 200;
    logo.height = 200;

    Sound change_option = LoadSound(CHANGE_OPTION_SOUND);
    Sound select_option = LoadSound(SELECT_OPTION_SOUND);
    Sound lightning = LoadSound(LIGHTNING_SOUND);

    Color background_color = BACKGROUND_COLOR;
    
    Image fireAnim = LoadImageAnim(FIRE_ANIM_PATH, &animFrames);
    Image rain = LoadImageAnim(RAIN_ANIM_PATH, &animFrames);

    Texture2D texFireAnim = LoadTextureFromImage(fireAnim);
    Texture2D texRain = LoadTextureFromImage(rain);

    Music music = LoadMusicStream(BACKGROUND_MENU_MUSIC);

    PlayMusicStream(music);

    while (!WindowShouldClose()) {  
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
        UpdateOptions(selectedOptionPtr, change_option, select_option);
        //
        //==============================================================================
        // Draw
        //
        //
        BeginDrawing();
        //
        // Draw background
        DrawBackground(logo, wall, texFireAnim, texRain, selectedOption);
        //
        // Rain effect
        DrawCircleGradient(verticalCenter+300, 500, 1000, Fade(WHITE, 0.f), Fade(WHITE, isRainingAlpha));
        //
        //
        // Check what part of the menu to draw
        if (world_settings) DrawWorldSettings(selectedOption);
        else if (!world_settings) DrawAllOptions(selectedOption);
        //
        // Draw fog
        DrawCircleGradient(verticalCenter+300, 0, 1000, Fade(background_color, 0.f), Fade(background_color, 10.0f));    
        //
        EndDrawing();

    if (TileMapGraph != NULL) return TileMapGraph;

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

        if (IsKeyPressed(KEY_ENTER) && !world_settings) {
            PlaySound(select_option);
            switch (selectedOption) {
                
                case OPTION_SINGLEPLAYER:
                    world_settings = true;
                    break;

                case OPTION_MULTIPLAYER:
                    world_settings = true;
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

        else if (IsKeyPressed(KEY_ENTER) && world_settings) {
            PlaySound(select_option);
            switch (selectedOption) {
                case 0:
                    MAP_SIZE += MAP_SIZE >= MAP_MAX_SIZE ? -MAP_MAX_SIZE : 50;
                    break;
                
                case 1:
                    MAP_SEED = rand() % MAX_SEED;
                    break;
                
                case 2:
                    world_settings = false;
                    break;
                
                case 3:
                    startSinglePlayer();
                    break;
            }
        }
    
        *selectedOptionPtr = selectedOption;
}

void UpdateRaining(Sound lightning){

    if (isRainingAlpha > 0.0f) isRainingAlpha -= 0.1f;
    else isRaining = false;


    if (rand()%10000 < 10 && !isRaining && !IsSoundPlaying(lightning)) {
            PlaySound(lightning);        
            isRaining = true;
            isRainingAlpha = 3.0f;
        }

}

void DrawBackground(Texture2D logo, Texture2D wall, Texture2D texFireAnim, Texture2D texRain, int selectedOption){


        ClearBackground((Color)BACKGROUND_COLOR);

        int fire_y = (selectedOption - 1.3) * 60;

        DrawTexture(texRain, verticalCenter-250, 0, WHITE);
        DrawTexture(logo, verticalCenter+240, 10, WHITE);
        DrawTexture(texFireAnim, verticalCenter+130, verticalCenter + fire_y, WHITE);
        DrawTexture(texFireAnim, verticalCenter+480, verticalCenter + fire_y, WHITE);

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
        Vector2 rectPos = {SCREEN_WIDTH / 2 - 200, verticalCenter + 60 * i};
        Rectangle optionRect = {rectPos.x, rectPos.y, 400, 40};
        

        Color color = i == selectedOption ? RED : ColorFromNormalized((Vector4){0.44f, 0.44f, 0.44f, 1.0f});
        DrawOption(defaultOptions[i], optionRect, color);
    }
}

void DrawWorldSettings(int selectedOption){
    char option_1[20], option_2[20];
    sprintf(option_1, "MAP SIZE: %i", MAP_SIZE);
    sprintf(option_2, "MAP SEED: %i", MAP_SEED);

    const char *drawWorldOptions[MAX_OPTIONS] = {option_1, option_2, "BACK", "START GAME"};

    for (int i = 0; i < MAX_OPTIONS; i++) {
        Vector2 rectPos = {SCREEN_WIDTH / 2 - 200, verticalCenter + 60 * i};
        Rectangle optionRect = {rectPos.x, rectPos.y, 400, 40};

        Color color = i == selectedOption ? RED : ColorFromNormalized((Vector4){0.44f, 0.44f, 0.44f, 1.0f});
        DrawOption(drawWorldOptions[i], optionRect, color);
    }
}
void startSinglePlayer(void){
    InitRandomSeed((void*)MAP_SEED);
    TileMapGraph = InitMap(MAP_SIZE);
}