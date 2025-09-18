#include "world.h"
#include "object.h"

#include "raylib.h"
#include "raymath.h"
#include "json.hpp"

#include <vector>
#include <fstream>
#include <sstream>

struct Units
{
    /* data */
};

float ComputePpiToFitBoard(const int& screenW, const int& screenH, const float& boardW_in, const float& boardH_in, const float& margin_px) {
    float ppiW = (screenW - 2.0f * margin_px) / boardW_in;
    float ppiH = (screenH - 2.0f * margin_px) / boardH_in;
    return std::min(ppiW, ppiH);
};

void DrawInchGrid(float ppi, int boardW_in, int boardH_in) {
    const float W = boardW_in * ppi;
    const float H = boardH_in * ppi;

    // background (optional)
    // DrawRectangle(0, 0, (int)W, (int)H, Fade(RAYWHITE, 0.02f));

    // vertical lines (every 1")
    for (int x = 0; x <= boardW_in; ++x) {
        int X = (int)(x * ppi);
        bool major = (x % 6 == 0);
        DrawLine(X, 0, X, (int)H, major ? Fade(BLACK, 0.18f) : Fade(BLACK, 0.08f));
    }
    // horizontal lines (every 1")
    for (int y = 0; y <= boardH_in; ++y) {
        int Y = (int)(y * ppi);
        bool major = (y % 6 == 0);
        DrawLine(0, Y, (int)W, Y, major ? Fade(BLACK, 0.18f) : Fade(BLACK, 0.08f));
    }

    // board outline
    DrawRectangleLinesEx(Rectangle{0,0,W,H}, 2, GRAY);
};

World GetWorld() {
    std::ifstream f("resource/maps/map1.json");
    nlohmann::json J;
    std::stringstream buffer;
    buffer << f.rdbuf();
    J = nlohmann::json::parse(buffer.str());
    World world{};
    if (J.contains("map")){
        auto& map = J["map"];
        
        world.height = map.value("h",0.0f);
        world.width = map.value("w",0.0f);
    }
    return world;
};

std::vector<Building> BuildBuildings(const float& ppi) {
    //load building layout
    std::ifstream f("resource/maps/map1.json");
    nlohmann::json J;
    std::stringstream buffer;
    buffer << f.rdbuf();
    J = nlohmann::json::parse(buffer.str());

    std::vector<Building> buildings;
    if (J.contains("buildings") && J["buildings"].is_array()) {
        for (auto& b : J["buildings"]) {
            Building B{};
            B.r.x = b.value("x",0.0f)*ppi;
            B.r.y = b.value("y",0.0f)*ppi;
            B.r.width = b.value("w",0.0f)*ppi;
            B.r.height = b.value("h",0.0f)*ppi;
            buildings.push_back(B);
        }
    }
    return buildings;

};
