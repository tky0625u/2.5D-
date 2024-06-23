#include "TItle.h"

void Title::Update()
{
	m_angle ++;
	if (m_angle > 360.0f)m_angle -= 360.0f;

	m_move.y = cos(DirectX::XMConvertToRadians(m_angle)) * 0.1f;
	m_pos += m_move;
}

void Title::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (int)m_pos.x, (int)m_pos.y, int(m_rect.width * m_size), int(m_rect.height * m_size), &m_rect);
}

void Title::Init()
{
	m_pos = { 0.0f,0.0f };
	m_move = { 0.0f,0.1f };
	m_rect = { 0,0,1110,312 };
	m_size =1.0f;
	m_angle = 0.0f;
	m_tex.Load("Asset/Textures/UI/Title/SkyRun.png");
}
