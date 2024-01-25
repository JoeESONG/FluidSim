//
//  SimDrawer.h
//  FluidSimDemo
//
//

#pragma once

#include <vector>

#include "SimEnv.h"
#include "Particle.h"
#include "CircleDrawer.h"
#include "WaterTankDrawer.h"

class SimDrawer
{
public:
    SimDrawer();

    bool Init();
    void Destroy();

    void Draw(const SimEnv& env, const std::vector<Particle>& particles, float scale, const glm::vec2& offset);

    void Resize(int width, int height);

private:
    CircleDrawer m_circleDrawer;
    WaterTankDrawer m_waterTankDrawer;
};

