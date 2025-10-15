#pragma once

#include <glm/glm.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    Camera(
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = -90.0f,
        float pitch = 0.0f,
        float fov = 45.0f,
        float aspect = 4.0f/3.0f,
        float znear = 0.1f,
        float zfar = 100.0f
    );

    glm::mat4 getView() const;
    glm::mat4 getProjection() const;

    void processKeyboard(Camera_Movement direction, float deltaTime);
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void processMouseScroll(float yoffset);

    // Getters
    glm::vec3 getPosition() const;
    glm::vec3 getFront() const;
    glm::vec3 getUp() const;
    glm::vec3 getRight() const;
    float getYaw() const;
    float getPitch() const;
    float getFov() const;
    float getAspect() const;
    float getZNear() const;
    float getZFar() const;

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;
    float fov;
    float aspect;
    float znear;
    float zfar;

    void updateCameraVectors();
};