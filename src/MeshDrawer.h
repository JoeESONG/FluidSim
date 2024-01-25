//
//  MeshDrawer.h
//  FluidSimDemo
//
//

#pragma once

#include <GL/glew.h>

#include "Mesh.h"

class MeshDrawer
{
public:
    MeshDrawer();
    virtual ~MeshDrawer();

    virtual bool Init();
    virtual void Destroy();
    virtual void Draw();
    virtual void Update(const Mesh& mesh);

protected:
    GLenum m_mode;
    GLuint m_vao, m_vbo, m_ibo;
    int m_vboSize, m_iboSize;

    virtual void UpdateVAO() = 0;
};

