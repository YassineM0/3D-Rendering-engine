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

void processInput(GLFWwindow *window, Camera* camera, float deltaTime);

int main() {
    
    Renderer* renderer = new Renderer();
    renderer->setWidth(SCR_WIDTH);
    renderer->setHeight(SCR_HEIGHT);
    if (!renderer->init()) {
        return -1;
    }

    renderer->setShader(std::make_unique<Shader>("../shaders/vertex.glsl", "../shaders/fragment.glsl"));
    renderer->setCamera(std::make_unique<Camera>(
        glm::vec3(0.0f, 0.0f, 11.0f),
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


    auto stpBody = Mesh::loadSTEP("../sample_step_files/as1-ac-214.stp");
    renderer->uploadMesh(stpBody);

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
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera->processKeyboard(FORWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->processKeyboard(BACKWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->processKeyboard(LEFT, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->processKeyboard(RIGHT, deltaTime);
}
