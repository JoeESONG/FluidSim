//
//  Mesh.h
//  FluidSimDemo
//
//

#pragma once

#include <vector>

#include <GL/glew.h>

typedef unsigned short ushort;

struct Mesh
{
    GLenum m_mode;
    std::vector<float> m_vertices;
    std::vector<ushort> m_indices;
};

