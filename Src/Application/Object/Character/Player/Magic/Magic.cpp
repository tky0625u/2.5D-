#include "Magic.h"
#include"../../../../WindowUI/WindowUI.h"
#include"Skill/Ult/Ult.h"
#include"Skill/CutIn/CutIn.h"
#include"Skill/Normal/Normal.h"
#include"Skill/Circle/Circle.h"

void Magic::PreUpdate()
{
	if (!m_bFlg)return;

	//必殺技===================================================================================================================================================

	//カットイン========================================================================================================
	if (GetAsyncKeyState('E') & 0x8000)
	{
		if (!m_bUlt && !m_bStop)
		{
			m_cutIn = std::make_shared<CutIn>();
			m_cutIn->SetTexture(&m_cutInTex, &m_pTex);
			for (int i = 0; i < CircleNum; ++i)
			{
				m_circle[i].reset();
				m_circle[i] = nullptr;
			}
			m_bStop = true;
		}
	}
	//==================================================================================================================

	if (!m_bUlt)
	{
		//出現==============================================================================================================
		if (m_cutIn != nullptr && m_cutIn->IsExpired())  //カットインが終わったら
		{
			//カットイン消滅
			m_cutIn.reset();
			m_cutIn = nullptr;

			//必殺技生成
			m_ult = std::make_shared<Ult>();  //生成
			m_ult->SetPos({ m_pos.x + sin(DirectX::XMConvertToRadians(m_angle)) * DEFAULTPOS,m_pos.y,m_pos.z + cos(DirectX::XMConvertToRadians(m_angle)) * DEFAULTPOS });  //座標 ※プレイヤーの少し前
			m_ult->SetAngle(m_angle);  //角度　※プレイヤーの目の前に来るように
			m_ult->SetAtk(status.Atk); //攻撃力

			m_circle[ULT] = std::make_shared<Circle>();
			m_circle[ULT]->SetAngleX(UltCircleAngleX);
			m_circle[ULT]->SetPos({ m_pos.x,m_pos.y + 0.1f,m_pos.z });

			m_bUlt = true; //フラグオン　※二度撃ち防止
		}
		else if (m_cutIn != nullptr)
		{
			m_cutIn->PreUpdate();
		}
		//==================================================================================================================
	}
	else
	{
		if (m_ult->GetSize() < SIZEMAX)  //サイズが小さい時はプレイヤーの目の前に来るようにする
		{
			m_ult->SetPos({ m_pos.x + sin(DirectX::XMConvertToRadians(m_angle)) * DEFAULTPOS,m_pos.y,m_pos.z + cos(DirectX::XMConvertToRadians(m_angle)) * DEFAULTPOS });
			m_ult->SetAngle(m_angle);
			m_circle[ULT]->SizeUP();
		}
		else
		{
			m_bStop = false;
			if (m_circle[ULT] != nullptr)
			{
				m_circle[ULT]->PreUpdate();
				m_circle[ULT]->RotationY();
				m_circle[ULT]->SizeDOWN();
				m_circle[ULT]->SetPos({ m_pos.x,m_pos.y + 0.1f,m_pos.z });
			
				if (m_circle[ULT]->IsExpired())
				{
					m_circle[ULT].reset();
					m_circle[ULT] = nullptr;
					m_ult->FlgOFF();
				}
			}
		}

		m_ult->PreUpdate();

		if (m_ult->IsExpired())  //消滅したらリセット
		{
			m_ult.reset();
			m_bUlt = false;
		}
	}
	//==============================================================================================================================================================

	if (!m_bStop)
	{
		//通常技=======================================================================================================================================================================================
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			//魔法陣=============================================================
			if (m_circle[NORMAL] == nullptr)
			{
				m_circle[NORMAL] = std::make_shared<Circle>();  //生成
				m_circle[NORMAL]->SetAngleX(NORMALCircleAngleX);                 //角度X
				m_circle[NORMAL]->SetAngleY(m_angle);           //角度Y
				m_circle[NORMAL]->SetPos({ m_pos.x + sin(DirectX::XMConvertToRadians(m_angle)) * NORMALDEFAULTPOS,m_pos.y+1.0f,m_pos.z + cos(DirectX::XMConvertToRadians(m_angle)) * NORMALDEFAULTPOS });  //座標　※プレイヤーの少し前
			}
			//===================================================================
			if (m_CoolTime <= 0 && m_circle[NORMAL]->GetSize()>=NORMALCircleSizeMAX)  //クールタイムが終わったらAND魔法陣が大きくなったら
			{
				std::shared_ptr<Normal>normal = std::make_shared<Normal>();
				normal->SetModel(m_NormalModel);
				normal->SetPos({ m_pos.x + sin(DirectX::XMConvertToRadians(m_angle)) * NORMALDEFAULTPOS,m_pos.y+1.0f,m_pos.z + cos(DirectX::XMConvertToRadians(m_angle)) * NORMALDEFAULTPOS });  //座標 ※プレイヤーの少し前
				normal->SetAngle(m_angle);  //角度　※プレイヤーの目の前に来るように
				normal->SetAtk(status.Atk); //攻撃力
				m_NormalList.push_back(normal);  //リスト追加
				m_CoolTime = COOLTIME;           //クールタイム
			}
			m_bNormal = true;
		}
		else
		{
			m_bNormal = false;
		}

		//魔法陣===================================================================================
		if (m_circle[NORMAL] != nullptr)
		{
			if (m_bNormal && m_circle[NORMAL]->GetSize() < NORMALCircleSizeMAX)m_circle[NORMAL]->SizeUP();  //最大まで増加
			else if(!m_bNormal)
			{
				m_circle[NORMAL]->SizeDOWN();  //フラグがオフになったら減少
			}

			//プレイヤーの正面に来るように=============================================
			m_circle[NORMAL]->SetAngleY(m_angle);
			m_circle[NORMAL]->SetPos({ m_pos.x + sin(DirectX::XMConvertToRadians(m_angle)) * NORMALDEFAULTPOS,m_pos.y+1.0f,m_pos.z + cos(DirectX::XMConvertToRadians(m_angle)) * NORMALDEFAULTPOS });
			//=========================================================================
			m_circle[NORMAL]->RotationZ();
			m_circle[NORMAL]->PreUpdate();
			if (m_circle[NORMAL]->IsExpired())
			{
				m_circle[NORMAL].reset();
				m_circle[NORMAL] = nullptr;
			}
		}
		//===========================================================================================

		PlayerBase::PreUpdate();
		for (auto normal : m_NormalList)normal->PreUpdate();

		//リスト削除=================================================================================
		std::vector<std::shared_ptr<Normal>>::iterator it = m_NormalList.begin();
		while (it != m_NormalList.end())
		{
			const bool normalFlg = (*it)->IsExpired();

			if (normalFlg)
			{
				it = m_NormalList.erase(it);
			}
			else
			{
				it++;
			}
		}
		//============================================================================================

		//クールタイム================================================================================
		m_CoolTime--;
		if (m_CoolTime <= 0)m_CoolTime = 0;
		//============================================================================================
		 
		//=============================================================================================================================================================================================
	}
}

