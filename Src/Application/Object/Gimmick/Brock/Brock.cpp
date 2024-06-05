#include "Brock.h"

void Brock::Update()
{
	Math::Matrix RotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = RotY * Trans;
}

void Brock::Draw()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);  //モデル描画
}

void Brock::DrawLit()
{
	Draw();
}

void Brock::GenerateDepthMapFromLight()
{
	Draw();
}

void Brock::Init()
{
	m_pos = { -20,-2,0 };
	m_angle = 90;
	m_model = std::make_shared<KdModelData>();          //メモリ確保
	m_model->Load("Asset/Models/Brock/Brock.gltf");  //モデル読み込み
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Brock", m_model, KdCollider::Type::TypeGround);
}
