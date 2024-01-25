//
//  Particle.h
//  FluidSimDemo
//
//

#pragma once

#include <glm/glm.hpp>

class Particle
{
public:
    Particle();

    void SetDensity(float density);
    float GetDensity() const;

    void SetPos(const glm::vec2& pos);
    glm::vec2 GetPos() const;

    void SetVel(const glm::vec2& vel);
    glm::vec2 GetVel() const;

    void SetForce(const glm::vec2& force);
    glm::vec2 GetForce() const;

    void SetPrevForce(const glm::vec2& prevForce);
    glm::vec2 GetPrevForce() const;

    void UpdatePos(float dt);
    void UpdateVel(float dt);

private:
    float m_density;

    glm::vec2 m_pos;
    glm::vec2 m_vel;
    glm::vec2 m_force;
    glm::vec2 m_prevForce;
};

