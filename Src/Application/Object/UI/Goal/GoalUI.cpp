#include "GoalUI.h"
#include"../../../WindowUI/WindowUI.h"

void GoalUI::Update()
{
	m_size += GoalSIZEUP;
	if (m_size > GoalSIZEMAX)
	{
		m_size = GoalSIZEMAX;
		m_finishFlg = true;
	}
}

void GoalUI::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_Tex, (int)m_pos.x, (int)m_pos.y, int(m_Tex.GetWidth() * m_size), int(m_Tex.GetHeight() * m_size));
}

void GoalUI::Init()
{
	m_pos = {};
	m_size = 0.0f;
	m_finishFlg = false;
	m_Tex.Load("Asset/Textures/UI/Goal/Goal.png");
}
