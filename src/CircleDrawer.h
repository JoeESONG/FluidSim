//
//  CircleDrawer.h
//  FluidSimDemo
//
//

#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "Circle.h"
#include "MeshDrawer.h"

class CircleDrawer : public MeshDrawer
{
public:
    bool Init();
    void Destroy();

    void Draw(
        const Circle& circle, float border, float antialias,
        const glm::vec3& color, const glm::vec3& borderColor);

    void Resize(int width, int height);

private:
    Shader m_shader;

    void UpdateVAO();
};

