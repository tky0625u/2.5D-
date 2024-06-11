#include "Trampoline.h"

void Trampoline::Update()
{
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Trans;
}

void Trampoline::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Trampoline/Trampoline.gltf");
	m_pos = { 320.0f,-5.0f,0.0f };
	m_size = 1.0f;
	m_bound = 2.0f;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Trampoline", m_model, KdCollider::TypeGround);
}
