// This file is part of DungeonDelveC.
// Copyright (C) 2024 Guilherme Oliveira Santos

// DungeonDelveC is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
    

    printf("%s[%s]%s %s", escape_code, text, RESET, message);
}

void ShowControls(void)
{
    static int show = true;
    if (IsKeyPressed(KEY_C)) show = !show;
    if (!show) return;

    DrawText("Controls | 'C' to close:", 20, 20, 10, WHITE);
    DrawText("Move - W | A | S | D ", 40, 40, 10, WHITE);
    DrawText("Attack - SPACE", 40, 60, 10, WHITE);
    DrawText("Interact - E ", 40, 80, 10, WHITE);
}

void GetGameInfo(Player* player) {
    const int BUFFER_SIZE = 32;
    const int INFO_COUNT = 5;
    const int TEXT_SIZE = 10;
    char* texts[INFO_COUNT];

    for (int i = 0; i < INFO_COUNT; i++) 
        texts[i] = (char*)malloc(BUFFER_SIZE * sizeof(char));

    float values[] = { (float)GetFPS(),
        player->entity.health,
        player->entity.stamina,
        player->entity.mana,
        player->entity.damage
    };

    const char* formats[] = { "FPS: %.1f",
        "Health: %.1f",
        "Stamina: %.1f",
        "Mana: %.1f",
        "Strength: %.1f"
    };

    float right_corner = (float)SCREEN_WIDTH / 10 * 9.3;

    for (int i = 0; i < INFO_COUNT; i++) {
        sprintf(texts[i], formats[i], values[i]);
        DrawText(texts[i], right_corner, i * 20, TEXT_SIZE, WHITE);
        free(texts[i]);
    
    }

}

void InitRandomSeed(void* value){
    if (value == NULL){
        unsigned long seed = mix(clock(), time(NULL), getpid());
        srand(seed);
        return;
    }

    srand((unsigned long)value);
}

// Robert Jenkins' 96 bit Mix Function
// Credits: https://gist.github.com/badboy/6267743
unsigned long mix(unsigned long a, unsigned long b, unsigned long c)
{
    a=a-b;  a=a-c;  a=a^(c >> 13);
    b=b-c;  b=b-a;  b=b^(a << 8);
    c=c-a;  c=c-b;  c=c^(b >> 13);
    a=a-b;  a=a-c;  a=a^(c >> 12);
    b=b-c;  b=b-a;  b=b^(a << 16);
    c=c-a;  c=c-b;  c=c^(b >> 5);
    a=a-b;  a=a-c;  a=a^(c >> 3);
    b=b-c;  b=b-a;  b=b^(a << 10);
    c=c-a;  c=c-b;  c=c^(b >> 15);
    return c;
}

void DrawFog(Camera2D camera, int radius){
    DrawCircleGradient(camera.target.x, camera.target.y, radius, Fade(BLACK, 0.6f), Fade(BLACK, 10.0f));
}

void UpdateFrameValues(int* current_frame, int* frame_counter, float* delta_time){

    float frame_time = GetFrameTime();
    delta_time = &frame_time;

    (*frame_counter)++;

    *frame_counter = (*frame_counter >= (TARGET_FPS/PLAYER_FRAME_SPEED)) ? 0 : *frame_counter;
    *current_frame = (*frame_counter == 0) ? ((*current_frame > 5) ? 0 : *current_frame + 1) : *current_frame;


}