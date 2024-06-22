#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/BackGround/BackGround.h"
#include"../../Object/Ground/Start/StartBlock.h"
#include"../../Object/Ground/Bridge/Bridge.h"
#include"../../Object/Ground/Goal/Goal.h"
#include"../../Object/Character/Player/Player.h"
#include"../../Object/UI/Timer/TimerManager.h"
#include"../../Object/UI/Goal/GoalUI.h"
#include"../../Object/UI/GameOver/GameOver.h"
#include"../../Object/UI/Start/StartUI.h"
#include"../../Object/Gimmick/GimmickManager/GimmickManager.h"
#include"../../Object/Cloud/Cloud.h"
#include"../../Object//BigCloud/BigCloud.h"
#include"../../Object/UI/Cuesor/Cursor.h"

#include<fstream>
#include<sstream>

void GameScene::PreUpdate()
{
	if (m_menuFlg)return;

	if (m_player.expired() == false)
	{
		if (m_player.lock()->GetGoal() == false && m_player.lock()->GetGameOver()==false)BaseScene::PreUpdate();
	}
}

void GameScene::Update()
{
	if (GetAsyncKeyState(VK_TAB) & 0x8000)
	{
		if (!m_keyFlg)
		{
			if (!m_menuFlg)
			{
				m_menuFlg = true;
				KdAudioManager::Instance().PauseAllSound();
				m_cursor->FlgChange(true);
				
			}
			else 
			{
				m_menuFlg = false;
				KdAudioManager::Instance().ResumeAllSound();
				
				SetCursorPos(640, 360);
				m_cursor->FlgChange(false);
			}

			m_keyFlg = true;
		}
	}
	else
	{
		m_keyFlg = false;
	}


	if (!m_menuFlg)
	{
		if (!m_fedeinFlg && m_brackAlpha > 0.0f)
		{
			m_brackAlpha -= 0.01f;
		}
		else if (m_fedeinFlg)
		{
			m_brackAlpha += 0.01f;
		}

		m_brackColor = { 0.0f,0.0f,0.0f,m_brackAlpha };

		if (m_player.lock()->GetGoal() == false && m_player.lock()->GetGameOver() == false)
		{
			for (auto& obj : m_objList)
			{
				obj->Update();
			}
		}
		else if (m_player.lock()->GetGoal()) { m_goalUI->Update(); }
		else if (m_player.lock()->GetGameOver()) { m_gameOverlUI->Update(); }

		Event();
	}
	else
	{
		m_cursor->Update();
	}
}

void GameScene::PostUpdate()
{
	m_cursor->PostUpdate();

	if (m_menuFlg)return;

	if (m_player.expired() == false)
	{
		if (m_player.lock()->GetGoal() == false && m_player.lock()->GetGameOver() == false)BaseScene::PostUpdate();
	}
}

void GameScene::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.Begin();
	{
		for (auto& obj : m_objList)
		{
			obj->DrawSprite();
		}

		if (m_player.expired() == false)
		{
			if (m_player.lock()->GetGoal())m_goalUI->DrawSprite();
			else if (m_player.lock()->GetGameOver())m_gameOverlUI->DrawSprite();
		}

		KdShaderManager::Instance().m_spriteShader.DrawBox((int)m_brackPos.x, (int)m_brackPos.y, 640, 360, &m_brackColor, true);

		m_cursor->DrawSprite();
	}
	KdShaderManager::Instance().m_spriteShader.End();
}

void GameScene::Write(std::string a_filePath)
{
	std::ofstream ost(a_filePath);

	if (ost.is_open())
	{
		//ゲームオーバーだった場合
		if (m_player.lock()->GetGameOver())
		{
			ost << "Second" << "\n" << 0 << "\n" << "GameOver" << "\n" << m_player.lock()->GetGameOver();
		}
		//ゴールした場合
		else if(m_player.lock()->GetGoal())ost << "Second" << "\n" << m_timer.lock()->GetSecond() << "\n" << "GameOver" << "\n" << m_player.lock()->GetGameOver();

		ost.close();
	}
}

