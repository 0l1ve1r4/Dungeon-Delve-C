#include "defs.h"
#include "structs.h"
#include "entity/player.h"
#include "render/render.h"
#include "utils/utils.h"
#include "enums.h"

int main(void)
{

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    Player *player = InitPlayer();
    Camera2D camera = InitPlayerCamera(player);
    Tile*** TileMap = CreateMap(MAP_LENGTH, GRASS);

    InitAudioDevice();              // Initialize audio device

    Music music = LoadMusicStream("resources/sounds/background.mp3");

    PlayMusicStream(music);

    static int currentFrame = 0;
    static int framesCounter = 0;
    static int framesSpeed = 6;

    RenderTexture2D fogOfWar = LoadRenderTexture(MAP_LENGTH, MAP_LENGTH);
    SetTextureFilter(fogOfWar.texture, TEXTURE_FILTER_BILINEAR);

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
        
        //if (GetMusicTimePlayed(music) > 1.0f) PauseMusicStream(music);
        //----------------------------------------------------------------------------------

        //==================================================================================
        // Draw
        //==================================================================================
        BeginDrawing();
            ClearBackground(BLACK);
            
            BeginMode2D(camera);
                

                
                DrawFullMap(TileMap);
                DrawTextureRec(player->texture, player->frameRec, player->position, WHITE);
                
                DrawCircleGradient(player->position.x, player->position.y, PLAYER_TILE_VISIBILITY, Fade(WHITE, 0.1f), Fade(BLACK, 1.0f));
                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Fade(BLACK, 0.8f));


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

