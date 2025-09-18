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
