#include "Brock.h"

void Brock::Update()
{
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix RotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * RotY * Trans;
}

void Brock::Init()
{
	m_objType = ObjType::Gimmick;
	m_pos = { -8,-5,-3 };
	m_angle = 90;
	m_size = 2.0f;
	m_bound = 0.0f;
	m_model = std::make_shared<KdModelData>();          //メモリ確保
	m_model->Load("Asset/Models/Brock/Brock.gltf");  //モデル読み込み
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Brock", m_model, KdCollider::Type::TypeGround);
}
