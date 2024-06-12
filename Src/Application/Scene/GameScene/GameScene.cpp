#include "GameScene.h"
#include"../SceneManager.h"
#include"../../Object/Ground/Start/StartBlock.h"
#include"../../Object/Ground/Bridge/Bridge.h"
#include"../../Object/Ground/Center/Center.h"
#include"../../Object/Ground/Road/Road.h"
#include"../../Object/Character/Player/Player.h"
#include"../../Object/UI/Timer/TimerManager.h"
#include"../../Object/Gimmick/GimmickManager/GimmickManager.h"

void GameScene::Event()
{

	//プレイヤー情報取得===================================
	static float playerAngleY = 0;
	static Math::Vector3 playerPos = {};
	if (m_player.expired() == false)
	{
		playerPos = m_player.lock()->GetPos();
	}
	//=====================================================

	if (!m_gimmick.expired())
	{
		//ギミック
		//カメラ情報取得========================================
		m_gimmick.lock()->SetCameraPos(m_pos + playerPos);
	    //======================================================

		//プレイヤー
		//弾リスト格納==========================================
		if (!m_player.expired())
		{
			m_player.lock()->SetBulletList(m_gimmick.lock()->GetBulletList());
		}
		//======================================================
	}

	//カメラ　更新===============================================================================================================

	//行列更新=================================================================================================================
	Math::Matrix RotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_angleX));      //角度
	Math::Matrix RotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angleY));  //角度
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);                                   //座標 (プレイヤーの少し前)
	Math::Matrix PlayerTrans = Math::Matrix::CreateTranslation(playerPos);                         //プレイヤー座標
	Math::Matrix Mat = RotX * Trans * RotY * PlayerTrans;                                          //行列合成
 	m_camera->SetCameraMatrix(Mat);                                                                //行列セット
	//=========================================================================================================================

	//===========================================================================================================================
}

void GameScene::Init()
{
	//カメラ　生成＆視野角設定===================================================================================================
	m_angleX = 20;
	m_angleY = 20;
	m_ViewingAngle = 60;
	m_pos = { 0,10,-15 };
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

	//中間地点===================================================================================================================
	//std::shared_ptr<CenterBlock>center = std::make_shared<CenterBlock>();  //メモリ確保
	//m_objList.push_back(center);                                           //リストに追加
	//===========================================================================================================================

	//一本道=====================================================================================================================
	std::shared_ptr<Road>road = std::make_shared<Road>();  //メモリ確保
	m_objList.push_back(road);                             //リストに追加
	//===========================================================================================================================

	//タイマー===================================================================================================================
	std::shared_ptr<TimerManager>timer = std::make_shared<TimerManager>();  //メモリ確保
	m_objList.push_back(timer);                                             //リストに追加
	//===========================================================================================================================
}
