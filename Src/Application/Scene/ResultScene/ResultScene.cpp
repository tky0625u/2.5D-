#include "ResultScene.h"
#include"../SceneManager.h"
#include"../../WindowUI/WindowUI.h"
#include"../../Object/UI/Timer/TimerManager.h"

#include<fstream>
#include<sstream>

void ResultScene::Update()
{
	if (!m_fedeinFlg && m_brackAlpha > 0.0f)
	{
		m_brackAlpha -= 0.05f;
	}
	else if (m_fedeinFlg)
	{
		m_brackAlpha += 0.01f;
	}
	m_brackColor = { 0.0f,0.0f,0.0f,m_brackAlpha };

	if (m_ramdomFlg)
	{
		m_timer->Random();
		if (!m_ramdomSoundFlg)
		{
			KdAudioManager::Instance().Play("Asset/Sounds/SE/Result/電子ルーレット回転中.WAV", 0.1f, false);
			m_ramdomSoundFlg = true;
		}
	}

	Event();
}

void ResultScene::PostUpdate()
{
	m_timer->PostUpdate();

	m_frame++;
	if (m_frame >= SECOND * 1)
	{
		if (m_ramdomSoundFlg && !m_StopSoundFlg)
		{
			KdAudioManager::Instance().StopAllSound();
			KdAudioManager::Instance().Play("Asset/Sounds/SE/Result/電子ルーレット停止ボタンを押す.WAV", 0.1f, false);
			m_StopSoundFlg = true;
		}
		if (m_ResultTime == 0)m_timer->TimeNO();
		m_ramdomFlg = false;
	}
}

void ResultScene::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.Begin();
	{
		m_timer->DrawSprite();
		KdShaderManager::Instance().m_spriteShader.DrawBox((int)m_brackPos.x, (int)m_brackPos.y, 640, 360, &m_brackColor, true);
	}
	KdShaderManager::Instance().m_spriteShader.End();
}

void ResultScene::Load(std::string a_filePath)
{
	std::ifstream ifs(a_filePath);
	if (ifs.is_open())
	{
		std::string lineString;

		getline(ifs, lineString);
		getline(ifs, lineString);
		const int Data = stoi(lineString);

		m_timer = std::make_shared<TimerManager>();
		m_timer->SetPos(Math::Vector2{ -200,0 });
		m_timer->SetSize(2.0f);
		m_timer->Init();

		if (Data > 0)
		{
			for (int i = 0; i < Data; i++)
			{
				m_timer->Scroll();
			}

			getline(ifs, lineString);
			getline(ifs, lineString);
			const bool GameOverFlg = stoi(lineString);

			if (!GameOverFlg)BestWrite("ResultTime/BestTime.csv", Data);
		}

		m_ResultTime = Data;
	}

	ifs.close();
}

void ResultScene::BestWrite(std::string a_filePath,int Time)
{
	std::ifstream ifs(a_filePath);

	std::vector<int> BestTimerList;
	if (ifs.is_open())
	{
		std::string lineString;

		getline(ifs, lineString);
		getline(ifs, lineString);
		const int Data = stoi(lineString);

		if ((Data > Time && Time > 0) || Data == 0)
		{
			std::ofstream ost(a_filePath);

			if (ost.is_open())
			{
				ost << "BestTime" << "\n" << Time;

				ost.close();
			}
		}
	}

	ifs.close();
}

void ResultScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		m_fedeinFlg = true;
	}

	if (m_fedeinFlg && m_brackAlpha >= 1.0f)
	{
		KdAudioManager::Instance().StopAllSound();
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
}

void ResultScene::Init()
{
	//フェードイン===============================================================================================================
	m_brackAlpha = 1.0f;
	m_brackPos = {};
	m_brackColor = { 0.0f,0.0f,0.0f,m_brackAlpha };
	m_fedeinFlg = false;
	//===========================================================================================================================

	m_ResultTime = 0;
	m_frame = 0;
	m_ramdomFlg = true;
	m_ramdomSoundFlg = false;
	m_StopSoundFlg = false;
	Load("ResultTime/ResultTime.csv");
	ShowCursor(true);
}
