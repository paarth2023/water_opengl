#pragma once

#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
    unsigned int ID;

public:
    Shader(const char *veretexPath, const char *fragmentPath);
    ~Shader();

    void use() const;
    void setFloat(const std::string &name, float value) const;
    void setInt(const std::string &name, int value) const;
    void setBool(const std::string &name, bool value) const;

    void setMat2(const std::string &name, glm::mat2 &mat2) const;
    void setMat3(const std::string &name, glm::mat3 &mat3) const;
    void setMat4(const std::string &name, glm::mat4 &mat4) const;

private:
    void checkCompileErrors(unsigned int shader, std::string type);
};
