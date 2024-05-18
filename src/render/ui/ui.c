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

#include "ui.h"

static Texture2D heart;
static Texture2D half_heart;
static Texture2D empty_heart;

void InitUi(void){
    heart = LoadTexture("res/frames/ui_heart_full.png");
    half_heart = LoadTexture("res/frames/ui_heart_half.png");
    empty_heart = LoadTexture("res/frames/ui_heart_empty.png");
}


void DrawUi(Player *player, Camera2D camera){
    // Cast player's health to an integer directly
    int int_health = (player->health);
    float health = player->health;

    // Calculate half_heart using modulus operator to check if there's a remainder when divided by 1

    // Use a constant for the size of the rectangle to avoid magic numbers
    const int RECT_SIZE = 5;

    // Draw full hearts

    float x = camera.target.x - 150;
    float y = camera.target.y + 70;


    for (int i = 0; i < int_health; i++){
        DrawTextureEx(heart, (Vector2){x + i * heart.width, y}, 0, 1, WHITE);
    }

    if (health - int_health > 0){
        DrawTextureEx(half_heart, (Vector2){x + int_health * heart.width, y}, 0, 1, WHITE);
        int_health++;
    }

}