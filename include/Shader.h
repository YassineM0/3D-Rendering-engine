#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    unsigned int id;
    Shader(const char* vertexPath, const char* fragmentPath);
    void use() const;
    void setMat4(const std::string& name, const glm::mat4& m) const;
    void setVec3(const std::string& name, const glm::vec3& v) const;
    ~Shader();

private:
    void checkCompileErrors(unsigned int shader, std::string type);
};