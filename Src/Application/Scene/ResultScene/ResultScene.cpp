#include "ResultScene.h"
#include"../SceneManager.h"
#include"../../WindowUI/WindowUI.h"
#include"../../Object/UI/Timer/TimerManager.h"
#include"../../Object/Character/Player/Result/ResultPlayer.h"
#include"../../Object/Ground/Goal/Goal.h"
#include"../../Object/BackGround/BackGround.h"
#include"../../Object/Cloud/Cloud.h"
#include"../../Object/UI/Cuesor/Cursor.h"
#include"../../Object/UI/Buttom/Exit/Exit.h"
#include"../../Object/UI/Best TIme/Best Time.h"
#include"../../Object/UI/Goal/GoalUI.h"
#include"../../Object/UI/GameOver/GameOver.h"

#include<fstream>
#include<sstream>

void ResultScene::Update()
{
	if (!m_fedeinFlg && m_whiteAlpha > 0.0f)
	{
		m_whiteAlpha -= 0.05f;
	}
	else if (m_fedeinFlg)
	{
		m_whiteAlpha += 0.01f;
	}
	m_whiteColor = { 1.0f,1.0f,1.0f,m_whiteAlpha };

	if (!m_gameOverFlg)
	{
		if (m_ramdomFlg)
		{
			m_timer->Random();
			if (!m_ramdomSoundFlg)
			{
				KdAudioManager::Instance().Play("Asset/Sounds/SE/Result/電子ルーレット回転中.WAV", 0.1f, false);
				m_ramdomSoundFlg = true;
			}
		}
	}

	for (auto& obj : m_objList)obj->Update();
	m_cursor->Update();
	for (auto& buttom : m_buttomList)buttom->Update();
	Event();

	m_frame++;
}

void ResultScene::PostUpdate()
{
	for (auto& obj : m_objList)obj->PostUpdate();
	m_cursor->PostUpdate();

	if (m_gameOverFlg)return;
		
	m_timer->PostUpdate();

	if (m_frame >= SECOND * 1)
	{
		if (m_ramdomSoundFlg && !m_StopSoundFlg)
		{
			KdAudioManager::Instance().StopAllSound();
			KdAudioManager::Instance().Play("Asset/Sounds/SE/Result/電子ルーレット停止ボタンを押す.WAV", 0.1f, false);
			KdAudioManager::Instance().Play("Asset/Sounds/SE/BestTime/ドンドンパフパフ.WAV", 0.2f, false);
			m_StopSoundFlg = true;
		}
		if (m_bestFlg)
		{
			if (!m_bestShowFlg)
			{
				m_bestShowFlg = true;
			}
		}
		m_ramdomFlg = false;
	}
}

void ResultScene::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.Begin();
	{
		for (auto& obj : m_objList)obj->DrawSprite();
		KdShaderManager::Instance().m_spriteShader.SetMatrix(Math::Matrix::Identity);

		if (!m_gameOverFlg)m_timer->DrawSprite();

		if(m_bestShowFlg)m_best->DrawSprite();

		for (auto& buttom : m_buttomList)buttom->DrawSprite();

		m_cursor->DrawSprite();

		KdShaderManager::Instance().m_spriteShader.DrawBox((int)m_whitePos.x, (int)m_whitePos.y, 640, 360, &m_whiteColor, true);
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

		if (Data == 0)return;

		m_timer = std::make_shared<TimerManager>();
		m_timer->SetPos(Math::Vector2{ 0,0 });
		m_timer->SetSize(2.0f);
		m_timer->Init();

		m_gameOverFlg = false;

		for (int i = 0; i < Data; i++)
		{
			m_timer->Scroll();
		}

		BestWrite("ResultTime/BestTime.csv", Data);
	
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
			m_bestFlg = true;
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
	if (!m_bgmFlg && m_frame > SECOND * 4)
	{
		if (!m_gameOverFlg)
		{
			KdAudioManager::Instance().Play("Asset/Sounds/BGM/Goal/Springin_News_おたよりコーナー.WAV", 0.1f, true);
		}
		else
		{
			KdAudioManager::Instance().Play("Asset/Sounds/BGM/GameOver/081_BPM118.WAV", 0.1f, true);
		}
		m_bgmFlg = true;
	}

	bool flg = m_exit.expired();
	if (m_exit.expired() == false)
	{
		bool Flg = m_exit.lock()->GetPush();
		if (Flg)
		{
			m_fedeinFlg = true;
		}
	}

	if (m_fedeinFlg && m_whiteAlpha >= 1.0f)
	{
		KdAudioManager::Instance().StopAllSound();
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Title
		);
	}

	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix Mat = Trans;
	m_camera->SetCameraMatrix(Mat);
}

