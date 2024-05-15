#include "defs.h"
#include "structs.h"

#include "entity/player.h"
#include "render/render.h"

#include "map/maps.h"

// Function prototypes
static void *LoadDataThread(void *arg);
static void DrawMenuText(const char *text, int posX, int posY, bool selected);

// Global variables
static atomic_bool dataLoaded = false; // Data Loaded completion indicator
static atomic_int dataProgress = 0;
static MapNode* TileMapGraph;

MapNode* menu_screen(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    pthread_t threadId = { 0 };

    int state = STATE_WAITING;
    int framesCounter = 0;

    MenuOption selectedOption = MENU_START_GAME;

    while (!WindowShouldClose()) // Main game loop
    {
        // Update
        //----------------------------------------------------------------------------------
        switch (state)
        {
            case STATE_WAITING:
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), (Rectangle){ 150, 170, MeasureText("Start Game", 20), 20 }))
                {
                    int error = pthread_create(&threadId, NULL, &LoadDataThread, NULL);
                    if (error != 0) TraceLog(LOG_ERROR, "Error creating loading thread");
                    else TraceLog(LOG_INFO, "Loading thread initialized successfully");
                    state = STATE_LOADING;
                }
            } break;
            case STATE_LOADING:
            {
                framesCounter++;
                if (atomic_load_explicit(&dataLoaded, memory_order_relaxed))
                {
                    framesCounter = 0;
                    int error = pthread_join(threadId, NULL);
                    if (error != 0) TraceLog(LOG_ERROR, "Error joining loading thread");
                    else TraceLog(LOG_INFO, "Loading thread terminated successfully");

                    state = STATE_FINISHED;
                }
            } break;
            case STATE_FINISHED:
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    // Reset everything to launch again
                    atomic_store_explicit(&dataLoaded, false, memory_order_relaxed);
                    atomic_store_explicit(&dataProgress, 0, memory_order_relaxed);
                    state = STATE_WAITING;
                }
            } break;
            default: break;
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw menu options
        DrawMenuText("Start Game", 150, 170, selectedOption == MENU_START_GAME);
        DrawMenuText("Options", 150, 220, selectedOption == MENU_OPTIONS);
        DrawMenuText("Quit", 150, 270, selectedOption == MENU_QUIT);

        switch (state)
        {
            case STATE_LOADING:
            {
                DrawText("LOADING DATA...", 240, 330, 40, DARKBLUE);
                TileMapGraph = CreateMap();
            } break;
            case STATE_FINISHED:
            {
                DrawRectangle(150, 320, 500, 60, LIME);
                DrawText("DATA LOADED!", 250, 330, 40, GREEN);
                return TileMapGraph;
            } break;
            default: break;
        }

        DrawRectangleLines(150, 320, 500, 60, DARKGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    return NULL;
}

static void *LoadDataThread(void *arg)
{
    // Simulate data loading (10 seconds)
    for (int i = 0; i <= 100; i++)
    {
        atomic_store_explicit(&dataProgress, i, memory_order_relaxed);
        
        // Simulate loading time
        for (int delay = 0; delay < 10000000; delay++) {}
    }

    // When data has finished loading, we set global variable
    atomic_store_explicit(&dataLoaded, true, memory_order_relaxed);

    return NULL;
}

// Draw menu text with optional highlight
static void DrawMenuText(const char *text, int posX, int posY, bool selected)
{
    if (selected) DrawText(text, posX, posY, 20, RED);
    else DrawText(text, posX, posY, 20, DARKGRAY);
}
