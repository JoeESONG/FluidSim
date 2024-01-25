//
//  FluidSimEffect.h
//  FluidSimDemo
//
//

#pragma once

#include "SimRunner.h"
#include "SimDrawer.h"

class FluidSimEffect
{
public:
    FluidSimEffect();

    void SetEnv(const SimEnv& env);

    bool Init();
    void Destroy();
    void Draw();
    void Update(bool playing);
    void Reset();

    void Resize(int width, int height);

private:
    SimEnv m_simEnv;
    SimRunner m_simRunner;
    SimDrawer m_simDrawer;
};

