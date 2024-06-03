#include "Player.h"
#include"../../../WindowUI/WindowUI.h"

void Player::Update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)m_pos.x -= 0.3f;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)m_pos.x += 0.3f;
	
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!m_jumpFlg)
		{
			m_gravity += 1.0f;
			m_jumpFlg = true;
		}
	}

	m_gravity -= 0.05f;
	m_pos += m_move;
	m_pos.y += m_gravity;

	if (m_pos.y <= 0)
	{
		m_pos.y = 0;
		m_gravity = 0;
		m_jumpFlg = false;
	}

	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Rot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Rot * Trans;
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
	m_move = { 0,0,0 };
	m_dir = Math::Vector3::Zero;
	m_size = 1.0f;
	m_angle = 0.0f;
	m_gravity = 0.005f;
	m_jumpFlg = false;
}
