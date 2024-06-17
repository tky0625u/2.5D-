#include "Circle.h"

void Circle::Update()
{
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Rot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Rot * Trans;
}

void Circle::Init()
{
	m_objType = ObjType::Gimmick;
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Rotate/Circle/Circle.gltf");
	m_pos = { 350.0f,0.0f,0.0f };
	m_size = 6.0f;
	m_angle = 0.0f;
	m_bound = 0.0f;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Circle", m_model, KdCollider::TypeGround);
}
