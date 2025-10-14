#pragma once

#include <glm/glm.hpp>

class Camera {
    public:
        glm::vec3 position{0.0f, 0.0f, 3.0f};
        glm::vec3 target{0.0f, 0.0f, 0.0f};
        glm::vec3 up{0.0f, 1.0f, 0.0f};

        float fov = 45.0f;
        float aspect = 4.0f;
        float znear = 0.1f;
        float zfar = 100.0f;

        glm::mat4 getView() const;
        glm::mat4 getProjection() const;


};