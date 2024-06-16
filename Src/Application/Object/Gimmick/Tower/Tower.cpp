#include "Tower.h"

void Tower::Update()
{
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Rot = Math::Matrix::CreateRotationY(m_angle);
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Rot * Trans;
}

void Tower::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Tower/Tower.gltf");
	m_pos = { 510.0f,-5.0f,0.0f };
	m_size = 1.0f;
	m_angle = 0.0f;
	m_bound = 0.0f;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Tower", m_model, KdCollider::TypeGround | KdCollider::TypeBump);
}
