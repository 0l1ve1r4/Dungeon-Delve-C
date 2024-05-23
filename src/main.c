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
#include "render/render.h"

void UpdateGameVariables(GameVariables *game_variables);

int main(void)
{    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(TARGET_FPS);
    InitAudioDevice();             

    MapNode* TileMap = menu_screen();
    Player* Player = InitPlayer(TileMap);
    Camera2D Camera = InitPlayerCamera(Player);
    GameVariables* GameVar = &(GameVariables){ .update = UpdateGameVariables };

    Music music = LoadMusicStream(BACKGROUND_MUSIC);

    PlayMusicStream(music);
    InitRandomSeed(NULL);

    //=======================================================================================
    // Main game loop
    //=======================================================================================    
    while (!WindowShouldClose())
    {
        //==================================================================================
        // Update
        //
        //
        UpdateMusicStream(music);
        //
        GameVar->update(GameVar); 
        Player->update(Player, GameVar->delta_time, GameVar->current_frame);
        Player->updateCamera(&Camera, Player, GameVar->delta_time, SCREEN_WIDTH, SCREEN_HEIGHT);
        TileMap->updateEnemies(TileMap, GameVar->delta_time, GameVar->current_frame, Player);
        TileMap->updateCollisions(Player, TileMap);
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
    free(TileMap);
    free(Player);
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();        // Close window and OpenGL context
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
