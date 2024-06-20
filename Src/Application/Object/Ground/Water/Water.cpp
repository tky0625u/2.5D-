#include "Water.h"

void Water::Update()
{
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Trans;
}

void Water::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Water::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Ground/Water/Water.gltf");
	m_pos = {};
	m_size = 5.0f;
}
