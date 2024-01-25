//
//  SimEnv.cpp
//  FluidSimDemo
//
//

#include "SimEnv.h"

SimEnv::SimEnv()
    : m_deltaTime(0.0f)
    , m_gravity(0.0f)
    , m_restDensity(0.0f)
    , m_gasConstant(0.0f)
    , m_viscosityConstant(0.0f)
    , m_surfaceTensionConstant(0.0f)
    , m_coreRadius(0.0f)
    , m_waterTankSize(0.0f, 0.0f)
    , m_waterBlobSize(0.0f, 0.0f)
    , m_waterBlobInitY(0.0f)
    , m_particleCount(0)
    , m_particleMass(0.0f)
    , m_useSpikyKernelForPressure(false)
    , m_useViscosityKernel(false)
    , m_usePoly6KernelForSurfaceTension(false)
{

}

void SimEnv::SetDeltaTime(float dt)
{
    m_deltaTime = dt;
}

float SimEnv::GetDeltaTime() const
{
    return m_deltaTime;
}

void SimEnv::SetGravity(float gravity)
{
    m_gravity = gravity;
}

float SimEnv::GetGravity() const
{
    return m_gravity;
}

void SimEnv::SetRestDensity(float density)
{
    m_restDensity = density;
}

float SimEnv::GetRestDensity() const
{
    return m_restDensity;
}

void SimEnv::SetGasConstant(float constant)
{
    m_gasConstant = constant;
}

float SimEnv::GetGasConstant() const
{
    return m_gasConstant;
}

void SimEnv::SetViscosityConstant(float constant)
{
    m_viscosityConstant = constant;
}

float SimEnv::GetViscosityConstant() const
{
    return m_viscosityConstant;
}

void SimEnv::SetSurfaceTensionConstant(float constant)
{
    m_surfaceTensionConstant = constant;
}

float SimEnv::GetSurfaceTensionConstant() const
{
    return m_surfaceTensionConstant;
}

void SimEnv::SetCoreRadius(float radius)
{
    m_coreRadius = radius;
}

float SimEnv::GetCoreRadius() const
{
    return m_coreRadius;
}

void SimEnv::SetWaterTankSize(const glm::vec2& size)
{
    m_waterTankSize = size;
}

glm::vec2 SimEnv::GetWaterTankSize() const
{
    return m_waterTankSize;
}

void SimEnv::SetWaterBlobSize(const glm::vec2& size)
{
    m_waterBlobSize = size;
}

glm::vec2 SimEnv::GetWaterBlobSize() const
{
    return m_waterBlobSize;
}

void SimEnv::SetWaterBlobInitY(float y)
{
    m_waterBlobInitY = y;
}

float SimEnv::GetWaterBlobInitY() const
{
    return m_waterBlobInitY;
}

void SimEnv::SetParticleCount(int count)
{
    m_particleCount = count;
}

int SimEnv::GetParticleCount() const
{
    return m_particleCount;
}

void SimEnv::SetParticleMass(float mass)
{
    m_particleMass = mass;
}

float SimEnv::GetParticleMass() const
{
    return m_particleMass;
}

