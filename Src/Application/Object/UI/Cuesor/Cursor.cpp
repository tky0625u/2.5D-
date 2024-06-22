#include "Cursor.h"
#include"../../Particle/Particle.h"
#include"../../../WindowUI/WindowUI.h"

void Cursor::Update()
{
	if (!m_cursorFlg)return;

	POINT Cursor;
	GetCursorPos(&Cursor);
	m_pos = { float(Cursor.x + m_rect.width) - 640,float((Cursor.y * -1) - m_rect.height) + 320 };

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_keyFlg)
		{
			for (int i = 0; i < ParticleNUM; ++i)
			{
				std::shared_ptr<Particle>particle = std::make_shared<Particle>();
				particle->SetTexture(m_particleTex);
				particle->Emit({ (float)Cursor.x - 640,float(Cursor.y * -1) + 320 },
					{ float(rand() % 3 - 1),float(rand() % 3 - 1) },
					3.0f,
					30);
				m_ptlList.push_back(particle);
			}
			m_keyFlg = true;
		}
	}
	else
	{
		m_keyFlg = false;
	}

	for (auto& particle : m_ptlList)particle->Update();
}

void Cursor::PostUpdate()
{
	auto it = m_ptlList.begin();

	while (it != m_ptlList.end())
	{
		const bool bFlg = (*it)->IsExpired();

		if (bFlg)
		{
			it = m_ptlList.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Cursor::DrawSprite()
{
	if (!m_cursorFlg)return;

	for (auto& particle : m_ptlList)particle->DrawSprite();

	KdShaderManager::Instance().m_spriteShader.DrawTex(&m_Tex, (int)m_pos.x, (int)m_pos.y, int(m_rect.width * m_size), int(m_rect.height * m_size), &m_rect);
}

void Cursor::Init()
{
	m_pos = {};
	m_rect = { 0,0,20,24 };
	m_size = 1.0f;
	m_Tex.Load("Asset/Textures/UI/Cursor/cursor_pointer3D.png");
	m_keyFlg = false;

	m_particleTex = std::make_shared<KdTexture>();
	m_particleTex->Load("Asset/Textures/UI/Cursor/Particle/Smoke_White.png");
}

void Cursor::FlgChange(bool Flg)
{
	m_cursorFlg = Flg;
}