void GameScene::Event()
{
	static float playerAngleX = 0;
	static float playerAngleY = 0;
	static Math::Vector3 playerPos = {};

	if (m_player.expired() == false)
	{
		if ( (m_player.lock()->GetGameOver() && m_gameOverlUI->GetFinish()) || (m_player.lock()->GetGoal() && m_goalUI->GetFinish()))
		{
			KdAudioManager::Instance().StopAllSound();

			if (m_timer.expired() == false)
			{
				Write("ResultTime/ResultTime.csv");
			}
			if(GetAsyncKeyState(VK_SPACE) & 0x8000)m_fedeinFlg = true;

			if (m_brackAlpha >= 1.0f)SceneManager::Instance().SetNextScene(SceneManager::SceneType::Result);
		}

		if (m_startUI.expired() == false)
		{
			if (m_ViewFlg)m_startUI.lock()->CountON();

			if (m_startUI.lock()->GetStart())
			{
				m_player.lock()->ActionON();
				if (m_timer.expired() == false)
				{
					m_timer.lock()->StartON();
				}
				if (!m_bgmFlg)
				{
					KdAudioManager::Instance().Play("Asset/Sounds/BGM/maou_bgm_ethnic31.WAV", 0.1f, true);
					m_bgmFlg = true;
				}
			}
		}

	//プレイヤー情報取得===================================
		playerPos = m_player.lock()->GetPos();
		playerAngleX = m_player.lock()->GetAngleX();
		if (playerAngleX >= 80)playerAngleX = 80;
		if (playerAngleX <= -90)playerAngleX = -90;

		playerAngleY = m_player.lock()->GetAngleY();
	}
	//=====================================================

	if (!m_gimmick.expired())
	{
		//プレイヤー
		//弾リスト格納==========================================
		if (!m_player.expired())
		{
			m_player.lock()->SetBulletList(m_gimmick.lock()->GetBulletList());
		}
		//======================================================
	}

	//カメラ　更新===============================================================================================================

	if (!m_ViewFlg)
	{
		static std::shared_ptr<KdSoundInstance> seInstans;
		if (!m_seFlg)
		{
			seInstans = KdAudioManager::Instance().Play("Asset/Sounds/SE/Camera/maou_se_magic_wind01.WAV", 0.1f, true);
			m_seFlg = true;
		}

		Math::Vector3 cameraMove;
		cameraMove.x = playerPos.x - m_pos.x;
		cameraMove.y = (playerPos.y + 2.0f) - m_pos.y;

		if (fabs(cameraMove.x)>0.1f&&fabs(cameraMove.y)>0.1f)
		{
			cameraMove.Normalize();
			m_pos += 2.0 * cameraMove;
			if (m_pos.x < playerPos.x)m_pos.x = playerPos.x;
			if (m_pos.y < playerPos.y + 2.0f)m_pos.y = playerPos.y + 2.0f;
		}
		else
		{
			if (m_angleY > playerAngleY)m_angleY -= 2.0f;
			else { m_angleY = playerAngleY; }

			if (m_angleX > playerAngleX)m_angleX -= 2.0f;
			else { m_angleX = playerAngleX; }

			if (m_angleX == playerAngleX && m_angleY == playerAngleY)
			{
				m_pos = { 0.0f,2.0f,0.0f };
				m_angleX = playerAngleX;
				m_ViewFlg = true;
				seInstans->Stop();
			}
		}
	}

	//行列更新=================================================================================================================
	Math::Matrix RotX;
	Math::Matrix RotY;
	Math::Matrix Trans;
	Math::Matrix Mat;
	if (m_ViewFlg)
	{
		RotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(playerAngleX));  //角度
		RotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(playerAngleY));  //角度
		Trans = Math::Matrix::CreateTranslation(m_pos);                                   //座標 (プレイヤーの少し前)
		Math::Matrix PlayerTrans = Math::Matrix::CreateTranslation(playerPos);            //プレイヤー座標
		Mat = RotX * Trans * RotY * PlayerTrans;                                          //行列合成
	}
	else
	{
		RotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_angleX));  //角度
		RotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angleY));  //角度
		Trans = Math::Matrix::CreateTranslation(m_pos);                               //座標 (プレイヤーの少し前)
		Mat = RotX * RotY * Trans;                                                    //行列合成
	}

 	m_camera->SetCameraMatrix(Mat);                                                   //行列セット
	//=========================================================================================================================

	//===========================================================================================================================

	SetCursorPos(640, 360);
}

