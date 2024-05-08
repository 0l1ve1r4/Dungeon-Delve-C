#include "utils.h"

void debug_log(char *message, char* escape_code){
    
    char* RESET = "\033[0m";
    printf("%s%s%s", escape_code, message, RESET);
}

void ShowControls(void)
{
    static int show = true;
    if (IsKeyPressed(KEY_C)) show = !show;
    if (!show) return;

    DrawText("Controls | 'C' to close:", 20, 20, 10, BLACK);
    DrawText("Move - W | A | S | D ", 40, 40, 10, DARKGRAY);
    DrawText("Attack - Left Click ", 40, 60, 10, DARKGRAY);
    DrawText("Interact - Right Click ", 40, 80, 10, DARKGRAY);
}

void GetGameInfo(Player* player){

    char* info_text = (char*)malloc(50 * sizeof(char));

    int frames_per_second = GetFPS();
    int player_x = player->position.x;
    int player_y = player->position.y;

    sprintf(info_text, "| FPS: %i | X: %i Y: %i |", frames_per_second, player_x, player_y);
    
    float right_corner = (float)SCREEN_WIDTH/10 * 8;

    DrawText(info_text, right_corner, 0, 13, BLACK);
    

}