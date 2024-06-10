#include "Center.h"

void CenterBlock::Update()
{
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Trans;
}

void CenterBlock::Draw()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void CenterBlock::DrawLit()
{
	Draw();
}

void CenterBlock::GenerateDepthMapFromLight()
{
	Draw();
}

void CenterBlock::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Ground/Center/Center.gltf");
	m_pos = { 300.0f,0.0f,0.0f };
	m_size = 2.0f;

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Center", m_model, KdCollider::TypeGround);
}
