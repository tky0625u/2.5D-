#include "TitleScene.h"
#include "../SceneManager.h"
#include"../../Object/UI/Timer/TimerManager.h"

void TitleScene::PostUpdate()
{
	m_timer->PostUpdate();
}

void TitleScene::DrawSprite()
{
	m_timer->DrawSprite();
}

void TitleScene::Load(std::string a_filePath)
{
	std::ifstream ifs(a_filePath);

	if (ifs.is_open())
	{

		std::string lineString;

		getline(ifs, lineString);
		getline(ifs, lineString);
		const int Data = stoi(lineString);

		m_timer = std::make_shared<TimerManager>();
		m_timer->SetPos(Math::Vector2{ 0,-100 });
		m_timer->SetSize(1.5f);
		m_timer->Init();

		if (Data == 10)m_timer->TimeNO();
		else
		{
			for (int i = 0; i < Data; i++)
			{
				m_timer->Scroll();
			}
		}
	}
}

void TitleScene::Event()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Game
		);
	}
}

void TitleScene::Init()
{
	Load("ResultTime/BestTime.csv");
	ShowCursor(true);
}
