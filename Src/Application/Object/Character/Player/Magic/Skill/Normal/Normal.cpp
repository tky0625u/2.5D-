#include "Normal.h"

void Normal::PreUpdate()
{
	//プレイヤーの向いている方向飛ばす=====================================
	m_pos.z += cos(DirectX::XMConvertToRadians(m_angle)) * NORMALSPEED;
	m_pos.x += sin(DirectX::XMConvertToRadians(m_angle)) * NORMALSPEED;
	//=====================================================================

	m_AliveTime++;
	if (m_AliveTime >= NORMALALIVE) { m_isExpired = true; }
}

void Normal::Update()
{
	Math::Matrix Scale = Math::Matrix::CreateScale(0.5f);
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Trans;
}

void Normal::Draw()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Normal::DrawBright()
{
	Draw();
}

void Normal::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_pos = {};
	m_Atk = 1;
	m_PlayerAtk = 0;
	m_AliveTime = 0;
}
