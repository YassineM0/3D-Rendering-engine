#pragma once
#include <string>
#include <glad/gl.h>
#include <iostream>
#include <glm/glm.hpp>

class Shader {
public:
    unsigned int id = 0;
    Shader() = default;
    bool compileFromSource(const char* vsSrc, const char* fsSrc);
    void use() const {glUseProgram(id);}
    void setMat4(const std::string& name, const glm::mat4& m) const;
    void setVec3(const std::string& name, const glm::vec3& v) const;
}