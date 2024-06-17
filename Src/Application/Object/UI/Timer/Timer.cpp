#include "Timer.h"

void Timer::Update()
{
	m_rect = { m_cutX,0,TIMERWIDESIZE,TIMERHIGHTSIZE };
}

void Timer::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pTex, (int)m_pos.x, (int)m_pos.y,m_rect.width,m_rect.height, &m_rect, &m_color, { 0.5f,1.0f });
}

void Timer::Init()
{
	m_cutX = 0;
	m_pos = {};
	m_color = {1,1,1,1};
	m_rect = { m_cutX,0,TIMERWIDESIZE,TIMERHIGHTSIZE };
}

void Timer::SetPos(int Number,Math::Vector2 commaPos)
{
	if(Number<=1)m_pos = { (float)commaPos.x - (Number * 90)+160,commaPos.y };  //60秒以下
	else{ m_pos = { (float)commaPos.x - (Number * 90) + 120,commaPos.y }; }      //それ以上
}
