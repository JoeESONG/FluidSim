//
//  WaterTankDrawer.cpp
//  FluidSimDemo
//
//

#include "WaterTankDrawer.h"

bool WaterTankDrawer::Init()
{
    if(!m_shader.Init("WaterTank.vert", "WaterTank.frag"))
    {
        return false;
    }

    return true;
}

void WaterTankDrawer::Destroy()
{
    MeshDrawer::Destroy();
    m_shader.Destroy();
}

void WaterTankDrawer::Draw(const SimEnv& env, float scale, const glm::vec2& offset, const glm::vec4& color)
{
    glm::vec2 waterTankSize = env.GetWaterTankSize();

    glm::vec2 p0, p1, p2, p3;
    p0 = glm::vec2(0.0f, 0.0f) * scale + offset;
    p1 = glm::vec2(0.0f, waterTankSize.y) * scale + offset;
    p2 = glm::vec2(waterTankSize.x, 0.0f) * scale + offset;
    p3 = waterTankSize * scale + offset;

    Mesh mesh{
        GL_TRIANGLES,
        {
            p0.x, p0.y,
            p1.x, p1.y,
            p1.x - 5.0f, p1.y,
            p0.x - 5.0f, p0.y,
            p0.x - 5.0f, p0.y - 5.0f,
            p2.x + 5.0f, p2.y - 5.0f,
            p2.x + 5.0f, p2.y,
            p3.x + 5.0f, p3.y,
            p3.x, p3.y,
            p2.x, p2.y
        },
        {
            0, 1, 2, 0, 2, 3,
            3, 4, 5, 3, 5, 6,
            6, 7, 8, 6, 8, 9
        }
    };

    MeshDrawer::Update(mesh);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    m_shader.On();

    m_shader.SetUniform("uColor", color.x, color.y, color.z, color.w);

    MeshDrawer::Draw();

    m_shader.Off();

    glDisable(GL_BLEND);
}

void WaterTankDrawer::Resize(int width, int height)
{
    m_shader.On();
    m_shader.SetUniform("uResolution", width, height);
    m_shader.Off();
}

void WaterTankDrawer::UpdateVAO()
{
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    m_shader.SetAttrib("aPos", 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

