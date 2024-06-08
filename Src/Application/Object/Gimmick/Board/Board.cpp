#include "Board.h"

void Board::Update()
{	
	m_angle += 0.5f;
	if (m_angle > 360.0f)m_angle -= 360.0f;

	m_move.z = cos(DirectX::XMConvertToRadians(m_angle)) * m_speed;
	m_pos += m_move;
	
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Trans;
}

void Board::Init()
{
	m_pos = { 240,0,0 };
	m_move = { 0.0f,0.0f,0.0f };
	m_angle = 0;
	m_speed = 0.1f;
	m_size = 1.0f;
	m_model = std::make_shared<KdModelData>();          //メモリ確保
	m_model->Load("Asset/Models/Board/Board.gltf");  //モデル読み込み
	m_pCollider = std::make_unique<KdCollider>();
	m_pCollider->RegisterCollisionShape("Board", m_model, KdCollider::Type::TypeGround);
}

void Board::SetPos(int i)
{
	m_pos.x += BOARDDISTANS * i;
}

void Board::ChangeSpeed(int i)
{
	if ((i + 1) % 2 == 0)m_speed *= -1;
}
