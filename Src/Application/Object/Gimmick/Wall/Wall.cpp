#include "Wall.h"

void Wall::Update()
{
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Rot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Rot * Trans;
}

void Wall::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Wall/Wall.gltf");
	m_pos = { 320.0f,-10.0f,0.0f };
	m_size = 3.0f;
	m_angle = 180.0f;
	m_bound = 0.0f;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Wall", m_model, KdCollider::TypeBump | KdCollider::TypeGround);
}
