#include "Bullet.h"

void Bullet::Update()
{
	//座標更新=====================================================================================
	m_pos.x += sin(DirectX::XMConvertToRadians(m_angle)) * BULLET_SPEED;
	m_pos.z += cos(DirectX::XMConvertToRadians(m_angle)) * BULLET_SPEED;
	//=============================================================================================

	//行列更新=====================================================================================
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);       //拡縮
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);  //座標
	m_mWorld = Scale * Trans;                                     //ワールド行列合成
	//=============================================================================================
}

void Bullet::PostUpdate()
{
	if (m_pos.z <= -50.0f)m_isExpired = true;
}

void Bullet::Draw()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Bullet::DrawLit()
{
	Draw();
}

void Bullet::GenerateDepthMapFromLight()
{
	Draw();
}

void Bullet::Init()
{
	m_objType = ObjType::Gimmick;
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Cannon/Bullet/Bullet.gltf");
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Bullet", m_model, KdCollider::Type::TypeBump);
	m_pos = {};
	m_size = 1.0f;
	m_angle = 0.0f;
}
