#include "Trampoline.h"

void Trampoline::Update()
{
	m_angle += m_angleChange;
	if (m_angle > 360.0f)m_angle -= 360.0f;

	m_move.z = cos(DirectX::XMConvertToRadians(m_angle)) * m_speed;
	m_pos += m_move;

	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Trans;
}

void Trampoline::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Trampoline/Trampoline.gltf");
	m_pos = { 420.0f,2.0f,0.0f };
	m_move = { 0.0f,0.0f,0.0f };
	m_size = 2.0f;
	m_angle = 0.0f;
	m_angleChange = 0.8f;
	m_bound = 1.5f;
	m_speed = 0.1f;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Trampoline", m_model, KdCollider::TypeGround);
}
