//
//  Viscosity.h
//  FluidSimDemo
//
//

#pragma once

#include <glm/glm.hpp>

class Viscosity
{
public:
    Viscosity();

    void SetH(float h);
    float GetH() const;

    float CalcL(const glm::vec2& r) const;

private:
    float m_h, m_h4;
};

