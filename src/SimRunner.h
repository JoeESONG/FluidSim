//
//  SimRunner.h
//  FluidSimDemo
//
//

#pragma once

#include "SimEnv.h"

#include "Poly6.h"
#include "Spiky.h"
#include "Viscosity.h"

#include "Particle.h"
#include "ParticleGrid.h"

class SimRunner
{
public:
    SimRunner();

    void SetEnv(const SimEnv& env);
    const SimEnv& GetEnv() const;

    const std::vector<Particle>& GetParticles() const;

    void Reset();
    void Update();

private:
    SimEnv m_simEnv;

    Poly6 m_poly6;
    Spiky m_spiky;
    Viscosity m_viscosity;

    std::vector<Particle> m_particles;
    ParticleGrid m_particleGrid;

    void Init();
};

