//
//  Shader.cpp
//  FluidSimDemo
//
//

#include "Shader.h"

#include <fstream>
#include <iostream>

Shader::Shader()
    : m_program(0)
{

}

bool Shader::Init(const std::string& vertPath, const std::string& fragPath)
{
    if(m_program > 0)
    {
        Destroy();
    }

    m_program = Link({Compile(GL_VERTEX_SHADER, vertPath), Compile(GL_FRAGMENT_SHADER, fragPath)});
    return m_program > 0;
}

void Shader::Destroy()
{
    glDeleteProgram(m_program);
    m_program = 0;
}

void Shader::On()
{
    glUseProgram(m_program);
}

void Shader::Off()
{
    glUseProgram(0);
}

void Shader::SetAttrib(
    const std::string name, GLint size, GLenum type,
    GLboolean normalized, GLsizei stride, const void* pointer)
{
    auto nameCStr = (const GLchar*)name.c_str();
    GLint posLoc = glGetAttribLocation(m_program, nameCStr);
    glVertexAttribPointer(posLoc, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(posLoc);
}

void Shader::SetUniform(const std::string name, float v0)
{
    auto nameCStr = (const GLchar*)name.c_str();
    glUniform1f(glGetUniformLocation(m_program, nameCStr), v0);
}

void Shader::SetUniform(const std::string name, float v0, float v1)
{
    auto nameCStr = (const GLchar*)name.c_str();
    glUniform2f(glGetUniformLocation(m_program, nameCStr), v0, v1);
}

void Shader::SetUniform(const std::string name, float v0, float v1, float v2)
{
    auto nameCStr = (const GLchar*)name.c_str();
    glUniform3f(glGetUniformLocation(m_program, nameCStr), v0, v1, v2);
}

void Shader::SetUniform(const std::string name, float v0, float v1, float v2, float v3)
{
    auto nameCStr = (const GLchar*)name.c_str();
    glUniform4f(glGetUniformLocation(m_program, nameCStr), v0, v1, v2, v3);
}

void Shader::SetUniform(const std::string name, int components, int count, const float* value)
{
    auto nameCStr = (const GLchar*)name.c_str();
    auto loc = glGetUniformLocation(m_program, nameCStr);

    if(components == 1)
    {
        glUniform1fv(loc, count, value);
    }
    else if(components == 2)
    {
        glUniform2fv(loc, count, value);
    }
    else if(components == 3)
    {
        glUniform3fv(loc, count, value);
    }
    else if(components == 4)
    {
        glUniform4fv(loc, count, value);
    }
}

GLuint Shader::Compile(GLenum stage, const std::string& path)
{
    std::ifstream input(path, std::ios::in | std::ios::binary | std::ios::ate);
    if(!input)
    {
        std::cerr << "Failed to load " << path << std::endl;
        return 0;
    }

    auto inputSize = input.tellg();
    input.seekg(0, std::ios::beg);

    std::string source(inputSize, '\0');
    input.read((char *)source.data(), inputSize);
    input.close();

    auto sourceCStr = (const GLchar*)source.c_str();

    auto shader = glCreateShader(stage);
    glShaderSource(shader, 1, &sourceCStr, nullptr);
    glCompileShader(shader);

    GLint isCompiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

    if(isCompiled != GL_TRUE)
    {
        std::cerr << "Failed to compile " << path << std::endl;

        GLint maxLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        if(maxLength > 0)
        {
            std::string infoLog(maxLength - 1, '\0');
            glGetShaderInfoLog(shader, maxLength - 1, &maxLength, (char *)infoLog.data());
            std::cerr << infoLog << std::endl;
        }

        glDeleteShader(shader);

        return 0;
    }

    return shader;
}

GLuint Shader::Link(std::vector<GLuint>&& shaders)
{
    for(const auto& shader : shaders)
    {
        if(glIsShader(shader) != GL_TRUE)
        {
            return 0;
        }
    }

    auto program = glCreateProgram();

    for(const auto& shader : shaders)
    {
        glAttachShader(program, shader);
    }

    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &isLinked);

    if(isLinked != GL_TRUE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        if(maxLength > 0)
        {
            std::string infoLog(maxLength - 1, '\0');
            glGetProgramInfoLog(program, maxLength - 1, &maxLength, (char *)infoLog.data());
            std::cerr << infoLog << std::endl;
        }

        glDeleteShader(program);

        return 0;
    }

    for(const auto& shader : shaders)
    {
        glDetachShader(program, shader);
        glDeleteShader(shader);
    }

    return program;
}

