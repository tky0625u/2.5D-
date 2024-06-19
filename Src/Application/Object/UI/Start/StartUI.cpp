#include "StartUI.h"
#include"../../../WindowUI/WindowUI.h"

void StartUI::Update()
{
	if (!m_StartFlg)
	{
		if (m_frame < SECOND / 2)
		{
			m_size += StartSIZECHANGE;
			if (m_size > StartSIZEMAX)m_size = StartSIZEMAX;
		}
		else
		{
			m_size -= StartSIZECHANGE;
			if (m_size < 0.0f)m_size = 0.0f;
		}
	}
	else
	{
		if (m_size > StartSIZEMAX)
		{
			m_size += Start_GO_SizeUP;
			m_alpha -= StartAlphaDOWN;
		}
		else{m_size += StartSIZECHANGE;}
	}

	if (m_frame >= SECOND)
	{
		m_cutX += m_rect.width;
		if(!m_StartFlg)m_size = 0.0f;
		m_frame = 0.0f;
		if (m_cutX == m_rect.width * Start_GO)
		{
			if(!m_StartFlg)m_StartFlg = true;
		}
	}
	m_rect = { long(m_cutX),0,m_rect.width,m_rect.height };
	m_color = { 1.0f,1.0f,1.0f,m_alpha };

	if (m_alpha < 0.0f)
	{
		m_isExpired = true;
	}

	m_frame++;
}

void StartUI::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_Tex, (int)m_pos.x, (int)m_pos.y, int(m_rect.width * m_size), int(m_rect.height * m_size), &m_rect, &m_color);
}

void StartUI::Init()
{
	m_pos = {};
	m_cutX = 0;
	m_rect = { long(m_cutX),0,134,100 };
	m_alpha = 1.0f;
	m_color = { 1.0f,1.0f,1.0f,m_alpha };
	m_size = 0.0f;
	m_frame = 0.0f;
	m_StartFlg = false;
	m_Tex.Load("Asset/Textures/UI/Start/Start.png");
}
