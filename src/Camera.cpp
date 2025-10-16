#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(
    glm::vec3 position,
    glm::vec3 up,
    float yaw,
    float pitch,
    float fov,
    float aspect,
    float znear,
    float zfar
) : position(position), worldUp(up), yaw(yaw), pitch(pitch), fov(fov), aspect(aspect), znear(znear), zfar(zfar) {
    updateCameraVectors();
}

glm::mat4 Camera::getModel() const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));   
    model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f)); 
    model = glm::scale(model, glm::vec3(1.0f));                  
    return model;
}

glm::mat4 Camera::getView() const {
    return glm::lookAt(position, position + front, up);
}

glm::mat4 Camera::getProjection() const {
    return glm::perspective(glm::radians(fov), aspect, znear, zfar);
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = 2.5f * deltaTime;
    if (direction == FORWARD)
        position += front * velocity;
    if (direction == BACKWARD)
        position -= front * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }
    updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset) {
    fov -= yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

void Camera::updateCameraVectors() {
    glm::vec3 frontVec;
    frontVec.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    frontVec.y = sin(glm::radians(pitch));
    frontVec.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(frontVec);
    right = glm::normalize(glm::cross(front, worldUp));
    up    = glm::normalize(glm::cross(right, front));
}

glm::vec3 Camera::getPosition() const { return position; }
glm::vec3 Camera::getFront() const { return front; }
glm::vec3 Camera::getUp() const { return up; }
glm::vec3 Camera::getRight() const { return right; }
float Camera::getYaw() const { return yaw; }
float Camera::getPitch() const { return pitch; }
float Camera::getFov() const { return fov; }
float Camera::getAspect() const { return aspect; }
float Camera::getZNear() const { return znear; }
float Camera::getZFar() const { return zfar; }