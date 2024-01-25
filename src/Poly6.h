//
//  Poly6.h
//  FluidSimDemo
//
//

#pragma once

#include <glm/glm.hpp>

class Poly6
{
public:
    Poly6();

    void SetH(float h);
    float GetH() const;

    float Calc(const glm::vec2& r) const;
    glm::vec2 CalcG(const glm::vec2& r) const;
    float CalcL(const glm::vec2& r) const;

private:
    float m_h, m_h2, m_h4;
};

