#include "ButtomBase.h"

void ButtomBase::Update()
{
}

void ButtomBase::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_Tex, (int)m_pos.x, (int)m_pos.y, int(m_rect.width * m_size), int(m_rect.height * m_size), &m_rect, &m_color);
}

void ButtomBase::Init()
{
}
