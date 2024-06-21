#include "ResultPlayer.h"
#include"../../../../WindowUI/WindowUI.h"
#include"../../../../Scene/SceneManager.h"

void ResultPlayer::Update()
{
	if (m_gameOverFlg)
	{
		m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Middle);
		m_polygon->SetUVRect(14, 0);

		static float angle = 0.1f;

		m_angleMove += 1.0f;
		if (m_angleMove > 360.0f)m_angleMove -= 360.0f;
		angle = sin(DirectX::XMConvertToRadians(m_angleMove)) * 0.1f;

		m_angleZ += angle;
	}
	else
	{
		//アニメーション===============================================================================
		int Anime[IDOL_MAX] = { 0,1,2,3 }; //アニメーション配列

		//立ち=======================================
		if (!m_jumpFlg)
		{
			m_anime.m_AnimeCnt = 0.0f;
			m_anime.m_CntMAX = IDOL_MAX;
		}
		//===========================================

		m_anime.m_AnimeCnt += ANIME;  //アニメーション
		if (m_anime.m_AnimeCnt >= m_anime.m_CntMAX)m_anime.m_AnimeCnt = 0.0f;  //最大値になったら最初に戻す

		m_polygon->SetUVRect(Anime[(int)m_anime.m_AnimeCnt], 0);
		//=============================================================================================

		m_move.y -= m_gravity;  //重力を与える
		m_pos.y += m_move.y;    //高さ

		if (m_angleZ != 0.0f)m_angleZ = 0.0f;
	}
	//行列更新=====================================================================================
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);                                  //拡縮 S
	Math::Matrix RotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angleY));  //回転 R
	Math::Matrix RotZ = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_angleZ));  //回転 R
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);                             //座標 T
	m_mWorld = Scale * RotY * RotZ * Trans;                                                  //行列合成
	//=============================================================================================
}

void ResultPlayer::PostUpdate()
{
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

	//地面=======================================
	std::list<KdCollider::CollisionResult> retRayGroundList;
	for (auto ground : SceneManager::Instance().GetObjList())
	{
		ground->Intersects(ray, &retRayGroundList);
	}
	//===========================================

	//=====================================================

	//レイに当たったオブジェクトで一番近いものを検出
	float maxOverLap = 0;  //レイがはみ出た長さ
	Math::Vector3 hitPos;  //当たった座標
	bool RayHit = false;    //当たり判定フラグ

	//地面=================================================
	for (auto& ret : retRayGroundList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			RayHit = true;
		}
	}
	//=====================================================

	if (RayHit)
	{
		m_pos = hitPos + Math::Vector3{ 0.0f,-0.1f,0.0f };  //座標更新
		m_move.y = 0.0f;
		m_jumpFlg = false;                                  //ジャンプフラグfalse
	}
	else
	{
		m_jumpFlg = true;
	}

	//===============================================================
}

void ResultPlayer::Draw()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void ResultPlayer::DrawLit()
{
	Draw();
}

void ResultPlayer::GenerateDepthMapFromLight()
{
	Draw();
}

void ResultPlayer::Init()
{
	m_objType = ObjType::Player;
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Character/Player/sheets/DinoSprites - doux.png");
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_polygon->SetSplit(24, 1);
	m_pos = { 0.0f,-7.5f,20.0f };
	m_size = { 5.0f,5.0f,5.0f };
	m_move = Math::Vector3::Zero;
	m_angleX = 0.0f;
	m_angleY = 0.0f;
	m_angleZ = 45.0f;
	m_angleMove = 0.0f;
	m_gravity = 0.05f;
	m_jumpFlg = false;
	m_gameOverFlg = false;

	//アニメーション
	m_anime.m_AnimeCnt = 0.0f;
	m_anime.m_CntMAX = IDOL_MAX;

	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}
