#include"BigCloud.h"

void BigCloud::Update()
{
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Trans;
}

void BigCloud::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void BigCloud::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void BigCloud::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/BigCloud/BigCloud.gltf");
	m_pos = {175.0f,-80.0f,0.0f};
	m_size = 15.0f;
}