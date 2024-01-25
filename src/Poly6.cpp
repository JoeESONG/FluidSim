//
//  Poly6.cpp
//  FluidSimDemo
//
//

#include "Poly6.h"

#include <glm/gtx/norm.hpp>
#include <glm/gtc/constants.hpp>

Poly6::Poly6()
    : m_h(0.0f)
    , m_h2(0.0f)
    , m_h4(0.0f)
{

}

void Poly6::SetH(float h)
{
    m_h = h;
    m_h2 = m_h * m_h;
    m_h4 = m_h2 * m_h2;
}

float Poly6::GetH() const
{
    return m_h;
}

float Poly6::Calc(const glm::vec2& r) const
{
    float len2 = glm::length2(r);

    if(len2 >= m_h2)
    {
        return 0.0f;
    }

    float t = 1.0f - len2 / m_h2;
    return 4.0f / (glm::pi<float>() * m_h2) * t * t * t;
}

glm::vec2 Poly6::CalcG(const glm::vec2& r) const
{
    float len2 = glm::length2(r);

    if(len2 >= m_h2)
    {
        return glm::vec2(0.0f, 0.0f);
    }

    float t = 1.0f - len2 / m_h2;
    return -24.0f * r / (glm::pi<float>() * m_h4) * t * t;
}

float Poly6::CalcL(const glm::vec2& r) const
{
    float len2 = glm::length2(r);

    if(len2 >= m_h2)
    {
        return 0.0f;
    }

    float t = len2 / m_h2;
    return 24.0f / (glm::pi<float>() * m_h4) * (1.0f - t) * (5.0f * t - 1.0f);
}

