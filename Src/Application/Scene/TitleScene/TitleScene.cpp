#include "TitleScene.h"
#include "../SceneManager.h"
#include"../../Object/UI/Timer/TimerManager.h"
#include"../../Object/UI/Cuesor/Cursor.h"
#include"../../Object/UI/Best TIme/Best Time.h"
#include"../../Object/BackGround/BackGround.h"
#include"../../Object/Cloud/Cloud.h"
#include"../../Object//BigCloud/BigCloud.h"
#include"../../Object/UI/Title/TItle.h"
#include"../../Object/UI/Crick/Crick.h"

void TitleScene::Update()
{
	if (m_fedeinFlg)
	{
		m_brackAlpha += 0.01f;
	}

	m_brackColor = { 0.0f,0.0f,0.0f,m_brackAlpha };
	m_cursor->Update();

	for (auto& obj : m_objList)obj->Update();

	Event();
}

void TitleScene::PostUpdate()
{
	m_timer->PostUpdate();

	for (auto& obj : m_objList)obj->PostUpdate();
}

void TitleScene::DrawSprite()
{
	KdShaderManager::Instance().m_spriteShader.Begin();
	{
		for (auto& obj : m_objList)obj->DrawSprite();
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
		m_timer->SetPos(Math::Vector2{ 0,320 });
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
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		m_fedeinFlg = true;
	}

	if (m_brackAlpha >= 1.0f)
	{
		KdAudioManager::Instance().StopAllSound();
		SceneManager::Instance().SetNextScene
		(
			SceneManager::SceneType::Game
		);
	}

	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix Mat = Trans;
	m_camera->SetCameraMatrix(Mat);
}

void TitleScene::Init()
{
	//カメラ　生成＆視野角設定===================================================================================================
	m_angleX = 0;
	m_angleY = 0;
	m_ViewingAngle = 60;
	m_pos = { 150.0f,0,-150.0f };
	m_camera = std::make_unique<KdCamera>();        //メモリ確保
	m_camera->SetProjectionMatrix(m_ViewingAngle);  //視野角設定

	KdShaderManager::Instance().WorkAmbientController().SetFogEnable(false, true);
	KdShaderManager::Instance().WorkAmbientController().SetheightFog({ 1.0f,1.0f,1.0f }, -5.0f, -10.0f, 0);

	//===========================================================================================================================

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
	m_best->SetPos(Math::Vector2{ 0.0f,330.0f });
	m_best->SetSize(0.8f);
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
	back[0]->SetPos(Math::Vector3{ 200.0f,200.0f,0.0f });
	back[0]->SetAngle(90.0f, 90.0f);

	back[1]->SetPos(Math::Vector3{ 600.0f,0.0f,0.0f });
	back[1]->SetAngle(0.0f, 90.0f);

	back[2]->SetPos(Math::Vector3{ -250.0f,100.0f,0.0f });
	back[2]->SetAngle(0.0f, 90.0f);

	back[3]->SetPos(Math::Vector3{ 200.0f,0.0f,300.0f });
	back[3]->SetAngle(0.0f, 0.0f);

	back[4]->SetPos(Math::Vector3{ 200.0f,-100.0f,0.0f });
	back[4]->SetAngle(90.0f, 90.0f);

	for (int i = 0; i < BackNUM; ++i)m_objList.push_back(back[i]);
	//===========================================================================================================================

	//雲=========================================================================================================================
	static const int CloudNum = 30;
	for (int i = 0; i < CloudNum; ++i)
	{
		std::shared_ptr<Cloud>cloud = std::make_shared<Cloud>();
		cloud->SetPos(Math::Vector3{ float(rand() % 850 - 250), float(rand() % 10 + 50) ,float(rand() % 601 - 300) });
		cloud->SetMove(Math::Vector3{ float(rand() % 4 + 5) * 0.1f, 0.0f,0.0f });
		cloud->SetSize(1.0f);
		m_objList.push_back(cloud);
	}
	//===========================================================================================================================

	//大きい雲===================================================================================================================
	std::shared_ptr<BigCloud>big = std::make_shared<BigCloud>();
	m_objList.push_back(big);
	//===========================================================================================================================

	//タイトル===================================================================================================================
	std::shared_ptr<Title>title = std::make_shared<Title>();
	m_objList.push_back(title);
	//===========================================================================================================================

	//クリック===================================================================================================================
	std::shared_ptr<Crick>crick = std::make_shared<Crick>();
	m_objList.push_back(crick);
	//===========================================================================================================================

	KdAudioManager::Instance().Play("Asset/Sounds/BGM/Title/Short60_ゆったりDIY_02.WAV", 0.1f, true);

	Load("ResultTime/BestTime.csv");
	ShowCursor(true);
}
