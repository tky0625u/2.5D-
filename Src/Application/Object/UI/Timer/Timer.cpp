#include "Timer.h"

void Timer::Update()
{
	m_rect = { m_cutX,0,TIMERWIDESIZE,TIMERHIGHTSIZE };
	Math::Matrix Scale = Math::Matrix::CreateScale(0.07, 1.0, 0);
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos.x, m_pos.y, 0);
	m_Mat = Scale * Trans;
}

void Timer::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_Mat);
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pTex, 0, 0, &m_rect, &m_color, { 0.5f,1.0f });
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
	if(Number<=1)m_pos = { (float)commaPos.x - (Number * 60)+100,commaPos.y };  //60秒以下
	else{ m_pos = { (float)commaPos.x - (Number * 60) + 80,commaPos.y }; }      //それ以上
}
