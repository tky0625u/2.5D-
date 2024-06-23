#include "Best Time.h"

void BestTime::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_tex, (int)m_pos.x, (int)m_pos.y, int(m_rect.width * m_size), int(m_rect.height * m_size), &m_rect);
}

void BestTime::Init()
{
	m_pos = {};
	m_rect = { 0,0,350,53 };
	m_size = 1.0f;
	m_tex.Load("Asset/Textures/UI/Best Time/Best Time.png");
}
