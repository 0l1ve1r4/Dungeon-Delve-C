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

#include "entity/player.h"
#include "entity/enemy.h"
#include "render/render.h"


int main(void)
{    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(TARGET_FPS);
    
    InitAudioDevice();             
    InitRandomSeed(NULL);

    MapNode* TileMapGraph = menu_screen();

    Color bgColor = BLACK;

    Player *player = InitPlayer(TileMapGraph);
    Camera2D camera = InitPlayerCamera(player);
    
    Music music = LoadMusicStream("res/sounds/background.mp3");

    PlayMusicStream(music);

    static int current_frame = 0;
    static int frame_counter = 0;
    static float delta_time = 0;

    //=======================================================================================
    // Main game loop
    //=======================================================================================    
    while (!WindowShouldClose())
    {
        //==================================================================================
        // Update
        //
        delta_time = GetFrameTime();
        frame_counter++;
        frame_counter = (frame_counter >= (TARGET_FPS/PLAYER_FRAME_SPEED)) ? 0 : frame_counter;
        current_frame = (frame_counter == 0) ? ((current_frame > 5) ? 0 : current_frame + 1) : current_frame;
        //
        UpdateMusicStream(music); 
        UpdatePlayer(player, delta_time, current_frame);

        

        UpdateEnemiesMap(TileMapGraph, delta_time, current_frame, player);

        UpdatePlayerCamera(&camera, player, delta_time, SCREEN_WIDTH, SCREEN_HEIGHT);
        UpdateMapCollision(player, TileMapGraph);

        //
        //==================================================================================
        // Draw
        BeginDrawing();
            ClearBackground(bgColor);
            
            BeginMode2D(camera);
                    
                RenderMap(TileMapGraph, camera);

                DrawEnemyMap(TileMapGraph);

                DrawPlayer(player);                

                DrawFog(camera, FOG_RADIUS);

            EndMode2D();

            ShowControls();
            GetGameInfo(player);
        EndDrawing();
        //
        //==================================================================================
    }

    //==================================================================================
    CloseWindow();        // Close window and OpenGL context
    //==================================================================================

    return 0;
}
