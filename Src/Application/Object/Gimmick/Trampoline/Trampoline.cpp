#include "Trampoline.h"

void Trampoline::Update()
{
	m_pos.z += m_move.z;
	if (m_pos.z >= m_reverse || m_pos.z <= (m_reverse) * -1.0f)
	{
		m_move.z *= -1.0f;
	}

	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Trans;
}

void Trampoline::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Trampoline/Trampoline.gltf");
	m_pos = { 420.0f,2.0f,0.0f };
	m_move = { 0.0f,0.0f,0.5f };
	m_size = 2.0f;
	m_bound = 2.0f;
	m_reverse = 30.0f;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Trampoline", m_model, KdCollider::TypeGround);
}
