#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <vector>
#include "Mesh.h"
#include "Scene.h"
#include "Camera.h"
#include "Shader.h"

class Renderer {

public:
    bool init();
    void uploadMesh(const std::shared_ptr<Mesh>& m);
    void render(float deltatime);
    void shutdown();

    // Window
    GLFWwindow* getWindow() const;
    void setWindow(GLFWwindow* win);

    // Width/Height
    int getWidth() const;
    int getHeight() const;
    void setWidth(int w);
    void setHeight(int h);

    // Shader
    Shader* getShader() const;
    void setShader(std::unique_ptr<Shader> s);

    // Camera
    Camera* getCamera() const;
    void setCamera(std::unique_ptr<Camera> c);

    // Meshes
    const std::vector<std::shared_ptr<Mesh>>& getMeshes() const;
    void setMeshes(const std::vector<std::shared_ptr<Mesh>>& m);

    ~Renderer();
    

private:
    GLFWwindow* window = nullptr;
    int width = 1280, height = 720;
    std::unique_ptr<Shader> shader;
    std::unique_ptr<Camera> camera;
    std::vector<std::shared_ptr<Mesh>> meshes;
    glm::mat4 rotation = glm::mat4(1.0f);

};