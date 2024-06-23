#include "TitleScene.h"
#include "../SceneManager.h"
#include"../../Object/UI/Timer/TimerManager.h"
#include"../../Object/UI/Cuesor/Cursor.h"
#include"../../Object/UI/Best TIme/Best Time.h"

void TitleScene::Update()
{
	if (m_fedeinFlg)
	{
		m_brackAlpha += 0.01f;
	}

	m_brackColor = { 0.0f,0.0f,0.0f,m_brackAlpha };
	m_cursor->Update();

	Event();
}

void TitleScene::PostUpdate()
{
	m_timer->PostUpdate();
}

void TitleScene::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.Begin();
	{
		m_timer->DrawSprite();
		m_best->DrawSprite();
		m_cursor->DrawSprite();
		KdShaderManager::Instance().m_spriteShader.DrawBox((int)m_brackPos.x, (int)m_brackPos.y, 640, 360, &m_brackColor, true);
	}
	KdShaderManager::Instance().m_spriteShader.End();	
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
		m_timer->SetPos(Math::Vector2{ 0,-150 });
		m_timer->SetSize(1.5f);
		m_timer->Init();

		if (Data == 0)m_timer->TimeNO();
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
		m_fedeinFlg = true;
	}

	if (m_brackAlpha >= 1.0f)
	{
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Game
		);
	}
}

void TitleScene::Init()
{
	//カーソル===================================================================================================================
	m_cursor = std::make_unique<Cursor>();
	m_cursor->FlgChange(true);
	//===========================================================================================================================

	//フェードイン===============================================================================================================
	m_brackAlpha = 0.0f;
	m_brackPos = {};
	m_brackColor = { 0.0f,0.0f,0.0f,m_brackAlpha };
	m_fedeinFlg = false;
	//===========================================================================================================================

	//ベストスコア===============================================================================================================
	m_best = std::make_shared<BestTime>();
	m_best->SetPos(Math::Vector2{ 0.0f,-140 });
	m_best->SetSize(0.8f);
	//===========================================================================================================================

	Load("ResultTime/BestTime.csv");
	ShowCursor(true);
}
