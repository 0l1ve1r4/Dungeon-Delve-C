#include "defs.h"
#include "structs.h"

#include "entity/player.h"
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


        UpdatePlayerCamera(&camera, player, delta_time, SCREEN_WIDTH, SCREEN_HEIGHT);
        UpdateMapCollision(player, TileMapGraph);

        //
        //==================================================================================
        // Draw
        BeginDrawing();
            ClearBackground(bgColor);
            
            BeginMode2D(camera);
                    
                RenderMap(TileMapGraph, camera);

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
