#include "Storm.h"

void Storm::Update()
{
	m_MoveAngle += 2.0f;
	if (m_MoveAngle > 360.0f)m_MoveAngle -= 360.0f;

	m_angle -= 10.0f;
	if (m_angle < -360.0f)m_angle += 360.0f;


	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Rot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	Math::Matrix MoveRot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_MoveAngle));
	Math::Matrix CircleTrans = Math::Matrix::CreateTranslation(m_CirclePos);
	m_mWorld = Scale * Rot * Trans * MoveRot * CircleTrans;
}

void Storm::Init()
{
	m_objType = ObjType::Gimmick;
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Rotate/Wall/Wall.gltf");
	m_pos = { 0.0f,0.0f,40.0f };
	m_move = { 0.6f,0.0f,0.6f };
	m_size = 10.0f;
	m_angle = 0.0f;
	m_MoveAngle = 0.0f;
	m_bound = 0.0f;

	m_CirclePos = {};

	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Strom", m_model, KdCollider::TypeBump);
}
