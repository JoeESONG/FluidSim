//
//  FluidSimEffect.cpp
//  FluidSimDemo
//
//

#include "FluidSimEffect.h"

#include <GL/glew.h>

FluidSimEffect::FluidSimEffect()
{

}

void FluidSimEffect::SetEnv(const SimEnv& env)
{
    m_simRunner.SetEnv(env);
}

bool FluidSimEffect::Init()
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    if(!m_simDrawer.Init())
    {
        return false;
    }

    return true;
}

void FluidSimEffect::Destroy()
{
    m_simDrawer.Destroy();
}

void FluidSimEffect::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    m_simDrawer.Draw(m_simRunner.GetEnv(), m_simRunner.GetParticles(), 200.0f, glm::vec2(5.0f, 5.0f));
}

void FluidSimEffect::Update(bool playing)
{
    if(playing)
    {
        m_simRunner.Update();
    }
}

void FluidSimEffect::Reset()
{
    m_simRunner.Reset();
}

void FluidSimEffect::Resize(int width, int height)
{
    if(width <= 0 || height <= 0)
    {
        return;
    }

    glViewport(0, 0, width, height);

    m_simDrawer.Resize(width, height);
}

