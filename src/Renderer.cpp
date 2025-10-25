#include "Renderer.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>


bool Renderer::init() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "3D Renderer", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    return true;
}
//...
void Renderer::uploadMesh(const std::shared_ptr<Mesh>& m) {
    meshes.push_back(m);
}

void Renderer::render(float deltaTime) {
    if (!window) return;

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (shader) shader->use();
    if (camera && shader) {
        //shader->setMat4("model", camera->getModel());
        shader->setMat4("view", camera->getView());
        shader->setMat4("projection", camera->getProjection());
    }
    for (const auto& mesh : meshes) {
        shader->setMat4("model", mesh->getModel());
        mesh->draw();
    }
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    shader->setVec3("light.position", lightPos);
    shader->setVec3("viewPos", camera->getPosition());

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Renderer::shutdown() {
    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
}

// width/height
int Renderer::getHeight() const { return height; }
int Renderer::getWidth() const { return width; }
void Renderer::setHeight(int h) { height = h; }
void Renderer::setWidth(int w) { width = w; }

//  window
GLFWwindow* Renderer::getWindow() const { return window; }
void Renderer::setWindow(GLFWwindow* win) { window = win; }

// Shader
Shader* Renderer::getShader() const { return shader.get(); }
void Renderer::setShader(std::unique_ptr<Shader> s) { shader = std::move(s); }

// Camera
Camera* Renderer::getCamera() const { return camera.get(); }
void Renderer::setCamera(std::unique_ptr<Camera> c) { camera = std::move(c); }

// Meshes
const std::vector<std::shared_ptr<Mesh>>& Renderer::getMeshes() const { return meshes; }
void Renderer::setMeshes(const std::vector<std::shared_ptr<Mesh>>& m) { meshes = m; }

Renderer::~Renderer() {
    shutdown();
}