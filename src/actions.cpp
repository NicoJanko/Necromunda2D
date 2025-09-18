#include "object.h"
#include "actions.h"

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include "raylib.h"
#include "raymath.h"

static bool CircleRectCollide(Vector2 center, float radius, Rectangle rec) {
    // raylib has CheckCollisionCircleRec, but re-expose for clarity
    return CheckCollisionCircleRec(center, radius, rec);
}

// , 
void UpdateMouvement(Actor& actor,const std::vector<Building>& B,float dt) {
    // is there move left
    if (!actor.moving || actor.moveLeft <= 0.0f) {
        actor.moving = false;
        return;
    }
    ::Vector2 toTarget = Vector2Subtract(actor.target, actor.pos);
    float distToTarget = Vector2Length(toTarget);
    if (distToTarget < 0.001f) {
        actor.moving = false;
        return;
    }
    float stepMax = actor.speed * dt;
    float step = fminf(stepMax, fminf(distToTarget, actor.moveLeft));
    const float subStep = 2.0f;
    ::Vector2 dir = Vector2Scale(toTarget, 1.0f / distToTarget);

    float moved = 0.f;
    while (moved < step - 1e-4f) {
        float thisStep = fminf(subStep, step - moved);
        ::Vector2 nextPos = Vector2Add(actor.pos, Vector2Scale(dir, thisStep));

        bool hit = false;
        for (auto& b : B) {
            if (CircleRectCollide(nextPos, actor.radius, b.r)) { hit = true; break; }
        }
        if (hit) { 
            actor.moving = false; 
            break; 
        }

        actor.pos = nextPos;
        moved += thisStep;
        actor.moveLeft -= thisStep;
        if (actor.moveLeft <= 0.f) { actor.moving = false; break; }
    }

    // If we reached the target (within a pixel), snap and stop
    if (Vector2Distance(actor.pos, actor.target) < 1.0f) {
        actor.pos = actor.target;
        actor.moving = false;
    }

}
