//
//  MeshDrawer.cpp
//  FluidSimDemo
//
//

#include "MeshDrawer.h"

MeshDrawer::MeshDrawer()
    : m_mode(GL_TRIANGLES)
    , m_vao(0), m_vbo(0), m_ibo(0)
    , m_vboSize(0), m_iboSize(0)
{

}

MeshDrawer::~MeshDrawer()
{

}

bool MeshDrawer::Init()
{
    return true;
}

void MeshDrawer::Destroy()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);

    m_mode = GL_TRIANGLES;
    m_vao = m_vbo = m_ibo = 0;
    m_vboSize = m_iboSize = 0;
}

void MeshDrawer::Draw()
{
    glBindVertexArray(m_vao);
    glDrawElements(m_mode, m_iboSize / sizeof(ushort), GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}

void MeshDrawer::Update(const Mesh& mesh)
{
    m_mode = mesh.m_mode;

    int vboSize = mesh.m_vertices.size() * sizeof(float);

    if(vboSize != m_vboSize)
    {
        m_vboSize = vboSize;

        glDeleteBuffers(1, &m_vbo);
        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, m_vboSize, mesh.m_vertices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    else
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, m_vboSize, mesh.m_vertices.data());
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    int iboSize = mesh.m_indices.size() * sizeof(ushort);

    if(iboSize != m_iboSize)
    {
        m_iboSize = iboSize;

        glDeleteBuffers(1, &m_ibo);
        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_iboSize, mesh.m_indices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_iboSize, mesh.m_indices.data());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    if(m_vao == 0)
    {
        glGenVertexArrays(1, &m_vao);
    }

    UpdateVAO();
}

