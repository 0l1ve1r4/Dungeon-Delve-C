#include "utils.h"

void debug_log(char *message, char* escape_code){
    
    char* RESET = "\033[0m";
    char* ERROR = "\033[0;31m";
    char* WARNING = "\033[0;33m";
    char* INFO = "\033[0;36m";

    char* text;

    if (strcmp(escape_code, "ERROR") == 0){ 
        escape_code = ERROR;
        text = "ERROR";
    }

    else if (strcmp(escape_code, "WARNING") == 0) {
        escape_code = WARNING;
        text = "WARNING";}

    else if (strcmp(escape_code, "INFO") == 0){
        escape_code = INFO;
        text = "INFO";}

    else {
        escape_code = INFO;
        text = "INFO";}
    

    printf("%s[%s]%s%s", escape_code, text, RESET, message);
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

    sprintf(info_text, "| FPS: %i | X: %i Y: %i |", frames_per_second, player_x / __TILE_SIZE, player_y / __TILE_SIZE);
    
    float right_corner = (float)SCREEN_WIDTH/10 * 6;

    DrawText(info_text, right_corner, 0, 15, WHITE);
    

}

void InitRandomSeed(void){
    srand(time(NULL));
}
