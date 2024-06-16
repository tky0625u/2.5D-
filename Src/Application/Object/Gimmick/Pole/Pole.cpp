#include "Pole.h"

void Pole::Update()
{
	//回転==============================================================================================
	m_angleX += m_rotationX;                    //角度増加
	if (m_angleX >= 360.0f)m_angleX -= 360.0f;  //360度を越えたら
	//==================================================================================================

	//行列更新==========================================================================================
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);                                    //拡縮
	Math::Matrix RotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_angleX));  //回転　X軸
	Math::Matrix RotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angleY));  //回転　Y軸
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);                               //座標
	m_mWorld = Scale * RotX * RotY * Trans;                                                    //行列合成
	//==================================================================================================
}

void Pole::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Pole/Pole.gltf");
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Pole", m_model, KdCollider::Type::TypeBump|KdCollider::TypeGround);
	m_pos = { 40,0.0f,0.0f };
	m_size = 2.0f;
	m_angleX = 0.0f;
	m_angleY = 0.0f;
	m_rotationX = ROTATION_X;
	m_bound = 0.0f;
}

void Pole::Rotation(int i)
{
	if ((i + 1) % 2 == 0)m_rotationX *= -1;
}

void Pole::SetPos(int i)
{
	m_pos.x += POLEDISTANS * i;
}
