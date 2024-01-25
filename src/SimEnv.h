//
//  SimEnv.h
//  FluidSimDemo
//
//

#pragma once

#include <glm/glm.hpp>

class SimEnv
{
public:
    SimEnv();

    void SetDeltaTime(float dt);
    float GetDeltaTime() const;

    void SetGravity(float gravity);
    float GetGravity() const;

    void SetRestDensity(float density);
    float GetRestDensity() const;

    void SetGasConstant(float constant);
    float GetGasConstant() const;

    void SetViscosityConstant(float constant);
    float GetViscosityConstant() const;

    void SetSurfaceTensionConstant(float constant);
    float GetSurfaceTensionConstant() const;

    void SetCoreRadius(float radius);
    float GetCoreRadius() const;

    void SetWaterTankSize(const glm::vec2& size);
    glm::vec2 GetWaterTankSize() const;

    void SetWaterBlobSize(const glm::vec2& size);
    glm::vec2 GetWaterBlobSize() const;

    void SetWaterBlobInitY(float y);
    float GetWaterBlobInitY() const;

    void SetParticleCount(int count);
    int GetParticleCount() const;

    void SetParticleMass(float mass);
    float GetParticleMass() const;

public:
    float m_deltaTime;

    float m_gravity;
    float m_restDensity;

    float m_gasConstant;
    float m_viscosityConstant;
    float m_surfaceTensionConstant;

    float m_coreRadius;

    glm::vec2 m_waterTankSize;
    glm::vec2 m_waterBlobSize;
    float m_waterBlobInitY;

    int m_particleCount;
    float m_particleMass;

    bool m_useSpikyKernelForPressure;
    bool m_useViscosityKernel;
    bool m_usePoly6KernelForSurfaceTension;
};

