#include "ResultScene.h"
#include"../SceneManager.h"
#include"../../WindowUI/WindowUI.h"
#include"../../Object/UI/Timer/TimerManager.h"

#include<fstream>
#include<sstream>

void ResultScene::Update()
{
	if (m_frame < SECOND * 1)m_timer->Random();

	Event();
}

void ResultScene::PostUpdate()
{
	m_timer->PostUpdate();

	m_frame++;
}

void ResultScene::DrawSprite()
{
	m_timer->DrawSprite();
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
		m_timer->Init();
		m_timer->SetSize(2.0f);

		for (int i = 0; i < Data; i++)
		{
			m_timer->Scroll();
		}

		getline(ifs, lineString);
		getline(ifs, lineString);
		const bool GameOverFlg= stoi(lineString);

		if(!GameOverFlg)BestWrite("ResultTime/BestTime.csv", Data);
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
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}
}

void ResultScene::Init()
{
	Load("ResultTime/ResultTime.csv");
	m_frame = 0;
	ShowCursor(true);
}
