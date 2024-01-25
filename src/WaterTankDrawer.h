//
//  WaterTankDrawer.h
//  FluidSimDemo
//
//

#pragma once

#include <glm/glm.hpp>

#include "SimEnv.h"
#include "Shader.h"
#include "MeshDrawer.h"

class WaterTankDrawer : public MeshDrawer
{
public:
    bool Init();
    void Destroy();

    void Draw(const SimEnv& env, float scale, const glm::vec2& offset, const glm::vec4& color);

    void Resize(int width, int height);

private:
    Shader m_shader;

    void UpdateVAO();
};

