#include "Ult.h"
#include"../Circle/Circle.h"

void Ult::PreUpdate()
{
	if (m_size < SIZEMAX)
	{
		m_size += SIZEUP;  //サイズ増加
	}
	else
	{
		//プレイヤーの向いている方向飛ばす=====================================
		m_pos.z += cos(DirectX::XMConvertToRadians(m_angle)) * ULTSPEED;
		m_pos.x += sin(DirectX::XMConvertToRadians(m_angle)) * ULTSPEED;
		//=====================================================================
		m_AliveTime++;  //生存時間増加
	}
}

void Ult::Update()
{
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Trans;
	
}

void Ult::Draw()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Ult::DrawLit()
{
	Draw();
}

void Ult::DrawBright()
{
	Draw();
}

void Ult::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Player/Skill/Ult/Fire.gltf");
	m_pos = {};
	m_AliveTime = 0;
	m_Atk = 5;
	m_PlayerAtk = 0;
	m_size = 1.0f;
	m_angle = 0.0f;
}

void Ult::SetPos(Math::Vector3 a_pos)
{
	m_pos = a_pos;
}

void Ult::FlgOFF()
{
	m_isExpired = true;
}
