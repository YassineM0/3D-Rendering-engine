#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Shader.h"
#include <memory>


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void processInput(GLFWwindow *window, Camera* camera, float deltaTime);

int main() {
    Renderer* renderer = new Renderer();

    renderer->setWidth(SCR_WIDTH);
    renderer->setHeight(SCR_HEIGHT);
    
    if(!renderer->init())
    {
        return -1;
    }

    renderer->setShader(std::make_unique<Shader>("../../../shaders/vertex.glsl", "../../../shaders/fragment.glsl"));
    renderer->setCamera(std::make_unique<Camera>(
        glm::vec3(0.0f, 0.0f, 0.1f),
        glm::vec3(0.0f, 1.0f, 0.0f), 
        -90.0f,                      
        0.0f,                      
        45.0f,                      
        float(SCR_WIDTH) / SCR_HEIGHT, 
        0.1f,
        100.0f,
        glm::mat4(1.0f),
        glm::mat4(1.0f),
        glm::mat4(1.0f)                
    ));

    std::vector<Vertex> vertices = {
        {{-0.5f,  0.5f, 0.0f}, {0.5f, 1.0f}},
        {{0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f}, {1.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}},

        {{-0.5f,  0.5f, -0.5f}, {0.5f, 1.0f}},
        {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
    };

    std::vector<unsigned int> indices = { 
        0, 1, 3,
        0, 1, 2,

        0, 2, 4,
        0, 2, 6,

        4, 5, 7,
        4, 5, 6,

        1, 3, 5,
        1, 3, 7,

        2, 6, 7,
        2, 6, 5,

        0, 4, 7,
        0, 4, 3

    
    };

    std::shared_ptr<Mesh> cube = std::make_shared<Mesh>(vertices, indices);
    renderer->uploadMesh(cube);

    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(renderer->getWindow())) {
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(renderer->getWindow(), renderer->getCamera(), deltaTime);
        renderer->render(deltaTime);
    }

    delete renderer;
    return 0;

}

void processInput(GLFWwindow *window, Camera* camera, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->processKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->processKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->processKeyboard(RIGHT, deltaTime);
}
