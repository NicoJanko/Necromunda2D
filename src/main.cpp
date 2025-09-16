/*******************************************************************************************
*
*   raylib [core] example - 2d camera mouse zoom
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 4.2, last time updated with raylib 4.2
*
*   Example contributed by Jeffery Myers (@JeffM2501) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2022-2025 Jeffery Myers (@JeffM2501)
*
********************************************************************************************/
#include "camera.h"
#include "object.h"
#include "actions.h"
#include "world.h"


#include <iostream>
#include "raylib.h"

#include "rlgl.h"
#include "raymath.h"
#include "json.hpp"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main ()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    

    InitWindow(screenWidth, screenHeight, "Necro2D");
    Vector2 ballPosition = { (float)screenWidth/2, (float)screenHeight/2 };
    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    //int zoomMode = 0;   // 0-Mouse Wheel, 1-Mouse Move

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    std::vector<Building> buildings{BuildBuildings()};
    
    Actor actor;
    actor.pos.x = 60.0f;
    actor.pos.y = 60.0f;
    actor.radius = 14.0f;
    actor.moveMax = 180.0f;
    actor.moveLeft = actor.moveMax;
    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        float dt = GetFrameTime();
        Vector2 mouse = GetMousePosition();
        // Update
        //----------------------------------------------------------------------------------
        //camera works
        SetCamera(camera);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            actor.target = mouse;      // world == screen for now (no camera transform used)
            // If target is inside a building, we still try: movement/collision will stop us at the edge.
            actor.moving = true;
        }
        UpdateMouvement(actor,dt);
        //Update ball position


        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);

            for (auto& b : buildings) {
                DrawRectangleRec(b.r, Color{70, 80, 110, 255});
                DrawRectangleLinesEx(b.r, 2, Color{110, 130, 170, 255});
            }

            BeginMode2D(camera);

                // Draw the 3d grid, rotated 90 degrees and centered around 0,0
                // just so we have something in the XY plane
                rlPushMatrix();
                    rlTranslatef(0, 25*50, 0);
                    rlRotatef(90, 1, 0, 0);
                    DrawGrid(100, 50);
                rlPopMatrix();
                //Vector2 mousePos = GetWorldToScreen2D(GetMousePosition(), camera)
                //Draw the red circle here as it is a world object
                if (actor.moving) {
                    DrawCircleV(actor.target, 4, Color{ 255, 200, 60, 255 });
                    DrawLineV(actor.pos, actor.target, Color{ 255, 200, 60, 180 });
                }
                DrawCircleV(actor.pos, actor.radius, Color{ 230, 80, 90, 255 });
                DrawCircleLinesV(actor.pos, actor.radius, Color{ 255, 160, 170, 255 });

                        // Simple movement bar
                float barW = 240.f;
                float ratio = (actor.moveMax <= 0.0f) ? 0.0f : (actor.moveLeft / actor.moveMax);
                ratio = Clamp(ratio, 0.0f, 1.0f);
                DrawRectangle(12, 84, (int)(barW), 12, Color{50,50,60,255});
                DrawRectangle(12, 84, (int)(barW*ratio), 12, Color{120,220,160,255});
                DrawRectangleLines(12, 84, (int)barW, 12, Color{180,180,200,255});
                //get the position of the ball
                //DrawTextEx(GetFontDefault(), TextFormat("[%.0f, %.0f]", ballPosition.x, ballPosition.y),
                //Vector2Add((Vector2) {ballPosition.x, ballPosition.y}, (Vector2){ -44, -24 }), 20, 2, RED);

                // Draw a small reference circle
                DrawCircle(GetScreenWidth()/20, GetScreenHeight()/20, 50, BLUE);
                

            EndMode2D();

            // Draw mouse reference

            
            //std::cout << "Ball position" << ballPosition.x << ballPosition.y;
            // mouse is not a world object
            DrawCircleV(GetMousePosition(), 4, DARKGRAY);
            DrawTextEx(GetFontDefault(), TextFormat("[%i, %i]", GetMouseX(), GetMouseY()),
                Vector2Add(GetMousePosition(), (Vector2){ -44, -24 }), 20, 2, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}
