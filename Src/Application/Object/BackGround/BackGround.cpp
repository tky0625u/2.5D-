#include "BackGround.h"

void BackGround::Update()
{
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix RotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_angleX));
	Math::Matrix RotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angleY));
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * RotX * RotY * Trans;
}

void BackGround::DrawUnLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void BackGround::Init()
{
	m_pos = {};
	m_size = 900.0f;
	m_angleX = 0.0f;
	m_angleY = 0.0f;
}