void GameScene::Init()
{
	srand(timeGetTime());

	//カメラ　生成＆視野角設定===================================================================================================
	m_angleX = 20;
	m_angleY = 270;
	m_ViewingAngle = 60;
	m_ViewFlg = false;
	m_seFlg = false;
	m_pos = { 600,100,0 };
	m_camera = std::make_unique<KdCamera>();        //メモリ確保
	m_camera->SetProjectionMatrix(m_ViewingAngle);  //視野角設定
	KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, true);
	KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 1.0f,1.0f,1.0f }, -15.0f, -50.0f, 0);
	//===========================================================================================================================

	//ギミック===================================================================================================================
	std::shared_ptr<GimmickManager>gimmick = std::make_shared<GimmickManager>();  //メモリ確保
	m_objList.push_back(gimmick);                                                 //リストに追加
	m_gimmick = gimmick;                                                          //ギミック変数に格納
	//===========================================================================================================================

	//プレイヤー=================================================================================================================
	std::shared_ptr<Player>player = std::make_shared<Player>();  //メモリ確保
	player->SetGimmickList(gimmick->GetGimmickList());           //ギミックリストを格納
	m_player = player;                                           //プレイヤー変数に格納
	m_objList.push_back(player);                                 //リストに追加
	//===========================================================================================================================

	//スタート位置===============================================================================================================
	std::shared_ptr<StartBlock>start = std::make_shared<StartBlock>();  //メモリ確保
	m_objList.push_back(start);                                         //リストに追加
	//===========================================================================================================================

	//橋=========================================================================================================================
	std::shared_ptr<Bridge>bridge = std::make_shared<Bridge>();  //メモリ確保
	m_objList.push_back(bridge);                                 //リストに追加
	//===========================================================================================================================

	//ゴール位置=================================================================================================================
	std::shared_ptr<Goal>goal = std::make_shared<Goal>();
	goal->SetPos(Math::Vector3{ 565.0f,30.0f,0.0f });
	m_objList.push_back(goal);
	//===========================================================================================================================

	//タイマー===================================================================================================================
	std::shared_ptr<TimerManager>timer = std::make_shared<TimerManager>();  //メモリ確保
	timer->SetSize(1.5f);
	timer->Init();
	m_objList.push_back(timer);                                             //リストに追加
	m_timer = timer;
	//===========================================================================================================================

	//ゴール表記=================================================================================================================
	std::shared_ptr<GoalUI>goalUI = std::make_shared<GoalUI>();
	m_goalUI = goalUI;
	//===========================================================================================================================

	//ゲームオーバー表記=========================================================================================================
	std::shared_ptr<GameOverUI>gameOverUI = std::make_shared<GameOverUI>();
	m_gameOverlUI = gameOverUI;
	//===========================================================================================================================

	//スタート表記===============================================================================================================
	std::shared_ptr<StartUI>startUI = std::make_shared<StartUI>();
	m_objList.push_back(startUI);
	m_startUI = startUI;
	//===========================================================================================================================

	//背景=======================================================================================================================
	static const int BackNUM = 6;
	std::shared_ptr<BackGround>back[BackNUM]; 
	for (int i = 0; i < BackNUM; ++i)
	{
		back[i] = std::make_shared<BackGround>();

		std::shared_ptr<KdSquarePolygon> backPolygon = std::make_shared<KdSquarePolygon>();
		backPolygon->SetMaterial("Asset/Textures/BackGround/BackGround.png");
		back[i]->SetPolygon(backPolygon);

	}
	back[0]->SetPos(Math::Vector3{200.0f,200.0f,0.0f});
	back[0]->SetAngle(90.0f, 90.0f);

	back[1]->SetPos(Math::Vector3{ 600.0f,0.0f,0.0f });
	back[1]->SetAngle(0.0f, 90.0f);
	
	back[2]->SetPos(Math::Vector3{ -250.0f,100.0f,0.0f });
	back[2]->SetAngle(0.0f, 90.0f);
	
	back[3]->SetPos(Math::Vector3{ 200.0f,0.0f,300.0f });
	back[3]->SetAngle(0.0f, 0.0f);
	
	back[4]->SetPos(Math::Vector3{ 200.0f,0.0f, -300.0f });
	back[4]->SetAngle(0.0f, 0.0f);

	back[5]->SetPos(Math::Vector3{ 200.0f,-100.0f,0.0f });
	back[5]->SetAngle(90.0f, 90.0f);

	for (int i = 0; i < BackNUM; ++i)m_objList.push_back(back[i]);
	//===========================================================================================================================

	//雲=========================================================================================================================
	static const int CloudNum = 30;
	for (int i = 0; i < CloudNum; ++i)
	{
		std::shared_ptr<Cloud>cloud = std::make_shared<Cloud>();
		if(i>=15)cloud->SetPos(Math::Vector3{ float(rand() % 850 - 250), float(rand() % 10 + 50 ) ,float(rand() % 601 - 300) });
		else{ cloud->SetPos(Math::Vector3{ float(rand() % 850 - 250), float(rand() % 10 - 12) ,float(rand() % 601 - 300) }); }
		cloud->SetMove(Math::Vector3{ float(rand() % 4 + 5) * 0.1f,0.0f,0.0f });
		cloud->SetSize(5.0f);
		m_objList.push_back(cloud);
	}
	//===========================================================================================================================

	//大きい雲===================================================================================================================
	std::shared_ptr<BigCloud>big = std::make_shared<BigCloud>();
	m_objList.push_back(big);
	//===========================================================================================================================

	//フェードイン===============================================================================================================
	m_brackAlpha = 1.0f;
	m_brackPos = {};
	m_brackColor = { 0.0f,0.0f,0.0f,m_brackAlpha };
	m_fedeinFlg = false;
	//===========================================================================================================================

	//カーソル===================================================================================================================
	m_cursor = std::make_unique<Cursor>();
	m_cursor->FlgChange(false);
	//===========================================================================================================================

	m_bgmFlg = false;
	m_menuFlg = false;
	m_keyFlg = false;
}
