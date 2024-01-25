//
//  SimRunner.cpp
//  FluidSimDemo
//
//

#include "SimRunner.h"

#include <cmath>

// #include <iostream>
#include <algorithm>

#include <glm/gtx/string_cast.hpp>

static float CalcDist(float w, float h, int n)
{
	float p = w + h, q = w * h;
	return 2.0f * q / (p + std::sqrt(p * p + 4.0f * q * (n - 1)));
}

SimRunner::SimRunner()
{

}

void SimRunner::SetEnv(const SimEnv& env)
{
	m_simEnv = env;
	Init();
}

const SimEnv& SimRunner::GetEnv() const
{
	return m_simEnv;
}

const std::vector<Particle>& SimRunner::GetParticles() const
{
	return m_particles;
}

void SimRunner::Reset()
{
	glm::vec2 waterTankSize = m_simEnv.GetWaterTankSize();
	glm::vec2 waterBlobSize = m_simEnv.GetWaterBlobSize();
	float waterBlobInitY = m_simEnv.GetWaterBlobInitY();

	glm::vec2 startPos((waterTankSize.x - waterBlobSize.x) * 0.5f, waterBlobInitY);

	int particleCount = m_simEnv.GetParticleCount();

	float particleDist = CalcDist(waterBlobSize.x, waterBlobSize.y, particleCount);
	particleDist = std::min(m_simEnv.m_coreRadius * 0.5f, particleDist);

	int particleRows, particleCols;
	particleRows = int(waterBlobSize.y / particleDist);
	particleCols = int(waterBlobSize.x / particleDist);

	for (int r = 0; r < particleRows; ++r)
	{
		for (int c = 0; c < particleCols; ++c)
		{
			int particleIndex = r * particleCols + c;

			if (particleIndex < particleCount)
			{
				m_particles[particleIndex] = Particle();
				m_particles[particleIndex].SetPos(startPos + glm::vec2(c, r) * particleDist);
			}
		}
	}

	m_particleGrid.FillParticles(m_particles);

	float m = m_simEnv.GetParticleMass();
	float g = m_simEnv.GetGravity();

	for (int i = 0; i < particleCount; ++i)
	{
		float density = 0.0f;

		Particle& p = m_particles[i];
		glm::vec2 pPos = p.GetPos();

		std::vector<int> neighbors = m_particleGrid.QueryNeighbors(p);
		int neighborCount = int(neighbors.size());

		for (int j = 0; j < neighborCount; ++j)
		{
			const Particle& q = m_particles[neighbors[j]];
			density += m * m_poly6.Calc(pPos - q.GetPos());;
		}

		p.SetDensity(density);

		glm::vec2 gravityForce(0.0f, m * g / density);

		p.SetForce(gravityForce);
		p.SetPrevForce(gravityForce);
	}
}

