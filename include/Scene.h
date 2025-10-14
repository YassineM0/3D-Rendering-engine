#pragma once

#include "Mesh.h"
#include "Material.h"
#include <vector>
#include <glm/glm.hpp>

struct SceneNode {
    std::string name;
    Mesh mesh;
    Material material;
    glm::mat4 trasform = glm::mat4(1.0f);
    std::vector<SceneNode> children;
};

struct Scene {
    std::vector<SceneNode> nodes;
};