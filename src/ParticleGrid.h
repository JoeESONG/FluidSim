//
//  ParticleGrid.h
//  FluidSimDemo
//
//

#pragma once

#include <vector>

#include "Particle.h"

class ParticleGrid
{
public:
    ParticleGrid();

    void InitGrid(const glm::vec2& size, float radius);
    void FillParticles(const std::vector<Particle>& particles);
    std::vector<int> QueryNeighbors(const Particle& particle) const;

private:
    float m_radius;
    std::vector<std::vector<std::vector<int>>> m_grid;
};

