//
//  Shader.h
//  FluidSimDemo
//
//

#pragma once

#include <vector>
#include <string>

#include <GL/glew.h>

class Shader
{
public:
    Shader();

    bool Init(const std::string& vertPath, const std::string& fragPath);
    void Destroy();

    void On();
    void Off();

    void SetAttrib(
        const std::string name, GLint size, GLenum type,
        GLboolean normalized, GLsizei stride, const void* pointer);

    void SetUniform(const std::string name, float v0);
    void SetUniform(const std::string name, float v0, float v1);
    void SetUniform(const std::string name, float v0, float v1, float v2);
    void SetUniform(const std::string name, float v0, float v1, float v2, float v3);
    void SetUniform(const std::string name, int components, int count, const float* value);

private:
    GLuint m_program;

    GLuint Compile(GLenum stage, const std::string& path);
    GLuint Link(std::vector<GLuint>&& shaders);
};

