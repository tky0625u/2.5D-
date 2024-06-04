#include "Player.h"
#include"../../../WindowUI/WindowUI.h"

void Player::Update()
{
	//行動=========================================================================================
	
	int Anime[][7] = { { 0,1,2,3 }, { 4,5,6,7,8,9 } ,{ 10,11,12,13 } ,{ 17,18,19,20,21,22,23 } };
	static float a = 0.0f;
	static float b = 0.0f;
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
	if (m_move.x == 0.0f && m_move.y == 0.0f && m_move.z == 0.0f)
	{
		m_polygon->SetUVRect(Anime[0][(int)a], 0);
		a += ANIME;
		if (a >= 4)a = 0;
	}

	m_dir.Normalize();
	m_move.x = m_dir.x * SPEED;
	m_move.z = m_dir.z * SPEED;
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
	m_polygon->SetMaterial("Asset/Textures/Character/Player/sheets/DinoSprites - doux.png");
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_polygon->SetSplit(24, 1);
	m_pos = Math::Vector3::Zero;
	m_move = Math::Vector3::Zero;
	m_dir = Math::Vector3::Zero;
	m_size = { 3.0f,3.0f,3.0f };
	m_angle = 0.0f;
	m_gravity = 0.05f;
	m_jumpFlg = false;
}
