#include "TimerManager.h"
#include"Timer.h"

void TimerManager::Update()
{
	if (!m_startFlg)return;

	//タイマー=====================================================================================
	while (m_frame >= SECOND)  //一秒以上
	{
		Scroll();
		m_frame -= SECOND;  //一秒分マイナス
	}
	//=============================================================================================

	m_frame++;  //フレーム
}

void TimerManager::PostUpdate()
{
	for (unsigned int i = 0; i < m_timerList.size(); i++)
	{
		m_timerList[i]->PostUpdate();
	}
}

void TimerManager::DrawSprite()
{
	//タイマー=====================================================================================
	for (unsigned int i = 0; i < m_timerList.size(); i++)m_timerList[i]->DrawSprite();
	//=============================================================================================

	//コンマ=======================================================================================
	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_Tex, (int)m_pos.x, (int)m_pos.y, float(m_rect.width * m_size), float(m_rect.height * m_size), &m_rect, &m_color, { 0.5f,1.0f });
    //=============================================================================================
}

void TimerManager::Init()
{
	//コンマ=======================================================================================
	m_color = { 1,1,1,1 };
	m_rect = { 0,0,23,52 };
	m_Tex.Load("Asset/Textures/UI/Timer/comma.png");
	//=============================================================================================

	//タイマー=====================================================================================
	m_timerTex.Load("Asset/Textures/UI/Timer/number.png");
	m_second = 0;
	for (int i = 0; i < m_default; ++i)
	{
		std::shared_ptr<Timer> timer = std::make_shared<Timer>();
		timer->SetPos(i,m_pos);
		timer->SetSize(m_size);
		timer->SetTexture(&m_timerTex);
		m_timerList.push_back(timer);
	}
	//==============================================================================================

	m_frame = SECOND * SECOND * 0;  //フレーム
	m_startFlg = false;
}

void TimerManager::Random()
{
	for (unsigned int i = 0; i < m_timerList.size(); ++i)
	{
		m_timerList[i]->Scroll();
		if (m_timerList[i]->GetCutX() >= TIMERWIDESIZE * MAXNUM)m_timerList[i]->Reset();
	}
}

void TimerManager::Scroll()
{
	m_timerList[0]->Scroll();  //一の位
	//切り取り範囲変更===============================================================
	for (unsigned int i = 0; i < m_timerList.size(); i++)
	{
		//それ以外
		if (i != 1 && i != m_timerList.size() - 1)
		{
			if (m_timerList[i]->GetCutX() >= TIMERWIDESIZE * MAXNUM)  //端（9）まで来たら
			{
				m_timerList[i]->Reset();       //最初に戻す
				m_timerList[i + 1]->Scroll();  //上の位にプラス１
			}
		}
		//十の位
		else if (i == 1)
		{
			if (m_timerList[i]->GetCutX() >= TIMERWIDESIZE * MINUTENUM)  //60秒たったら
			{
				m_timerList[i]->Reset();
				m_timerList[i + 1]->Scroll();
			}
		}
		//右端
		else if (i == m_timerList.size() - 1)
		{
			if (m_timerList[i]->GetCutX() >= TIMERWIDESIZE * MAXNUM)
			{
				m_timerList[i]->Reset();
				//新しく追加　※カンスト防止=================================
				std::shared_ptr<Timer> timer = std::make_shared<Timer>();
				timer->SetPos(i + 1, m_pos);
				timer->SetTexture(&m_timerTex);
				timer->Scroll();  //1から表示させるため
				m_timerList.push_back(timer);
				//===========================================================
			}
		}
	}
	m_second++;
	//===============================================================================
}

void TimerManager::TimeNO()
{
	for (unsigned int i = 0; i < m_timerList.size(); ++i)
	{
		while (m_timerList[i]->GetCutX() != TIMERWIDESIZE * 10)
		{
			m_timerList[i]->Scroll();
		}
	}
}
