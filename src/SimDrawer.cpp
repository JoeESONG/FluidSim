//
//  SimDrawer.cpp
//  FluidSimDemo
//
//

#include "SimDrawer.h"

SimDrawer::SimDrawer()
{

}

bool SimDrawer::Init()
{
    if(!m_circleDrawer.Init() || !m_waterTankDrawer.Init())
    {
        return false;
    }

    return true;
}

void SimDrawer::Destroy()
{
    m_circleDrawer.Destroy();
    m_waterTankDrawer.Destroy();
}

void SimDrawer::Draw(const SimEnv& env, const std::vector<Particle>& particles, float scale, const glm::vec2& offset)
{
    m_waterTankDrawer.Draw(env, scale, offset, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

    float coreRadius = env.GetCoreRadius() * scale;

    int particleCount = int(particles.size());

    for(int i = 0; i < particleCount; ++i)
    {
        glm::vec2 pos = particles[i].GetPos() * scale + offset;

        m_circleDrawer.Draw(
            { pos.x, pos.y, 0.0f, coreRadius }, 0.0f, 2.0f,
            glm::vec3(0.1f, 0.4f, 0.7f), glm::vec3(0.0f, 0.0f, 0.0f));
    }
}

void SimDrawer::Resize(int width, int height)
{
    m_circleDrawer.Resize(width, height);
    m_waterTankDrawer.Resize(width, height);
}

