//
//  Spiky.cpp
//  FluidSimDemo
//
//

#include "Spiky.h"

#include <glm/gtc/constants.hpp>

Spiky::Spiky()
    : m_h(0.0f)
    , m_h3(0.0f)
{

}

void Spiky::SetH(float h)
{
    m_h = h;
    m_h3 = m_h * m_h * m_h;
}

float Spiky::GetH() const
{
    return m_h;
}

glm::vec2 Spiky::CalcG(const glm::vec2& r) const
{
    float len = glm::length(r);

    if(len <= 0.0f || len >= m_h)
    {
        return glm::vec2(0.0f, 0.0f);
    }

    float t = 1.0 - len / m_h;
    return -30.0f * (r / len) / (glm::pi<float>() * m_h3) * t * t;
}

