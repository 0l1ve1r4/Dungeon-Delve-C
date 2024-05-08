#include "defs.h"
#include "structs.h"
#include "entity/player.h"
#include "render/render.h"
#include "render/render.h"


int main(void)
{

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);

    Player *player = InitPlayer();
    Camera2D camera = InitPlayerCamera(player);

    EnvItem envItems[] = {
        {{ 0, 0, 1000, 400 }, 0, LIGHTGRAY },
        {{ 0, 400, 1000, 200 }, 1, GRAY },
        {{ 300, 200, 400, 10 }, 1, GRAY },
        {{ 250, 300, 100, 10 }, 1, GRAY },
        {{ 650, 300, 100, 10 }, 1, GRAY }
    };

    int envItemsLength = sizeof(envItems)/sizeof(envItems[0]);


    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())
    {   
        // Update
        //----------------------------------------------------------------------------------
        float deltaTime = GetFrameTime();

        UpdatePlayer(player, deltaTime, 0);
        UpdatePlayerCamera(&camera, player, deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(LIGHTGRAY);

            BeginMode2D(camera);

                for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(envItems[i].rect, envItems[i].color);

                
                DrawTexture(player->texture, player->position.x, player->position.y, WHITE);


                

            EndMode2D();

            ShowControls();
            GetGameInfo(player);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

