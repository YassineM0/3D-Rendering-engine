#pragma once

#include <vector>
#include <cstdint>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position; 
    glm::vec2 uv;   
};

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
    ~Mesh();

    void draw() const;

private:
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    unsigned int vbo, ebo, vao;

    void setupMesh();
};