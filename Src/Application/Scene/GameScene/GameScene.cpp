#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/BackGround/BackGround.h"
#include"../../Object/Ground/Start/StartBlock.h"
#include"../../Object/Ground/Bridge/Bridge.h"
#include"../../Object/Ground/Goal/Goal.h"
#include"../../Object/Ground/Water/Water.h"
#include"../../Object/Ground/Ground/Ground.h"
#include"../../Object/Character/Player/Player.h"
#include"../../Object/UI/Timer/TimerManager.h"
#include"../../Object/UI/Goal/GoalUI.h"
#include"../../Object/UI/GameOver/GameOver.h"
#include"../../Object/UI/Start/StartUI.h"
#include"../../Object/Gimmick/GimmickManager/GimmickManager.h"

#include<fstream>
#include<sstream>

void GameScene::PreUpdate()
{

	if (m_player.expired() == false)
	{
		if (m_player.lock()->GetGoal() == false && m_player.lock()->GetGameOver()==false)BaseScene::PreUpdate();
	}
}

void GameScene::Update()
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
	else if(m_player.lock()->GetGoal()){ m_goalUI->Update(); }
	else if (m_player.lock()->GetGameOver()) { m_gameOverlUI->Update(); }

	Event();
}

void GameScene::PostUpdate()
{
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

	ShowCursor(false);
}

void GameScene::Init()
{
	//カメラ　生成＆視野角設定===================================================================================================
	m_angleX = 20;
	m_angleY = 270;
	m_ViewingAngle = 60;
	m_ViewFlg = false;
	m_pos = { 600,100,0 };
	m_camera = std::make_unique<KdCamera>();        //メモリ確保
	m_camera->SetProjectionMatrix(m_ViewingAngle);  //視野角設定
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
	m_objList.push_back(goal);
	//===========================================================================================================================

	//水=========================================================================================================================
	static const int WaterNUM = 3;
	std::shared_ptr<Water>water[WaterNUM];
	for (int i = 0; i < WaterNUM; ++i)water[i] = std::make_shared<Water>();
	water[0]->SetPos(Math::Vector3{ -250.0f,-20.0f,0.0f });
	water[1]->SetPos(Math::Vector3{ 210.0f,-19.0f,0.0f });
	water[2]->SetPos(Math::Vector3{ 670.0f,-20.0f,0.0f });
	for (int i = 0; i < WaterNUM; ++i)m_objList.push_back(water[i]);
	//===========================================================================================================================

	//地面=======================================================================================================================
	static const int GroundNUM = 1;
	std::shared_ptr<Ground>ground[GroundNUM];
	for (int i = 0; i < GroundNUM; ++i)ground[i] = std::make_shared<Ground>();
	ground[0]->SetPos(Math::Vector3{ 250.0f,-10.0f,300.0f });
	//ground[1]->SetPos(Math::Vector3{ 210.0f,-19.0f,0.0f });
	//ground[2]->SetPos(Math::Vector3{ 670.0f,-20.0f,0.0f });
	for (int i = 0; i < GroundNUM; ++i)m_objList.push_back(ground[i]);
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
	static const int BackNUM = 5;
	std::shared_ptr<BackGround>back[BackNUM]; 
	for (int i = 0; i < BackNUM; ++i)
	{
		back[i] = std::make_shared<BackGround>();

		std::shared_ptr<KdSquarePolygon> backPolygon = std::make_shared<KdSquarePolygon>();
		backPolygon->SetMaterial("Asset/Textures/BackGround/BackGround.png");
		back[i]->SetPolygon(backPolygon);

	}
	back[0]->SetPos(Math::Vector3{200.0f,100.0f,0.0f});
	back[0]->SetAngle(90.0f, 90.0f);

	back[1]->SetPos(Math::Vector3{ 600.0f,0.0f,0.0f });
	back[1]->SetAngle(0.0f, 90.0f);
	
	back[2]->SetPos(Math::Vector3{ -250.0f,100.0f,0.0f });
	back[2]->SetAngle(0.0f, 90.0f);
	
	back[3]->SetPos(Math::Vector3{ 200.0f,0.0f,300.0f });
	back[3]->SetAngle(0.0f, 0.0f);
	
	back[4]->SetPos(Math::Vector3{ 200.0f,0.0f, -300.0f });
	back[4]->SetAngle(0.0f, 0.0f);

	for (int i = 0; i < BackNUM; ++i)m_objList.push_back(back[i]);
	//===========================================================================================================================

	//フェードイン===============================================================================================================
	m_brackAlpha = 1.0f;
	m_brackPos = {};
	m_brackColor = { 0.0f,0.0f,0.0f,m_brackAlpha };
	m_fedeinFlg = false;
	//===========================================================================================================================
}
