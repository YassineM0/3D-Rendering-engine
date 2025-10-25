#pragma once

#include <vector>
#include <cstdint>
#include <glm/glm.hpp>
#include <string>
#include <memory>

struct Vertex {
    glm::vec3 position; 
    glm::vec3 normal; 
    glm::vec2 uv;   
};

class Mesh {
public:
    Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

    void draw() const;





    static std::shared_ptr<Mesh> loadSTEP(const std::string& filepath);
    glm::mat4 getModel();
    void setModel(glm::mat4& m);
    ~Mesh();

private:
    unsigned int vbo, ebo, vao;

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;


    glm::mat4 model = glm::mat4(1.0f);

    void setupMesh();
};