void SimRunner::Update()
{
	float coreRadius = m_simEnv.GetCoreRadius();

	float dt = m_simEnv.GetDeltaTime();

	float m = m_simEnv.GetParticleMass();
	float g = m_simEnv.GetGravity();

	float restDensity = m_simEnv.GetRestDensity();

	float gasConstant = m_simEnv.GetGasConstant();
	float viscosityConstant = m_simEnv.GetViscosityConstant();
	float surfaceTensionConstant = m_simEnv.GetSurfaceTensionConstant();

	int particleCount = m_simEnv.GetParticleCount();

	for (int i = 0; i < particleCount; ++i)
	{
		m_particles[i].UpdatePos(dt);
	}

	m_particleGrid.FillParticles(m_particles);

	for (int i = 0; i < particleCount; ++i)
	{
		float density = 0.0f;

		Particle& p = m_particles[i];
		glm::vec2 pPos = p.GetPos();

		std::vector<int> neighbors = m_particleGrid.QueryNeighbors(p);
		int neighborCount = int(neighbors.size());

		// if(i == 0) std::cout << "pPos: " << glm::to_string(pPos) << std::endl;

		for (int j = 0; j < neighborCount; ++j)
		{
			const Particle& q = m_particles[neighbors[j]];
			density += m * m_poly6.Calc(pPos - q.GetPos());;

			// if(i == 0) std::cout << "qPos: " << glm::to_string(q.GetPos()) << std::endl;
		}

		p.SetDensity(density);
	}

	for (int i = 0; i < particleCount; ++i)
	{
		Particle& p = m_particles[i];

		glm::vec2 pPos = p.GetPos();
		glm::vec2 pVel = p.GetVel();

		float pDensity = p.GetDensity();
		float pPressure = std::max(0.0f, gasConstant * (pDensity - restDensity));
		// float pPressure = gasConstant * (pDensity - restDensity);

		glm::vec2 force(0.0f, m * g / pDensity);
		// if(i == 0) std::cout << "force 1: " << glm::to_string(force) << std::endl;

		std::vector<int> neighbors = m_particleGrid.QueryNeighbors(p);
		int neighborCount = int(neighbors.size());

		for (int j = 0; j < neighborCount; ++j)
		{
			const Particle& q = m_particles[neighbors[j]];

			float qDensity = q.GetDensity();
			float qPressure = std::max(0.0f, gasConstant * (qDensity - restDensity));
			// float qPressure = gasConstant * (qDensity - restDensity);

			float t = m / qDensity;
			glm::vec2 r = pPos - q.GetPos();

			if (m_simEnv.m_useSpikyKernelForPressure)
			{


				force += -0.5f * t * (pPressure + qPressure) * m_spiky.CalcG(r);

			}
			else
			{
				force += -0.5f * t * (pPressure + qPressure) * m_poly6.CalcG(r);

			}

			if (m_simEnv.m_useViscosityKernel)
			{
				force += viscosityConstant * t * (q.GetVel() - pVel) * m_viscosity.CalcL(r);

			}

			if (m_simEnv.m_usePoly6KernelForSurfaceTension)
			{
				glm::vec2 n = t * m_poly6.CalcG(r);


				if (glm::length(n) > 1.0f) // normal length threshold
				{
					force += -surfaceTensionConstant * t * m_poly6.CalcL(r) * glm::normalize(n);

				}
			}
		}

		p.SetForce(force);
	}

	glm::vec2 waterTankSize = m_simEnv.GetWaterTankSize();

	for (int i = 0; i < particleCount; ++i)
	{
		Particle& p = m_particles[i];
		p.UpdateVel(dt);

		glm::vec2 pos = p.GetPos();
		glm::vec2 vel = p.GetVel();

		if (pos.x < coreRadius)
		{
			pos.x = coreRadius;
			vel.x *= -0.2f;
		}
		else if (pos.x > waterTankSize.x - coreRadius)
		{
			pos.x = waterTankSize.x - coreRadius;
			vel.x *= -0.2f;
		}

		if (pos.y < coreRadius)
		{
			pos.y = coreRadius;
			vel.y *= -0.2f;
		}

		p.SetPos(pos);
		p.SetVel(vel);
	}
}

void SimRunner::Init()
{
	float coreRadius = m_simEnv.GetCoreRadius();

	m_poly6.SetH(coreRadius);
	m_spiky.SetH(coreRadius);
	m_viscosity.SetH(coreRadius);

	m_particles.resize(m_simEnv.GetParticleCount());

	glm::vec2 waterTankSize = m_simEnv.GetWaterTankSize();
	glm::vec2 waterBlobSize = m_simEnv.GetWaterBlobSize();
	float waterBlobInitY = m_simEnv.GetWaterBlobInitY();

	glm::vec2 simSize(std::max(waterTankSize.x, waterBlobSize.x),
		std::max(waterTankSize.y, waterBlobInitY + waterBlobSize.y));

	m_particleGrid.InitGrid(simSize, coreRadius);

	Reset();
}

