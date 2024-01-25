//
//  ParticleGrid.cpp
//  FluidSimDemo
//
//

#include "ParticleGrid.h"

#include <cmath>

ParticleGrid::ParticleGrid()
    : m_radius(0.0f)
{

}

void ParticleGrid::InitGrid(const glm::vec2& size, float radius)
{
    m_grid.clear();

    m_radius = (radius < 0.0f)? 0.0f : radius;

    if(!(size.x > 0.0f && size.y > 0.0f && m_radius > 0.0f))
    {
        return;
    }

    int rows, cols;
    rows = int(std::ceil(size.y / m_radius));
    cols = int(std::ceil(size.x / m_radius));

    m_grid.resize(rows, std::vector<std::vector<int>>(cols));
}

void ParticleGrid::FillParticles(const std::vector<Particle>& particles)
{
    int rows, cols;
    rows = int(m_grid.size());
    cols = (rows > 0)? int(m_grid[0].size()) : 0;

    for(int r = 0; r < rows; ++r)
    {
        for(int c = 0; c < cols; ++c)
        {
            m_grid[r][c].clear();
        }
    }

    glm::vec2 pos;
    int r, c;

    int count = int(particles.size());

    for(int i = 0; i < count; ++i)
    {
        pos = particles[i].GetPos();

        r = int(pos.y / m_radius);
        c = int(pos.x / m_radius);

        r = (r < 0)? 0 : (r > rows - 1)? rows - 1 : r;
        c = (c < 0)? 0 : (c > cols - 1)? cols - 1 : c;

        m_grid[r][c].push_back(i);
    }
}

std::vector<int> ParticleGrid::QueryNeighbors(const Particle& particle) const
{
    std::vector<int> ret;

    int rows, cols;
    rows = int(m_grid.size());
    cols = (rows > 0)? int(m_grid[0].size()) : 0;

    glm::vec2 pos = particle.GetPos();

    int r, c;
    r = int(pos.y / m_radius);
    c = int(pos.x / m_radius);

    r = (r < 0)? 0 : (r > rows - 1)? rows - 1 : r;
    c = (c < 0)? 0 : (c > cols - 1)? cols - 1 : c;

    for(int i = -1; i <= 1; ++i)
    {
        for(int j = -1; j <= 1; ++j)
        {
            if((std::abs(i) + std::abs(j) > 1) ||
               (r + i < 0 || r + i > rows - 1) ||
               (c + j < 0 || c + j > cols - 1))
            {
                continue;
            }

            const std::vector<int>& indices = m_grid[r + i][c + j];
            ret.insert(ret.end(), indices.begin(), indices.end());
        }
    }

    return ret;
}

