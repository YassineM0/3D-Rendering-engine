#pragma once

#include "Scene.h"
#include "Camera"
#include "Shader.h"
#include <GLFW/glfw3.h>

class Renderer {
public:
    GLFWwindow* window  = nullptr;
    int width = 1280, height = 720;

    Shader shader;
    Camera camera;

    bool init();
    void uploadMesh(Mesh& m);
    void render(const Scene& scene);
    void shutDown();
}