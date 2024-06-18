#include "GameOver.h"

void GameOverUI::Update()
{
	m_size += GameOverSIZEUP;
	if (m_size > GameOverSIZEMAX)
	{
		m_size = GameOverSIZEMAX;
		m_finishFlg = true;
	}
}

void GameOverUI::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_Tex, (int)m_pos.x, (int)m_pos.y, int(m_Tex.GetWidth() * m_size), int(m_Tex.GetHeight() * m_size));
}

void GameOverUI::Init()
{
	m_pos = {};
	m_size = 0.0f;
	m_finishFlg = false;
	m_Tex.Load("Asset/Textures/UI/GameOver/GameOver.png");
}
