#include "GimmickManager.h"
#include"../Cannon/Cannon.h"
#include"../Pole/Pole.h"
#include"../Brock/Brock.h"
#include"../Board/Board.h"
#include"../Trampoline/Trampoline.h"
#include"../Rotate/Circle/Circle.h"
#include"../Rotate/Wall/Wall.h"

void GimmickManager::Update()
{
	for (auto gimmick : m_GimmickList)gimmick->Update();
	
	//弾リスト格納==========================================================================
	for (int i = 0; i < CANNONNUM; ++i)
	{
		if (!m_cannon[i].expired())
		{
			if (m_cannon[i].lock()->GetCoolTime() <= 0)
			{
				std::shared_ptr<KdGameObject> bullet = m_cannon[i].lock()->GetBullet();
				m_BulletList.push_back(bullet);
				m_cannon[i].lock()->CoolTimeUP();  //クールタイム
			}
		}
	}
	//======================================================================================
}

void GimmickManager::PostUpdate()
{
	for (auto gimmick : m_GimmickList)gimmick->PostUpdate();

	std::vector<std::shared_ptr<KdGameObject>>::iterator it = m_BulletList.begin();
	while (it != m_BulletList.end())
	{
		const bool m_bFlg = (*it)->IsExpired();
		if (m_bFlg)  //存在消滅フラグがオンだったら削除
		{
			it = m_BulletList.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void GimmickManager::DrawLit()
{
	for (auto gimmick : m_GimmickList)gimmick->DrawLit();
}

void GimmickManager::GenerateDepthMapFromLight()
{
	for (auto gimmick : m_GimmickList)gimmick->GenerateDepthMapFromLight();
}

void GimmickManager::Init()
{
	//大砲=========================================================================================
	for (int i = 0; i < CANNONNUM; ++i)
	{
		std::shared_ptr<Cannon>cannon = std::make_shared<Cannon>();
		cannon->SetPos(i);
		m_GimmickList.push_back(cannon);
		m_cannon[i] = cannon;
	}
	//=============================================================================================

	//ポール=======================================================================================
	for (int i = 0; i < POLENUM; ++i)
	{
		std::shared_ptr<Pole>pole = std::make_shared<Pole>();
		pole->SetPos(i);
		m_GimmickList.push_back(pole);
	}
	//=============================================================================================

	//一マス床=====================================================================================
	std::shared_ptr<Brock>brock = std::make_shared<Brock>();
	m_GimmickList.push_back(brock);
	//=============================================================================================

	//動く床=======================================================================================
	for (int i = 0; i < BOARDNUM; ++i)
	{
		std::shared_ptr<Board>board = std::make_shared<Board>();
		board->SetPos(i);
		board->ChangeSpeed(i);
		m_GimmickList.push_back(board);
	}
	//=============================================================================================

	//トランポリン=================================================================================
	for (int i = 0; i < TRAMPOLINENUM; ++i)
	{
		std::shared_ptr<Trampoline>trampoline = std::make_shared<Trampoline>();
		trampoline->SetPos(Math::Vector3{ i * 25.0f,i * 10.0f,i * 6.0f });
		trampoline->SetReverse(i * 10.0f);
		m_GimmickList.push_back(trampoline);
	}
	//=============================================================================================

	//回転壁=======================================================================================
	
	//床=======================================================================
	std::shared_ptr<Circle>circle = std::make_shared<Circle>();
	m_GimmickList.push_back(circle);
	//=========================================================================

	//壁=======================================================================
	std::shared_ptr<Wall>wall = std::make_shared<Wall>();
	wall->SetPos(circle->GetPos());
	m_GimmickList.push_back(wall);
	//=========================================================================
	
	//=============================================================================================
}
