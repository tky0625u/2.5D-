#include "Crick.h"

void Crick::Update()
{
	m_angle++;
	if (m_angle > 360.0f)m_angle -= 360.0f;

	m_alpha = sin(DirectX::XMConvertToRadians(m_angle)) + 1.2f;

	m_color = { 1,1,1,m_alpha };
}

void Crick::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (int)m_pos.x, (int)m_pos.y, int(m_rect.width * m_size), int(m_rect.height * m_size), &m_rect, &m_color);
}

void Crick::Init()
{
	m_pos = { 0.0f,-200.0f };
	m_alpha = 1.0f;
	m_color = { 1,1,1,m_alpha };
	m_rect = { 0,0,745,115 };
	m_size = 0.5f;
	m_angle = 0.0f;
	m_tex.Load("Asset/Textures/UI/Crick/crick.png");
}
