#include "Circle.h"

void Circle::PreUpdate()
{
	if (m_size <= 0.0f)m_isExpired = true;  //サイズが０で消滅
}

void Circle::Update()
{
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix RotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_angleX));
	Math::Matrix RotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angleY));
	Math::Matrix RotZ = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_angleZ));
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * RotX * RotZ * RotY * Trans;
}

void Circle::Draw()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Circle::DrawLit()
{
	Draw();
}

void Circle::DrawBright()
{
	Draw();
}

void Circle::Init()
{
	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Effect/magic circle red.png");
	m_pos = {};
	m_angleX = 0.0f;
	m_angleY = 0.0f;
	m_angleZ = 0.0f;
	m_size = 0.0f;
	m_SizeMAX = 0.0f;
}

void Circle::RotationY()
{
	m_angleY++;  //回転
	if (m_angleY >= 360.0f)m_angleY -= 360.0f;
}

void Circle::RotationZ()
{
	m_angleZ++;
	if (m_angleZ >= 360.0f)m_angleZ -= 360.0f;
}
