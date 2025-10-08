#pragma once

#include <vector>
#include <cstdint>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position; 
    glm::vec3 normal;
    glm::vec2 uv;   
};

struct Mesh {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    unsigned int vao = 0;
    unsigned int vbo = 0;
    unsigned int ebo = 0;

};