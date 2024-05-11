#include "defs.h"
#include "structs.h"
#include "entity/player.h"
#include "render/render.h"
#include "utils/utils.h"
#include "enums.h"

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    InitAudioDevice();             
    InitRandomSeed();

    Player *player = InitPlayer();
    Camera2D camera = InitPlayerCamera(player);
    Tile*** TileMap = CreateMap(MAP_LENGTH, __TILE_SIZE);

    Music music = LoadMusicStream("resources/sounds/background.mp3");

    PlayMusicStream(music);

    static __uint8_t currentFrame = 0;
    static __uint8_t framesCounter = 0;

    //=======================================================================================
    // Main game loop
    //=======================================================================================    
    
    SetTargetFPS(TARGET_FPS);
    while (!WindowShouldClose())
    {   
        //==================================================================================
        // Update
        //==================================================================================
        UpdateMusicStream(music);   // Update music buffer with new stream data

        float deltaTime = GetFrameTime();
        framesCounter++;

        framesCounter = (framesCounter >= (TARGET_FPS/PLAYER_FRAME_SPEED)) ? 0 : framesCounter;
        currentFrame = (framesCounter == 0) ? ((currentFrame > 5) ? 0 : currentFrame + 1) : currentFrame;

        UpdatePlayer(player, deltaTime, currentFrame);
        UpdatePlayerCamera(&camera, player, deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT);
        UpdateMapCollision(player, TileMap, MAP_LENGTH, __TILE_SIZE);
        

        //==================================================================================
        // Draw
        //==================================================================================
        BeginDrawing();
            ClearBackground(BLACK);
            
            BeginMode2D(camera);
                
                DrawFullMap(TileMap, camera);
                
                //DrawTextureRec(player->texture, player->frameRec, player->position, WHITE);

                DrawPlayer(player);                
                DrawCircleGradient(player->position.x, player->position.y, PLAYER_TILE_VISIBILITY, Fade(BLACK, 0.8f), Fade(BLACK, 10.0f));


            EndMode2D();

            ShowControls();
            GetGameInfo(player);
        EndDrawing();

    }

    //==================================================================================
    CloseWindow();        // Close window and OpenGL context
    //==================================================================================

    return 0;
}

