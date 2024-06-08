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
#include "render/render.h"
#include "utils/utils.h"
#include "events/events.h"

void UpdateGameVariables(GameVariables*);
void FreeMemory(MenuData* MapInfo);

MapNode* GenerateNewMap(int map_size);

int main(void)
{    
    // ===========================================================================================
    // I dont like to use goto statements, but in this case it is the best easier solution      //
    // to avoid memory leaks and to keep the code clean.                                        //
    //                                                                                          //
    MENU:                                                                                       //
        InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);                                  //
        SetTargetFPS(TARGET_FPS);                                                               //
        InitAudioDevice();                                                                      //
        MenuData* MapInfo = menu_screen();                                                      //
        LoadingWindow();                                                                        //
    //                                                                                          //
    // ===========================================================================================

    GameVariables *GameVar = &(GameVariables){ .update = UpdateGameVariables }; // Not in the heap
    MapNode *TileMap = MapInfo->TileMapGraph;
    Player *Player = InitPlayer(TileMap);
    Camera2D Camera = InitPlayerCamera(Player);

    InitRandomSeed(NULL); // If not changed, always generate the same map

    Music backgroundMusic = LoadMusicStream(BACKGROUND_MUSIC); PlayMusicStream(backgroundMusic);

    //=======================================================================================
    // Main game loop
    //=======================================================================================    
    while (1)
    {
        //==================================================================================
        // Update - This sectin use some function pointers to update the game variables
        UpdateMusicStream(backgroundMusic);

        GameVar->update(GameVar); 
        static uint8_t *PlayerCollisionType;
        PlayerCollisionType = Player->update(Player, GameVar->delta_time, GameVar->current_frame, TileMap);
        Player->updateCamera(&Camera, Player, GameVar->delta_time);
        TileMap->updateEnemies(TileMap, GameVar->delta_time, GameVar->current_frame, Player);
        
        if(*PlayerCollisionType == STAIR || *PlayerCollisionType == HOLE) {
            StartPlayerOnNewMap(Player, *PlayerCollisionType, MapInfo, TileMap);
            *PlayerCollisionType = NO_COLLISION;
        }
        
        // Verify if the player wants to pause the game
        switch (PauseEvent()) {
            case 1:
                FreeMemory(MapInfo); goto MENU; break;
            case 2:
                goto END; break;
        }

        //================================================================================
        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            
            BeginMode2D(Camera);
                
                TileMap->drawMap(TileMap, Camera);  // function pointer
                TileMap->drawEnemies(TileMap);      // function pointer
                Player->draw(Player);               // function pointer
                DrawFog(Camera, FOG_RADIUS);        // static function

            EndMode2D();

            ShowControls();                         // static function
            GetGameInfo(Player, MapInfo);           // static function
        EndDrawing();
        //
        //================================================================================
    }

    //====================================================================================
    // Another goto, be aware of future changes                                         //
    //                                                                                  //
    END:                                                                                //  
        UnloadMusicStream(backgroundMusic);                                             //
        CloseAudioDevice();                                                             //  
        CloseWindow();                                                                  //
        free(TileMap);                                                                  //
        free(MapInfo);                                                                  //
        free(Player);                                                                   //
    //                                                                                  //
    //====================================================================================

    return 0;
}

void UpdateGameVariables(GameVariables *game_variables) {
    game_variables->delta_time = GetFrameTime();
    game_variables->frame_counter++;

    if (game_variables->frame_counter >= (TARGET_FPS/GLOBAL_FRAME_SPEED)) {
        game_variables->frame_counter = 0;
    }

    if (game_variables->frame_counter == 0) {
        if (game_variables->current_frame >= 3) {
            game_variables->current_frame = 0;
        } else {
            game_variables->current_frame++;
        }
    }
}

void FreeMemory(MenuData* MapInfo) {
    free(MapInfo);
    CloseWindow();
    CloseAudioDevice();
    
}
