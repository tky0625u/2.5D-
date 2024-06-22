#include "Particle.h"

void Particle::Update()
{
	m_lifespan--;
	m_size *= 0.95f;
	if (m_lifespan <= 0)
	{
		m_lifespan = 0;
		m_isExpired = true;
	}

	m_pos += m_move;
}

void Particle::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pTex, (int)m_pos.x, (int)m_pos.y, int(m_rect.width * m_size), int(m_rect.height * m_size), &m_rect);
}

void Particle::Init()
{
	m_pos = {};
	m_rect = { 0,0,20,20 };
	m_move = {};
	m_size = 1.0f;
	m_lifespan = 0;

	m_cursorPos = {};
}

void Particle::Emit(Math::Vector2 a_pos, Math::Vector2 a_move, float a_size, int a_lifespan)
{
	m_pos = a_pos;
	m_move = a_move;
	m_size = a_size;
	m_lifespan = a_lifespan;
}
