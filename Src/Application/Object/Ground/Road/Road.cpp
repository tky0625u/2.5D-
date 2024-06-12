#include "Road.h"

void Road::Update()
{
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Trans;
}

void Road::Draw()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Road::DrawLit()
{
	Draw();
}

void Road::GenerateDepthMapFromLight()
{
	Draw();
}

void Road::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Ground/Road/Road.gltf");
	m_pos = { 380.0f,3.0f,0.0f };
	m_size = 5.0f;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Road", m_model, KdCollider::TypeGround);
}
