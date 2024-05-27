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

#include "defs.h"
#include "structs.h"
#include "menu.h"

#include "entity/player.h"
#include "entity/enemy.h"
#include "map/maps.h"
#include "render/render.h"
#include "utils/utils.h"


void UpdateGameVariables(GameVariables *game_variables);
void LoadingWindow(void);
MapNode* GenerateNewMap(int map_size);

int main(void)
{    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(TARGET_FPS);
    InitAudioDevice();             

    MenuData* MapInfo = menu_screen();
    MapNode* TileMap = MapInfo->TileMapGraph;

    Player* Player = InitPlayer(TileMap);
    Camera2D Camera = InitPlayerCamera(Player);
    GameVariables* GameVar = &(GameVariables){ .update = UpdateGameVariables };

    Music backgroundMusic = LoadMusicStream(BACKGROUND_MUSIC);

    PlayMusicStream(backgroundMusic);
    InitRandomSeed(NULL);
    LoadingWindow();

    //=======================================================================================
    // Main game loop
    //=======================================================================================    
    while (!WindowShouldClose())
    {
        //==================================================================================
        // Update
        UpdateMusicStream(backgroundMusic);
        //
        GameVar->update(GameVar); 
        Player->update(Player, GameVar->delta_time, GameVar->current_frame);
        Player->updateCamera(&Camera, Player, GameVar->delta_time);
        TileMap->updateEnemies(TileMap, GameVar->delta_time, GameVar->current_frame, Player);
        int cType = TileMap->updateCollisions(Player, TileMap);
        if (cType == STAIR) {
            free(TileMap);
            TileMap = GenerateNewMap(MapInfo->MapSize);
            LoadingWindow();
        }

        //
        //==================================================================================
        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            
            BeginMode2D(Camera);
                    
                TileMap->drawMap(TileMap, Camera);
                TileMap->drawEnemies(TileMap);
                Player->draw(Player);
                DrawFog(Camera, FOG_RADIUS);

            EndMode2D();

            ShowControls();
            GetGameInfo(Player);
        EndDrawing();
        //
        //==================================================================================
    }

    //==================================================================================
    UnloadMusicStream(backgroundMusic);
    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context
    free(TileMap);
    free(Player);
    //==================================================================================

    return 0;
}

void UpdateGameVariables(GameVariables *game_variables) {
    game_variables->delta_time = GetFrameTime();
    game_variables->frame_counter++;

    // Reset the frame counter if it exceeds
    if (game_variables->frame_counter >= (TARGET_FPS/GLOBAL_FRAME_SPEED)) {
        game_variables->frame_counter = 0;
    }

    // Update the current frame
    if (game_variables->frame_counter == 0) {
        if (game_variables->current_frame > 5) {
            game_variables->current_frame = 0;
        } else {
            game_variables->current_frame++;
        }
    }
}

void LoadingWindow(void) {
    time_t start_time = time(NULL);
    int max_loading_seconds = 2;

    while (!WindowShouldClose() && time(NULL) - start_time < max_loading_seconds) {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText("Loading...", SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, 20, WHITE);
        EndDrawing();
    }
}

MapNode* GenerateNewMap(int map_size) {

    MapNode* TileMapGraph = InitMap(map_size);
    TileMapGraph->updateEnemies = &UpdateEnemiesMap;
    TileMapGraph->updateCollisions = &UpdateMapCollision;
    TileMapGraph->drawEnemies = &DrawEnemyMap;
    TileMapGraph->drawMap = &RenderMap;

    return TileMapGraph;
}