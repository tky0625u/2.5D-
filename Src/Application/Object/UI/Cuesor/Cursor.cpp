#include "Cursor.h"
#include"../../Particle/Particle.h"
#include"../../../WindowUI/WindowUI.h"
#include"../Buttom/ButtomBase.h"

void Cursor::Update()
{
	if (!m_cursorFlg)return;


	GetCursorPos(&cursor);
	m_pos = { float(cursor.x + (m_rect.width / 2)) - 640,float((cursor.y * -1) - (m_rect.height / 2)) + 360 };

	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (!m_keyFlg)
		{
			for (auto& buttom : m_buttomList)
			{
				if (buttom->GetHit())
				{
					buttom->PushON();
				}
			}

			for (int i = 0; i < ParticleNUM; ++i)
			{
				std::shared_ptr<Particle>particle = std::make_shared<Particle>();
				particle->SetTexture(m_particleTex);
				particle->Emit({ (float)cursor.x - 640,float(cursor.y * -1) + 360 },
					{ float(rand() % 3 - 1),float(rand() % 3 - 1) },
					3.0f,
					30);
				m_ptlList.push_back(particle);
			}
			KdAudioManager::Instance().Play("Asset/Sounds/SE/Crick/決定ボタンを押す2.WAV", 0.5f, false);
			m_keyFlg = true;
		}
	}
	else
	{
		m_keyFlg = false;
		for (auto& buttom : m_buttomList)buttom->PushOFF();
	}

	for (auto& particle : m_ptlList)particle->Update();
}

void Cursor::PostUpdate()
{
	for (auto& buttom : m_buttomList)
	{
		Math::Vector2 buttomPos = buttom->GetPos();
		Math::Rectangle buttomRect = buttom->GetRectangle();

		if (m_pos.x - (m_rect.width / 2) > buttomPos.x - (buttomRect.width / 2) && m_pos.x - (m_rect.width / 2) < buttomPos.x + (buttomRect.width / 2) && m_pos.y + (m_rect.height / 2) > buttomPos.y - (buttomRect.height / 2) && m_pos.y + (m_rect.height / 2) < buttomPos.y + (buttomRect.height / 2))
		{
			buttom->HitON();
		}
		else
		{
			buttom->HitOFF();
		}
	}

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
