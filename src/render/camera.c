#include "render.h"

Camera2D InitPlayerCamera(Player *player){
    Camera2D camera = { 0 };
    camera.target = player->position;
    camera.offset = (Vector2){ SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    return camera;

}

void UpdatePlayerCamera(Camera2D *camera, Player *player, float delta, int width, int height)
{
    float minSpeed = 30 * (float) (camera->zoom * 2);
    static float minEffectLength = 10; 
    static float fractionSpeed = 0.8f;

    int mouseWheel = GetMouseWheelMove();
    if (mouseWheel != 0)
    {
        camera->zoom += ((float)mouseWheel*0.05f);
        if (camera->zoom > 3.0f) camera->zoom = 3.0f;
        else if (camera->zoom < 1.0f) camera->zoom = 1.0f;
    }

    camera->offset = (Vector2){ width/2.0f, height/2.0f };
    Vector2 diff = Vector2Subtract(player->position, camera->target);
    float length = Vector2Length(diff);

    if (length > minEffectLength)
    {
        float speed = fmaxf(fractionSpeed*length, minSpeed);
        camera->target = Vector2Add(camera->target, Vector2Scale(diff, speed*delta/length));
    }
}


