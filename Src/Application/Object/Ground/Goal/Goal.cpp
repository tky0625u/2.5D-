#include "Goal.h"

void Goal::Update()
{
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Rot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Rot * Trans;
}

void Goal::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);  //モデル描画
}

void Goal::Init()
{
	m_objType = ObjType::Goal;
	m_pos = {};
	m_size = 5.0f;
	m_angle = 180.0f;
	m_model = std::make_shared<KdModelData>();          //メモリ確保
	m_model->Load("Asset/Models/Ground/Goal/Goal.gltf");  //モデル読み込み
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Goal", m_model, KdCollider::Type::TypeGround | KdCollider::TypeBump);
}
