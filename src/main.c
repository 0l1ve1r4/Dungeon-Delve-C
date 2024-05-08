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

    Tile** tiles = CreateGrassTiles(MAP_LENGTH, GRASS);

    static int currentFrame = 0;
    static int framesCounter = 0;
    static int framesSpeed = 6;

    //=======================================================================================
    // Main game loop
    //=======================================================================================    
    
    SetTargetFPS(TARGET_FPS);
    while (!WindowShouldClose())
    {   
        //==================================================================================
        // Update
        //==================================================================================
        
        float deltaTime = GetFrameTime();
        framesCounter++;

        framesCounter = (framesCounter >= (TARGET_FPS/PLAYER_FRAME_SPEED)) ? 0 : framesCounter;
        currentFrame = (framesCounter == 0) ? ((currentFrame > 5) ? 0 : currentFrame + 1) : currentFrame;

        // Atualize o jogador e passe o número do quadro atual como parâmetro
        UpdatePlayer(player, deltaTime, currentFrame);
        UpdatePlayerCamera(&camera, player, deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT);

        //==================================================================================
        // Draw
        //==================================================================================

        BeginDrawing();
            ClearBackground(LIGHTGRAY);
            
            BeginMode2D(camera);
                for(int i = 0; i < MAP_LENGTH; i++){
                    for(int j = 0; j < MAP_LENGTH; j++){
                        DrawTexture(tiles[i][j].texture, tiles[i][j].position.x, tiles[i][j].position.y, WHITE);


                    }
                }


                DrawTextureRec(player->texture, player->frameRec, player->position, WHITE);

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

