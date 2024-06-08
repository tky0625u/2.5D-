#include "Player.h"
#include"../../../WindowUI/WindowUI.h"
#include"../../../Scene/SceneManager.h"
#include"../../Gimmick/GimmickManager/GimmickManager.h"

void Player::Update()
{
	//行動=========================================================================================

	//移動===========================================================
	m_dir = Math::Vector3::Zero;
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		m_dir.z = 1.0f;
	}
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		m_dir.z = -1.0f;
	}
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		m_dir.x = -1.0f;
		m_size.x = -3.0f;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_dir.x = 1.0f;
		m_size.x = 3.0f;
	}
	//===============================================================

	//ジャンプ=======================================================
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!m_jumpFlg)  //空中ジャンプ防止
		{
			m_move.y = JUMP;   //※移動変数にジャンプ力を代入
			m_jumpFlg = true;  
		}
	}
	//===============================================================
	
	//デバッグ用=====================================================
	if (GetAsyncKeyState('P') & 0x8000)
	{
		if (!m_keyFlg)
		{
			if (!m_air)
			{
				m_air = true;
				m_move.y = 0;
			}
			else { m_air = false; }
			m_keyFlg = true;
		}
	}
	else
	{
		m_keyFlg = false;
	}
	//===============================================================

	m_dir.Normalize();
	m_move.x = m_dir.x * SPEED;
	m_move.z = m_dir.z * SPEED;
	if(!m_air)m_move.y -= m_gravity;  //重力を与える
	m_pos += m_move;

	if (m_pos.y <= -50 || GetAsyncKeyState('R')&0x8000)ReStart();
	//=============================================================================================

	//アニメーション===============================================================================
	int Anime[][WALK_MAX] = { { 0,1,2,3 }, { 4,5,6,7,8,9,10 } };  //アニメーション配列

	//移動=======================================
	if (m_move.x != 0 || m_move.z != 0)
	{
		if (m_anime.m_motion != WALK)
		{
			m_anime.m_motion = WALK;
			m_anime.m_AnimeCnt = 0.0f;
			m_anime.m_CntMAX = WALK_MAX;
		}
	}
	//===========================================

	//立ち=======================================
	else if (!m_jumpFlg)
	{
		if (m_anime.m_motion != IDOL)
		{
			m_anime.m_motion = IDOL;
			m_anime.m_AnimeCnt = 0.0f;
			m_anime.m_CntMAX = IDOL_MAX;
		}
	}
	//===========================================

	m_anime.m_AnimeCnt += ANIME;  //アニメーション
	if (m_anime.m_AnimeCnt >= m_anime.m_CntMAX)m_anime.m_AnimeCnt = 0.0f;  //最大値になったら最初に戻す

	m_polygon->SetUVRect(Anime[m_anime.m_motion][(int)m_anime.m_AnimeCnt], 0);
	//=============================================================================================

	//行列更新=====================================================================================
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);                                  //拡縮 S
	Math::Matrix Rot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));  //回転 R
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);                             //座標 T
	m_mWorld = Scale * Rot * Trans;                                                          //行列合成
	//=============================================================================================
}

void Player::PostUpdate()
{
	//当たり判定===================================================================================



	//レイ判定=======================================================
	
	//レイ判定変数宣言=====================================
	KdCollider::RayInfo ray;                      //レイ判定用の変数作成
	ray.m_pos = m_pos;                            //レイのスタート地点
	ray.m_dir = Math::Vector3::Down;              //レイの方向
	ray.m_pos.y += 0.1f;                          //少し上から飛ばす
	float enableStepHight = 0.2f;                 //段差の許容範囲
	ray.m_pos.y += enableStepHight;               //許容範囲を加える
	ray.m_range = -(m_move.y) + enableStepHight;  //レイの長さ
	ray.m_type = KdCollider::Type::TypeGround;    //当たり判定したいタイプ

	//デバッグ表示
	Math::Color color = { 1,1,1,1 };
	m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range, color);
	//=====================================================

	//当たり判定===========================================
	std::list<KdCollider::CollisionResult> retRayList;                                        //当たったオブジェクトの情報を格納するリスト
	for (auto obj : SceneManager::Instance().GetObjList())obj->Intersects(ray, &retRayList);  //地面
	for (auto gimmick : m_GimmickList)gimmick->Intersects(ray, &retRayList);                  //ギミック
	//=====================================================

	//レイに当たったオブジェクトで一番近いものを検出=======
	float maxOverLap = 0;  //レイがはみ出た長さ
	Math::Vector3 hitPos;  //当たった座標
	bool isHit = false;    //当たり判定フラグ
	for (auto& ret : retRayList)
	{
		//はみ出た長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			//情報を上書き=======================
			maxOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			//===================================
			
			isHit = true;  //当たり判定フラグtrue
		}
	}
	//=====================================================

	//当たった時===========================================
	if (isHit)
	{
		m_pos = hitPos + Math::Vector3{ 0.0f,-0.1f,0.0f };  //座標更新
		m_move.y = 0.0f;                                    //落下速度をなくす
		m_jumpFlg = false;                                  //ジャンプフラグfalse
	}
	else
	{
		m_jumpFlg = true;
	}
	//=====================================================

	//===============================================================

		//球判定=========================================================
	KdCollider::SphereInfo sphere;                                              //球判定用の変数作成
	sphere.m_sphere.Center = { m_pos.x,m_pos.y + 1.5f,m_pos.z };                //球の中心
	sphere.m_sphere.Radius = 1.5f;                                              //球の半径
	sphere.m_type = KdCollider::Type::TypeBump;  //当たり判定したいタイプ

	//デバッグ用
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, color);

	std::list<KdCollider::CollisionResult> retSphereList;                           //当たったオブジェクトの情報を格納するリスト
	for (auto gimmick : m_GimmickList)gimmick->Intersects(sphere, &retSphereList);  //ギミック
	for (auto bullet : m_BulletList)bullet->Intersects(sphere, &retSphereList);     //弾

	//球に当たったもので一番近いものを検出=================
	maxOverLap = 0;
	Math::Vector3 hitDir;
	isHit = false;
	for (auto& ret : retSphereList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			isHit = true;
		}
	}
	//=====================================================

	if (isHit)
	{
		//hitDir.y = 0.0f;
		hitDir.Normalize();
		m_pos += hitDir * maxOverLap;
		m_move.y = 0.0f;
		m_jumpFlg = false;
	}
	//===============================================================

	//=============================================================================================
}

void Player::Draw()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Player::DrawLit()
{
	Draw();
}

void Player::GenerateDepthMapFromLight()
{
	Draw();
}

void Player::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Character/Player/sheets/DinoSprites - doux.png");
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_polygon->SetSplit(24, 1);
	m_pos = { -50,0,0 };
	m_move = Math::Vector3::Zero;
	m_dir = Math::Vector3::Zero;
	m_size = { 3.0f,3.0f,3.0f };
	m_angle = 0.0f;
	m_gravity = 0.05f;
	m_jumpFlg = false;

	//アニメーション
	m_anime.m_AnimeCnt = 0.0f;
	m_anime.m_CntMAX = IDOL_MAX;
	m_anime.m_motion = IDOL;

	//デバッグ用
	m_keyFlg = false;
	m_air = false;
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Player::ReStart()
{
	m_pos = { -50,0,0 };
}
