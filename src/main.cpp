#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"
#include "Shader.h"
#include "Camera.h"

#include "Mesh.h"
#include "Renderer.h"
#include "Scene.h"

#include <vector>
#include <memory>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void processInput(GLFWwindow *window);

int main() {
    
    Renderer* renderer = new Renderer();
    renderer->setWidth(SCR_WIDTH);
    renderer->setHeight(SCR_HEIGHT);
    if (!renderer->init()) {
        return -1;
    }

    renderer->setShader(std::make_unique<Shader>("../shaders/vertex.shader", "../shaders/fragment.shader"));
    renderer->setCamera(std::make_unique<Camera>(
        glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 1.0f, 0.0f), 
        -90.0f,                      
        0.0f,                      
        45.0f,                      
        float(SCR_WIDTH) / SCR_HEIGHT, 
        0.1f,
        100.0f                      
    ));

    std::vector<Vertex> vertices = {
        {{0.0f,  0.5f, 0.0f}, {0.5f, 1.0f}},
        {{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}}
    };
    
    std::vector<unsigned int> indices = { 0, 1, 2 };
    auto triangle = std::make_shared<Mesh>(vertices, indices);
    renderer->uploadMesh(triangle);


    while (!glfwWindowShouldClose(renderer->getWindow())) {
        processInput(renderer->getWindow());
        renderer->render();
    }
    renderer->shutdown();
    delete renderer;
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
