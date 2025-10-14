#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Scene.h"
#include "Camera.h"
#include "Shader.h"

class Renderer {
public:
    GLFWwindow* window  = nullptr;
    int width = 1280, height = 720;

    Shader shader;
    Camera camera;

    bool init();
    void uploadMesh(Mesh& m);
    void render(const Scene& scene);
    void shutdown();
};