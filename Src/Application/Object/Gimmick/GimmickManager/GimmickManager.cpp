#include "GimmickManager.h"
#include"../Cannon/Cannon.h"
#include"../Pole/Pole.h"

void GimmickManager::Update()
{
	for (auto gimmick : m_GimmickList)gimmick->Update();
}

void GimmickManager::PostUpdate()
{
	for (int i = 0; i < CANNONNUM; ++i)
	{
		if (!m_cannon[i].expired())m_cannon[i].lock()->SetCameraPos(m_cameraPos);
	}
	for (auto gimmick : m_GimmickList)gimmick->PostUpdate();
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
	std::shared_ptr<Pole>pole = std::make_shared<Pole>();
	m_GimmickList.push_back(pole);
	//=============================================================================================
}
