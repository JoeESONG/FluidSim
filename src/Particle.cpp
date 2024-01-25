//
//  Particle.cpp
//  FluidSimDemo
//
//

#include "Particle.h"

Particle::Particle()
    : m_density(0.0f)
    , m_pos(0.0f, 0.0f)
    , m_vel(0.0f, 0.0f)
    , m_force(0.0f, 0.0f)
    , m_prevForce(0.0f, 0.0f)
{

}

void Particle::SetDensity(float density)
{
    m_density = density;
}

float Particle::GetDensity() const
{
    return m_density;
}

void Particle::SetPos(const glm::vec2& pos)
{
    m_pos = pos;
}

glm::vec2 Particle::GetPos() const
{
    return m_pos;
}

void Particle::SetVel(const glm::vec2& vel)
{
    m_vel = vel;
}

glm::vec2 Particle::GetVel() const
{
    return m_vel;
}

void Particle::SetForce(const glm::vec2& force)
{
    m_force = force;
}

glm::vec2 Particle::GetForce() const
{
    return m_force;
}

void Particle::SetPrevForce(const glm::vec2& prevForce)
{
    m_prevForce = prevForce;
}

glm::vec2 Particle::GetPrevForce() const
{
    return m_prevForce;
}

void Particle::UpdatePos(float dt)
{
    m_vel += 0.5f * dt * (m_prevForce / m_density);
    m_pos += dt * m_vel;
}

void Particle::UpdateVel(float dt)
{
    m_vel += 0.5f * dt * (m_force / m_density);
}

