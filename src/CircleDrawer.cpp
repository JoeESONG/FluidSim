//
//  CircleDrawer.cpp
//  FluidSimDemo
//
//

#include "CircleDrawer.h"

bool CircleDrawer::Init()
{
	if (!m_shader.Init("Circle.vert", "Circle.frag"))
	{
		return false;
	}

	Mesh mesh
	{
		GL_TRIANGLES,
		{ -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 1.0f, -1.0f },
		{ 0, 1, 2, 2, 1, 3 }
	};

	MeshDrawer::Update(mesh);

	return true;
}

void CircleDrawer::Destroy()
{
	MeshDrawer::Destroy();
	m_shader.Destroy();
}

void CircleDrawer::Draw(
	const Circle& circle, float border, float antialias,
	const glm::vec3& color, const glm::vec3& borderColor)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_shader.On();

	m_shader.SetUniform("uPos", circle.m_x, circle.m_y);
	m_shader.SetUniform("uInnerRadius", circle.m_innerRadius);
	m_shader.SetUniform("uOuterRadius", circle.m_outerRadius);
	m_shader.SetUniform("uBorder", border);
	m_shader.SetUniform("uAntialias", antialias);
	m_shader.SetUniform("uColor", color.x, color.y, color.z);
	m_shader.SetUniform("uBorderColor", borderColor.x, borderColor.y, borderColor.z);

	MeshDrawer::Draw();

	m_shader.Off();

	glDisable(GL_BLEND);
}

void CircleDrawer::Resize(int width, int height)
{
	m_shader.On();
	m_shader.SetUniform("uResolution", width, height);
	m_shader.Off();
}

void CircleDrawer::UpdateVAO()
{
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

	m_shader.SetAttrib("aPos", 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

