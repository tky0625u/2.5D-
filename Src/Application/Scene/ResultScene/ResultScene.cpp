#include "ResultScene.h"
#include"../SceneManager.h"
#include"../../WindowUI/WindowUI.h"
#include"../../Object/UI/Timer/TimerManager.h"
#include"../../Object/Character/Player/Result/ResultPlayer.h"
#include"../../Object/Ground/Goal/Goal.h"
#include"../../Object/BackGround/BackGround.h"

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

	for (auto& obj : m_objList)obj->Update();

	Event();
}

void ResultScene::PostUpdate()
{
	for (auto& obj : m_objList)obj->PostUpdate();
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
		for (auto& obj : m_objList)obj->DrawSprite();
		KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::Identity);

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
			m_gameOverFlg = false;

			for (int i = 0; i < Data; i++)
			{
				m_timer->Scroll();
			}

			getline(ifs, lineString);
			getline(ifs, lineString);
			const bool GameOverFlg = stoi(lineString);

			if (!GameOverFlg)BestWrite("ResultTime/BestTime.csv", Data);
		}
		else
		{
			m_gameOverFlg = true;
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
	m_gameOverFlg = false;
	Load("ResultTime/ResultTime.csv");
	ShowCursor(true);

	//カメラ　生成＆視野角設定===================================================================================================
	m_angleX = 0;
	m_angleY = 0;
	m_ViewingAngle = 60;
	m_pos = { 0,0,-10.0f };
	m_camera = std::make_unique<KdCamera>();        //メモリ確保
	m_camera->SetProjectionMatrix(m_ViewingAngle);  //視野角設定
	//===========================================================================================================================

	std::shared_ptr<ResultPlayer>player = std::make_shared<ResultPlayer>();
	player->SetGameOver(m_gameOverFlg);
	m_objList.push_back(player);

	std::shared_ptr<BackGround>back = std::make_shared<BackGround>();
	std::shared_ptr<KdSquarePolygon> backPolygon = std::make_shared<KdSquarePolygon>();
	backPolygon->SetMaterial("Asset/Textures/BackGround/BackGround.png");
	back->SetPolygon(backPolygon);
	back->SetPos(Math::Vector3{ 0.0f,0.0f,100.0f });
	back->SetAngle(0.0f, 0.0f);
	m_objList.push_back(back);

	if (!m_gameOverFlg)
	{
		//ゴール位置=================================================================================================================
		std::shared_ptr<Goal>goal = std::make_shared<Goal>();
		goal->SetPos(Math::Vector3{ 0.0f,-25.0f,30.0f });
		goal->SetAngle(90.0f);
		m_objList.push_back(goal);
		//===========================================================================================================================
	}
}
