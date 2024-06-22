#include "Cloud.h"

void Cloud::Update()
{
	if (m_pos.x > 700.0f)
	{
		int Random = rand() % 2;
		if(Random==0)m_pos = { -100.0f, float(rand() % 40 - 50) ,float(rand() % 601 - 300) };
		else if(Random==1)m_pos = { -100.0f, float(rand() % 10 + 50) ,float(rand() % 401 - 200) };

		m_move = Math::Vector3{ float(rand() % 4 + 5) * 0.1f,0.0f,0.0f };
	}

	if (m_pos.y > 60)
	{
		m_pos = { float(rand() % 60 - 30),float(rand() % 10 - 30),30.0f };
	}

	m_pos += m_move;
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);
	m_mWorld = Scale * Trans;
}

void Cloud::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Cloud::DrawBright()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Cloud::Init()
{
	srand(timeGetTime());
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Cloud/Cloud.gltf");
	m_pos = {};
	m_move = {};
	m_size = 1.0f;
}
