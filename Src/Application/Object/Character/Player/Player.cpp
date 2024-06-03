#include "Player.h"
#include"../../../WindowUI/WindowUI.h"

void Player::Update()
{
	//行動=========================================================================================
	
	//移動===========================================================
	m_move.x = 0;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)m_move.x = -SPEED;   //左  ※移動変数に速さを代入
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)m_move.x = SPEED;   //右
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

	m_move.y -= m_gravity;  //重力を与える
	m_pos += m_move;

	if (m_pos.y <= 0)  //地面についたら落ちないようにする
	{
		m_pos.y = 0;
		m_move.y = 0;
		m_jumpFlg = false;
	}
	//===============================================================

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
	m_polygon->SetMaterial("Asset/Textures/Character/Player/player.png");
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_pos = Math::Vector3::Zero;
	m_move = Math::Vector3::Zero;
	m_size = 3.0f;
	m_angle = 0.0f;
	m_gravity = 0.05f;
	m_jumpFlg = false;
}