void ResultScene::Init()
{
	srand(timeGetTime());

	//Exit=======================================================================================================================
	std::shared_ptr<Exit> exit = std::make_shared<Exit>();
	m_buttomList.push_back(exit);
	m_exit = exit;
	//===========================================================================================================================

	//カーソル===================================================================================================================
	m_cursor = std::make_unique<Cursor>();
	m_cursor->FlgChange(true);
	m_cursor->SetButtom(m_buttomList);
	//===========================================================================================================================

	//ベストスコア===============================================================================================================
	m_best = std::make_shared<BestTime>();
	m_best->SetPos(Math::Vector2{ 0.0f,20 });
	m_best->SetSize(1.0f);
	//===========================================================================================================================

	//フェードイン===============================================================================================================
	m_whiteAlpha = 1.0f;
	m_whitePos = {};
	m_whiteColor = { 1.0f,1.0f,1.0f,m_whiteAlpha };
	m_fedeinFlg = false;
	//===========================================================================================================================

	m_ResultTime = 0;
	m_frame = 0;
	m_ramdomFlg = true;
	m_ramdomSoundFlg = false;
	m_StopSoundFlg = false;
	m_bestFlg = false;
	m_bestShowFlg = false;
	m_gameOverFlg = true;
	m_bgmFlg = false;
	Load("ResultTime/ResultTime.csv");
	ShowCursor(true);

	//カメラ　生成＆視野角設定===================================================================================================
	m_angleX = 0;
	m_angleY = 0;
	m_ViewingAngle = 60;
	m_pos = { 0.0f,0,-5.0f };
	m_camera = std::make_unique<KdCamera>();        //メモリ確保
	m_camera->SetProjectionMatrix(m_ViewingAngle);  //視野角設定
	
	if (!m_gameOverFlg)
	{
		KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, true);
		KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 1.0f,1.0f,1.0f }, -5.0f, -10.0f, 0);
	}
	else
	{
		KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, false);
	}

	//===========================================================================================================================

	//プレイヤー=================================================================================================================
	std::shared_ptr<ResultPlayer>player = std::make_shared<ResultPlayer>();
	player->SetGameOver(m_gameOverFlg);
	if (m_gameOverFlg)player->SetAngleZ(45);
	else { player->SetAngleZ(0); }
	m_objList.push_back(player);
	//===========================================================================================================================

	//背景=======================================================================================================================
	std::shared_ptr<BackGround>back = std::make_shared<BackGround>();
	std::shared_ptr<KdSquarePolygon> backPolygon = std::make_shared<KdSquarePolygon>();
	backPolygon->SetMaterial("Asset/Textures/BackGround/BackGround.png");
	back->SetPolygon(backPolygon);
	back->SetPos(Math::Vector3{ 0.0f,0.0f,100.0f });
	back->SetAngle(0.0f, 0.0f);
	m_objList.push_back(back);
	//===========================================================================================================================

	static const int CloudNum = 3;

	if (!m_gameOverFlg)
	{
		//ゴール位置=================================================================================================================
		std::shared_ptr<Goal>goal = std::make_shared<Goal>();
		goal->SetPos(Math::Vector3{ 0.0f,-25.0f,30.0f });
		goal->SetAngle(90.0f);
		m_objList.push_back(goal);
		//===========================================================================================================================

		//ゴール表記=================================================================================================================
		std::shared_ptr<GoalUI>goalUI = std::make_shared<GoalUI>();
		m_objList.push_back(goalUI);
		//===========================================================================================================================
	}
	else
	{
		//雲=========================================================================================================================
		for (int i = 0; i < CloudNum; ++i)
		{
			std::shared_ptr<Cloud>cloud = std::make_shared<Cloud>();
			cloud->SetPos(Math::Vector3{ float(rand() % 60 - 30),float(rand() % 10 - 30),30.0f });
			cloud->SetMove(Math::Vector3{ 0.0f, float(rand() % 4 + 5) * 0.1f,0.0f });
			cloud->SetSize(1.0f);
			m_objList.push_back(cloud);
		}
		//===========================================================================================================================

		//ゲームオーバー表記=========================================================================================================
		std::shared_ptr<GameOverUI>gameOverUI = std::make_shared<GameOverUI>();
		m_objList.push_back(gameOverUI);
		//===========================================================================================================================

		KdAudioManager::Instance().Play("Asset/Sounds/SE/GameOver/呪いの旋律.WAV", 0.1f, false);
	}
}