void Magic::Update()
{
	//プレイヤー============================
	PlayerBase::Update();
	//======================================

	//魔法陣================================
	for (int i = 0; i < CircleNum; ++i)
	{
		if (m_circle[i] != nullptr)m_circle[i]->Update();
	}
	//======================================

	//カットイン============================
	if (m_cutIn != nullptr)m_cutIn->Update();
	//======================================

	//必殺技================================
	if (m_bUlt)m_ult->Update();
	//======================================

	//通常技================================
	for (auto normal : m_NormalList)normal->Update();
	//======================================
}

void Magic::Draw()
{
	if (!m_bFlg)return;
	PlayerBase::Draw();
}

void Magic::DrawLit()
{
	//プレイヤー===========================
	PlayerBase::DrawLit();
	//=====================================

	//必殺技===============================
	if (m_bUlt)m_ult->DrawLit();
	//=====================================

	//魔法陣===============================
	for (int i = 0; i < CircleNum; ++i)
	{
		if (m_circle[i] != nullptr)m_circle[i]->DrawLit();
	}
	//=====================================
}

void Magic::DrawBright()
{
	//通常技===============================
	for (auto normal : m_NormalList)normal->DrawBright();
	//=====================================

	//必殺技===============================
	if (m_bUlt)m_ult->DrawBright();
	//=====================================

	//魔法陣===============================
	for (int i = 0; i < CircleNum; ++i)
	{
		if (m_circle[i] != nullptr)m_circle[i]->DrawBright();
	}
	//=====================================
}

void Magic::DrawSprite()
{
	//カットイン===========================
	if (m_cutIn != nullptr)m_cutIn->DrawSprite();
	//=====================================
}

void Magic::Init()
{
	//カットイン===============================================================
	m_cutInTex.Load("Asset/Textures/CutIn/CutInYellow.png");
	m_pTex.Load("Asset/Textures/Character/Player/player.png");
	//=========================================================================

	//プレイヤー===============================================================
	PlayerBase::Init();
	status = { 1,1,1,1,1 };
	m_polygon->SetMaterial("Asset/Textures/Character/Player/player.png");
	//=========================================================================

	//通常技===================================================================
	m_NormalModel = std::make_shared<KdModelData>();
	m_NormalModel->Load("Asset/Models/Player/Skill/Ult/Fire.gltf");
	m_CoolTime = 0;
	//=========================================================================

	m_bUlt = false;   //必殺技
	m_bStop = false;  //停止
}
