#include "Wall.h"

void Wall::Update()
{
	m_angle--;
	if (m_angle < -360.0f)m_angle += 360.0f;

	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Rot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Rot * Trans;
}

void Wall::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Rotate/Wall/Wall.gltf");
	m_pos = {};
	m_size = 6.0f;
	m_angle = 0.0f;
	m_bound = 0.0f;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Wall", m_model, KdCollider::TypeBump);
}
