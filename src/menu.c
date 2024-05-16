#include "defs.h"
#include "map/maps.h"
#include "utils/utils.h"

// THIS CODE NEEDS TO BE REFACTORED AND CLEANED UP

static MapNode* TileMapGraph;
typedef enum {
    OPTION_SINGLEPLAYER,
    OPTION_MULTIPLAYER,
    OPTION_OPTIONS,
    OPTION_EXIT
    }    MenuOption;


MapNode* menu_screen(void) {

    MenuOption selectedOption = OPTION_SINGLEPLAYER;
    
    Texture2D logo = LoadTexture("res/static/background.png");
    Texture2D wall = LoadTexture("res/static/wall.png");

    Sound change_option = LoadSound("res/static/change_option.mp3");
    Sound select_option = LoadSound("res/static/select.mp3");
    Sound lightning = LoadSound("res/static/lightning.mp3");

    wall.width = __TILE_SIZE;
    wall.height = __TILE_SIZE;

    logo.width = 200;
    logo.height = 200;

    Color background_color = BACKGROUND_COLOR;
    
    int animFrames = 0;
    Image fireAnim = LoadImageAnim("res/static/fire.gif", &animFrames);
    Image rain = LoadImageAnim("res/static/rain.gif", &animFrames);

    Texture2D texFireAnim = LoadTextureFromImage(fireAnim);
    Texture2D texRain = LoadTextureFromImage(rain);

    Music music = LoadMusicStream(BACKGROUND_MENU_MUSIC);

    PlayMusicStream(music);

    
    uint32_t nextFrameDataOffset = 0;
    uint8_t currentAnimFrame = 0;      
    uint8_t frameDelay = 10;            
    uint8_t frameCounter = 0;
    
    bool isRaining = false;
    float isRainingAlpha = 0.0f;
    
    const char *optionsText[MAX_OPTIONS] = {"SINGLEPLAYER", "MULTIPLAYER", "OPTIONS", "EXIT"};

    while (!WindowShouldClose()) {
        // Update
        //
        UpdateMusicStream(music);
        
        if (isRainingAlpha > 0.0f) {
            isRainingAlpha -= 0.1f;
            isRaining = true;
        }
        
        else {
            isRaining = false;
        }

        
        if (rand()%10000 < 1 && !isRaining && !IsSoundPlaying(lightning)) {
            PlaySound(lightning);        
            isRaining = true;
            isRainingAlpha = 3.0f;
        }

        
        frameCounter++;
        if (frameCounter >= frameDelay) {
            currentAnimFrame = (currentAnimFrame + 1) % animFrames;
            nextFrameDataOffset = fireAnim.width * fireAnim.height * 4 * currentAnimFrame;
            UpdateTexture(texFireAnim, ((unsigned char *)fireAnim.data) + nextFrameDataOffset);
            UpdateTexture(texRain, ((unsigned char *)rain.data) + nextFrameDataOffset);


            frameCounter = 0;
        }

    
        if (IsKeyPressed(KEY_DOWN)) {
            selectedOption = (selectedOption + 1) % MAX_OPTIONS;
            PlaySound(change_option);

        } else if (IsKeyPressed(KEY_UP)) {
            selectedOption = (selectedOption - 1 + MAX_OPTIONS) % MAX_OPTIONS;
            PlaySound(change_option);
        }

        if (IsKeyPressed(KEY_ENTER)) {
            PlaySound(select_option);
            switch (selectedOption) {
                case OPTION_SINGLEPLAYER:
                    TileMapGraph = CreateMap();
                    return TileMapGraph;
                    break;
                case OPTION_MULTIPLAYER:
                    // Implement multiplayer logic
                    break;
                case OPTION_OPTIONS:
                    // Implement options logic
                    break;
                case OPTION_EXIT:
                    usleep(500000); // Sleep for 0.5 second
                    CloseWindow();
                    break;
            }
        }
        
        // Draw
        BeginDrawing();
        ClearBackground(background_color);

        int verticalCenter = (SCREEN_HEIGHT - 40 * MAX_OPTIONS) / 2;
        int fire_y = (selectedOption - 1.3) * 60;

        DrawTexture(texRain, verticalCenter-250, 0, WHITE);

        DrawTexture(logo, verticalCenter+240, 10, WHITE);
        DrawTexture(texFireAnim, verticalCenter+130, verticalCenter + fire_y, WHITE);
        DrawTexture(texFireAnim, verticalCenter+480, verticalCenter + fire_y, WHITE);

        
        DrawCircleGradient(verticalCenter+300, 500, 1000, Fade(WHITE, 0.f), Fade(WHITE, isRainingAlpha));
        
        
        for (int i = SCREEN_HEIGHT/ 2 + 310; i < SCREEN_HEIGHT; i += __TILE_SIZE)
            for (int j = 0; j < SCREEN_WIDTH; j += __TILE_SIZE)
                DrawTexture(wall, j, i, WHITE);        
        

        // Draw menu options with rectangles
        for (int i = 0; i < MAX_OPTIONS; i++) {
            Vector2 rectPos = {SCREEN_WIDTH / 2 - 200, verticalCenter + 60 * i};
            Rectangle optionRect = {rectPos.x, rectPos.y, 400, 40};
            if (i == selectedOption) {
                DrawRectangleRec(optionRect, RED);
                DrawText(optionsText[i], optionRect.x + 10, optionRect.y + 10, 30, WHITE);
                

            } else {
                DrawRectangleRec(optionRect, ColorFromNormalized((Vector4){0.44f, 0.44f, 0.44f, 1.0f}));
                DrawText(optionsText[i], optionRect.x + 10, optionRect.y + 10, 30, WHITE);
            }
        }


        DrawCircleGradient(verticalCenter+300, 0, 1000, Fade(background_color, 0.f), Fade(background_color, 10.0f));    

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

