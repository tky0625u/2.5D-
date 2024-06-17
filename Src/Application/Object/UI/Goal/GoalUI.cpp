#include "GoalUI.h"
#include"../../../WindowUI/WindowUI.h"

void GoalUI::Update()
{
	m_size += 0.2f;
	if (m_size > 1.0f)m_size = 1.0f;
}

void GoalUI::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_Tex, m_pos.x, m_pos.y, m_Tex.GetWidth() * m_size, m_Tex.GetHeight() * m_size);
}

void GoalUI::Init()
{
	m_pos = {};
	m_size = 0.0f;
	m_Tex.Load("Asset/Textures/UI/Goal/Goal.png");
}
