#include "Exit.h"

void Exit::Update()
{
	m_angle += 1.0f;
	if (m_angle > 360.0f)m_angle -= 360.0f;
	m_alpha = sin(DirectX::XMConvertToRadians(m_angle)) + 1.5f;
	m_color = { 1,1,1,m_alpha };

	if (m_hitFlg)
	{
		m_size = 1.2f;
	}
	else
	{
		m_size = 1.0f;
	}
}

void Exit::DrawSprite()
{
	ButtomBase::DrawSprite();
}

void Exit::Init()
{
	m_pos = { -550.0f, -340.0f };
	m_rect = { 0,0,138,45 };
	m_size = 1.0f;
	m_angle = 0.0f;
	m_alpha = 1.0f;
	m_color = { 1,1,1,m_alpha };
	m_hitFlg = false;
	m_pushFlg = false;
	m_Tex.Load("Asset/Textures/UI/exit/exit.png");
}
