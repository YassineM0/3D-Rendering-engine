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
    GLFWwindow* window = nullptr;
    int width = 1280, height = 720;

    std::unique_ptr<Shader> shader;
    std::unique_ptr<Camera> camera;

    std::vector<std::shared_ptr<Mesh>> meshes;

    bool init();
    void uploadMesh(const std::shared_ptr<Mesh>& m);
    void render();
    void shutdown();
};