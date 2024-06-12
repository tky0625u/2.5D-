#include "GimmickManager.h"
#include"../Cannon/Cannon.h"
#include"../Pole/Pole.h"
#include"../Brock/Brock.h"
#include"../Board/Board.h"
#include"../Trampoline/Trampoline.h"
#include"../Wall/Wall.h"

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
	for (int i = 0; i < CANNONNUM; ++i)
	{
		if (!m_cannon[i].expired())m_cannon[i].lock()->SetCameraPos(m_cameraPos);  //カメラ座標
	}
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

	//動く床=====================================================================================
	for (int i = 0; i < BOARDNUM; ++i)
	{
		std::shared_ptr<Board>board = std::make_shared<Board>();
		board->SetPos(i);
		board->ChangeSpeed(i);
		m_GimmickList.push_back(board);
	}
	//=============================================================================================

	//トランポリン=================================================================================
	std::shared_ptr<Trampoline>trampoline = std::make_shared<Trampoline>();
	m_GimmickList.push_back(trampoline);
	//=============================================================================================

	//反り立つ壁===================================================================================
	std::shared_ptr<Wall>wall = std::make_shared<Wall>();
	m_GimmickList.push_back(wall);
	//=============================================================================================
}
