#pragma once


#include <glm/glm.hpp>
#include <string>

struct Material {
    glm::vec3 albedo = {0.8f, 0.8f, 0.8f};
    float metallic = 0.0f;
    float roughness = 1.0f;
    std::string name;
};