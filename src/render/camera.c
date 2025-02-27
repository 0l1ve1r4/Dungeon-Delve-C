// This file is part of DungeonDelveC.
// Copyright (C) 2024 - 2025 Guilherme Oliveira Santos

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

#include "render.h"

Camera2D InitPlayerCamera(Player *player){
    Camera2D camera = { 0 };
    camera.target = player->entity.position;
    camera.offset = (Vector2){ SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 4.0f;

    return camera;

}

void UpdatePlayerCamera(Camera2D *camera, Player *player, float delta) {
    float minSpeed = 30 * (float) (camera->zoom * 2);
    static float minEffectLength = 10; 
    static float fractionSpeed = 0.8f;

    static float maxZoom = 4.0f;
    static float minZoom = 3.6f;

    int mouseWheel = GetMouseWheelMove();
    if (mouseWheel != 0)
    {
        camera->zoom += ((float)mouseWheel*0.05f);
        if (camera->zoom > maxZoom) camera->zoom = maxZoom;
        else if (camera->zoom < minZoom) camera->zoom = minZoom;
    }

    camera->offset = (Vector2){ SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
    Vector2 diff = Vector2Subtract(player->entity.position, camera->target);
    float length = Vector2Length(diff);
    
    if (length > minEffectLength)
    {   
        float speed = fmaxf(fractionSpeed*length, minSpeed);
        camera->target = Vector2Add(camera->target, Vector2Scale(diff, speed*delta/length));
    }
}


