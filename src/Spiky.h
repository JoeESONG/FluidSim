//
//  Spiky.h
//  FluidSimDemo
//
//

#pragma once

#include <glm/glm.hpp>

class Spiky
{
public:
    Spiky();

    void SetH(float h);
    float GetH() const;

    glm::vec2 CalcG(const glm::vec2& r) const;

private:
    float m_h, m_h3;
};

