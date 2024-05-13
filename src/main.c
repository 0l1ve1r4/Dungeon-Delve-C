#include "defs.h"
#include "structs.h"
#include "entity/player.h"
#include "render/render.h"
#include "utils/utils.h"


static bool game_started = false;
static void menu_screen(Tile***, Player*, Camera2D);
static void StartGame(void);
static void Options(void);
static void Quit(void);

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    InitAudioDevice();             
    InitRandomSeed();

    Player *player = InitPlayer();
    Camera2D camera = InitPlayerCamera(player);
    Tile*** TileMap = CreateMap(MAP_LENGTH, __TILE_SIZE, player);
    
    Music music = LoadMusicStream("res/sounds/background.mp3");

    PlayMusicStream(music);

    static int current_frame = 0;
    static int frame_counter = 0;
    static float delta_time = 0;

    //=======================================================================================
    // Main game loop
    //=======================================================================================    
    
    SetTargetFPS(TARGET_FPS);
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

        if (!game_started){
                menu_screen(TileMap, player, camera);
                continue;   
                                    }


        UpdatePlayerCamera(&camera, player, delta_time, SCREEN_WIDTH, SCREEN_HEIGHT);
        UpdateMapCollision(player, TileMap, MAP_LENGTH, __TILE_SIZE);
        //
        //==================================================================================
        // Draw
        BeginDrawing();
            ClearBackground(BLACK);
            
            BeginMode2D(camera);
                    
                DrawFullMap(TileMap, camera);
    
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


static void menu_screen(Tile*** RandTileMap, Player* player, Camera2D camera)
{

        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Start Game", SCREEN_WIDTH / 2 - MeasureText("Start Game", 20) / 2, 200, 20, WHITE);
        DrawText("Options", SCREEN_WIDTH / 2 - MeasureText("Options", 20) / 2, 240, 20, WHITE);
        DrawText("Quit", SCREEN_WIDTH / 2 - MeasureText("Quit", 20) / 2, 280, 20, WHITE);
        
        EndDrawing();

       
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();

            // Check if mouse click is within the bounds of any menu option
            if (CheckCollisionPointRec((Vector2){(float)mouseX, (float)mouseY}, (Rectangle){SCREEN_WIDTH / 2 - MeasureText("Start Game", 20) / 2, 200, MeasureText("Start Game", 20), 20}))
            {
                StartGame();
            }
            else if (CheckCollisionPointRec((Vector2){(float)mouseX, (float)mouseY}, (Rectangle){SCREEN_WIDTH / 2 - MeasureText("Options", 20) / 2, 240, MeasureText("Options", 20), 20}))
            {
                Options();
            }
            else if (CheckCollisionPointRec((Vector2){(float)mouseX, (float)mouseY}, (Rectangle){SCREEN_WIDTH / 2 - MeasureText("Quit", 20) / 2, 280, MeasureText("Quit", 20), 20}))
            {
                Quit();
            }
        }
}

// Function definitions
static void StartGame(void)
{
    game_started = true;   }

static void Options(void)
{
    DrawText("Guei", 10, 10, 20, WHITE);
}

static void Quit(void)
{
    CloseWindow();
}
