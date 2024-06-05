#include "Ground.h"

void Ground::Update()
{
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Trans;
}

void Ground::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model,m_mWorld);  //モデル描画
}

void Ground::Init()
{
	m_pos = { -35,-4,0 };
	m_model = std::make_shared<KdModelData>();          //メモリ確保
	m_model->Load("Asset/Models/Ground/Start.gltf");  //モデル読み込み
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Start", m_model, KdCollider::Type::TypeGround);
}
