//
//  Viscosity.cpp
//  FluidSimDemo
//
//

#include "Viscosity.h"

#include <glm/gtc/constants.hpp>

Viscosity::Viscosity()
    : m_h(0.0f)
    , m_h4(0.0f)
{

}

void Viscosity::SetH(float h)
{
    m_h = h;
    m_h4 = m_h * m_h * m_h * m_h;
}

float Viscosity::GetH() const
{
    return m_h;
}

float Viscosity::CalcL(const glm::vec2& r) const
{
    float len = glm::length(r);

    if(len >= m_h)
    {
        return 0.0f;
    }

    float t = 1.0 - len / m_h;
    return 40.0f / (glm::pi<float>() * m_h4) * t;
}

