#include "camera.h"

#include "raylib.h"
#include "raymath.h"

void SetCamera(Camera2D& camera) {
    static int zoomMode = 0;

    if (IsKeyPressed(KEY_ONE))
    {
        zoomMode = 0;
    }
    else if (IsKeyPressed(KEY_TWO))
    {
        zoomMode = 1;
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f/camera.zoom);
        camera.target = Vector2Add(camera.target, delta);
    }
    if (zoomMode == 0)
    {
        float wheel = GetMouseWheelMove();
        if (wheel != 0) 
        {
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
            camera.offset = GetMousePosition();
            camera.target = mouseWorldPos;

            float scale = 0.2f*wheel;
            camera.zoom = Clamp(expf(logf(camera.zoom)+scale), 0.125f, 64.0f);
        }
    }
    else //zoomMode 1
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
            camera.offset = GetMousePosition();
            camera.target = mouseWorldPos;
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            float deltaX = GetMouseDelta().x;
            float scale = 0.005f*deltaX;
            camera.zoom = Clamp(expf(logf(camera.zoom)+scale), 0.125f, 64.0f);
        }
    }
    

};