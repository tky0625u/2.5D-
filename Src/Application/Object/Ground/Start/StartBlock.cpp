#include "StartBlock.h"

void StartBlock::Update()
{
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Trans;
}

void StartBlock::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);  //モデル描画
}

void StartBlock::Init()
{
	m_objType = ObjType::Start;
	m_pos = { -60,-18,0 };
	m_size = 5.0f;
	m_model = std::make_shared<KdModelData>();          //メモリ確保
	m_model->Load("Asset/Models/Ground/Start/Start.gltf");  //モデル読み込み
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Start", m_model, KdCollider::Type::TypeGround | KdCollider::TypeBump);
}
