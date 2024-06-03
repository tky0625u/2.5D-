#include "EnemyBase.h"
#include"../../../WindowUI/WindowUI.h"

void EnemyBase::PreUpdate()
{
	//プレイヤーに近づく===============================================================================================
	if (!m_AtkFlg)
	{
		//プレイヤーとの距離===================================================
		float x = m_playerPos.x - m_pos.x;
		float z = m_playerPos.z - m_pos.z;
		//=====================================================================

		//進行方向からのプレイヤーの角度=======================================
		float angle = atan2(z, x);
		float angleDeg = angle * 180.0f / 3.14f;
		if (angleDeg < 0)angleDeg += 360.0f;
		m_angle = angleDeg;
		//=====================================================================

		//座標更新=============================================================
		m_pos.x += sin(DirectX::XMConvertToRadians(angleDeg)) * (status.Spd * SPDCORREC);
		m_pos.z += cos(DirectX::XMConvertToRadians(angleDeg)) * (status.Spd * SPDCORREC);
		//=====================================================================

		//距離計算=============================================================
		float dis = sqrt(x * x + z + z);
		if (dis <= m_AtkRange)m_AtkFlg = true;  //攻撃範囲内に入ったら攻撃フラグオン
		//=====================================================================
	}
	//=================================================================================================================
}

void EnemyBase::Update()
{
	//ワールド行列　合成===============================================================================================
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);       //大きさ
	Math::Matrix Rot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));    //回転
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);  //移動
	m_mWorld = Scale * Rot * Trans;                               //合成
	//=================================================================================================================
}

void EnemyBase::Draw()
{
	CharacterBase::Draw();
}

void EnemyBase::Init()
{
	type = CharaType(CharaType::Enemy);
	m_Atk = 0;
	m_size = 1.0f;
	m_angle = 0.0f;
	m_pos = Math::Vector3::Zero;
	m_move = Math::Vector3::Zero;
	m_playerPos = Math::Vector3::Zero;
	m_anime = 0;
	m_bFlg = true;
	m_AtkFlg = false;
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
}
