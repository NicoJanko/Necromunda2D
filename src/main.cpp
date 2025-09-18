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

static bool PointInRect(Vector2 p, Rectangle r) {
    return p.x >= r.x && p.x <= r.x + r.width && p.y >= r.y && p.y <= r.y + r.height;
}
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main ()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1280;
    const int screenHeight = 720;
    

    InitWindow(screenWidth, screenHeight, "Necro2D");
    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    //int zoomMode = 0;   // 0-Mouse Wheel, 1-Mouse Move

    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    World world{GetWorld()};
    float ppi{ComputePpiToFitBoard(screenWidth, screenHeight, world.width, world.height, 40.0f)};
    std::cout << "ppi : " << ppi ;
    std::vector<Building> buildings{BuildBuildings(ppi)};
    std::cout << "Buildings" << buildings.size() ;
    std::cout << buildings[0].r.x << " " << buildings[0].r.y << " " << buildings[0].r.height << " " << buildings[0].r.width << ";";
    
    Actor actor;
    actor.pos.x = 60.0f;
    actor.pos.y = 60.0f;
    actor.radius = 0.984252*ppi;
    actor.moveMax = 6*ppi;
    actor.moveLeft = actor.moveMax;
    // Main game loop
    const float W = world.width * ppi;
    const float H = world.height * ppi;
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        float dt = GetFrameTime();
        Vector2 mouse = GetMousePosition();
        Vector2 mouseWorld  = GetScreenToWorld2D(mouse, camera);
        // Update
        //----------------------------------------------------------------------------------
        //camera works
        SetCamera(camera);

        Rectangle nextTurnBtn { 12, 12, 140, 36 };
        bool overButton = PointInRect(mouse, nextTurnBtn);

        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON && !overButton)) {
            actor.target = mouseWorld;      // world == screen for now (no camera transform used)
            // If target is inside a building, we still try: movement/collision will stop us at the edge.
            actor.moving = true;
        }
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && overButton) {
            actor.moveLeft = actor.moveMax;
            actor.moving = false;
        }
        UpdateMouvement(actor,buildings,dt);
        //Update ball position


        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);

            
            //world
            BeginMode2D(camera);


                for (int x = 0; x <= (int)world.width; ++x) {
                    int X = (int)(x * ppi);
                     DrawLine(X, 0, X, (int)H, Fade(WHITE, 0.08f));
                    }
                for (int y = 0; y <= (int)world.height; ++y) {
                    int Y = (int)(y * ppi);
                    DrawLine(0, Y, (int)W, Y, Fade(WHITE, 0.08f));
                    }

                // (optional) board outline
                DrawRectangleLinesEx({0, 0, W, H}, 2, LIGHTGRAY);
                //Vector2 mousePos = GetWorldToScreen2D(GetMousePosition(), camera)
                //Draw the red circle here as it is a world object
                for (auto& b : buildings) {
                    //
                DrawRectangleRec(b.r, Color{70, 80, 110, 255});
                DrawRectangleLinesEx(b.r, 2, Color{110, 130, 170, 255});
                }
                if (actor.moving) {
                    DrawCircleV(actor.target, 4, Color{ 255, 200, 60, 255 });
                    DrawLineV(actor.pos, actor.target, Color{ 255, 200, 60, 180 });
                }
                DrawCircleV(actor.pos, actor.radius, Color{ 230, 80, 90, 255 });
                DrawCircleLinesV(actor.pos, actor.radius, Color{ 255, 160, 170, 255 });
                

            EndMode2D();

            // Draw mouse reference
             // Simple movement bar
             //UI
            float barW = 240.f;
            float ratio = (actor.moveMax <= 0.0f) ? 0.0f : (actor.moveLeft / actor.moveMax);
            ratio = Clamp(ratio, 0.0f, 1.0f);
            DrawRectangle(12, 84, (int)(barW), 12, Color{50,50,60,255});
            DrawRectangle(12, 84, (int)(barW*ratio), 12, Color{120,220,160,255});
            DrawRectangleLines(12, 84, (int)barW, 12, Color{180,180,200,255});
            DrawText(TextFormat("Mouvement Left: %.1f", actor.moveLeft/ppi), 22, 84, 18, BLACK);
            // Next Turn Button
            Color btnBg = overButton ? Color{ 80, 130, 220, 255 } : Color{ 60, 100, 190, 255 };
            DrawRectangleRounded(nextTurnBtn, 0.25f, 6, btnBg);
            DrawRectangleRoundedLines(nextTurnBtn, 0.25f, 6, Color{ 200, 220, 255, 255 });
            DrawText("Next turn", (int)(nextTurnBtn.x + 16), (int)(nextTurnBtn.y + 8), 18, RAYWHITE);
            
            //std::cout << "Ball position" << ballPosition.x << ballPosition.y;
            // mouse is not a world object
            DrawCircleV(GetMousePosition(), 4, DARKGRAY);
            DrawTextEx(GetFontDefault(), TextFormat("[%.0f, %.0f]", mouseWorld.x/ppi, mouseWorld.y/ppi),
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
