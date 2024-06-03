#include "CutIn.h"
#include"../../../../../../WindowUI/WindowUI.h"

void CutIn::PreUpdate()
{
	//カットインのサイズ増減========================================
	if (fluctFlg)m_size += FLUCT;         //増減フラグがtrueで増加
	else if (!fluctFlg)m_size -= FLUCT; //増減フラグがfalseで減少
	//==============================================================

	//カットイン　アニメーション====================================
	animeCnt--; //アニメーション制御
	if (animeCnt <= 0)
	{
		cutY += CUTINHIGHT; //一枚分進める
		animeCnt = ANIME; //間隔をとる
		if (cutY >= CUTINHIGHT * CUTINCutNUM) //最大まで
		{
			cutY = 0; //最初に戻す
		}
	}
	//==============================================================

	//カットイン増減制御=================================================================================
	if (m_size >= CUTINSIZEMAX)
	{
		m_size = CUTINSIZEMAX;

		//プレイヤー画像==================================================
		m_PlayerPos.x += PLAYERSPEED;
		if (CutInCnt < CUTINCNTNUM * SECOND)
		{
			if (m_PlayerPos.x >= 0)
			{
				CutInCnt++;         //カットイン増減停滞用
				m_PlayerPos.x = 0;  //中心に停滞
			}
		}
		//================================================================

		if (m_PlayerPos.x > PlayerMax)fluctFlg = false;//プレイヤー画像が画面から出たらたったら増減フラグをfalse
	}
	else if (!fluctFlg && m_size <= CUTINSIZEMIN)
	{
		m_isExpired = true;
	}
	//===================================================================================================

	m_rect = { 0,cutY,WIDE,CUTINHIGHT };
}

void CutIn::Update()
{
	m_scale = Math::Matrix::CreateScale(1, m_size, 1);
	m_trans = Math::Matrix::CreateTranslation(m_pos);
	m_mat = m_scale * m_trans;

	Math::Matrix PlayerScale = Math::Matrix::CreateScale(m_PlayerSize);
	Math::Matrix PlayerTrans = Math::Matrix::CreateTranslation(m_PlayerPos);
	m_PlayerMat = PlayerScale * PlayerTrans;

	m_blackMat = Math::Matrix::CreateTranslation(0, 0, 0);
}

void CutIn::DrawSprite()
{
	//背景========================================================================================================
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_blackMat);
	KdShaderManager::Instance().m_spriteShader.DrawBox(0, 0, WIDE / 2, HIGHT / 2, &m_brackColor, true);
	//============================================================================================================

	//カットイン==================================================================================================
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_mat);
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pTex, 0, 0, &m_rect, &m_color);
	//============================================================================================================

	//プレイヤー画像==============================================================================================
	KdShaderManager::Instance().m_spriteShader.SetMatrix(m_PlayerMat);
	KdShaderManager::Instance().m_spriteShader.DrawTex(m_pPlayerTex, 0, 0, &m_PlayerRect, &m_PlayerColor);
	//============================================================================================================
}

void CutIn::Init()
{
	//カットイン=================================
	animeCnt = 0.0f;
	m_size = CUTINSIZEMIN;
	CutInCnt = 0.0f;
	cutY = 0;
	fluctFlg = true;
	m_pos = { 0,0 };
	m_color = { 1,1,1,1 };
	m_rect = { 0,cutY,WIDE,CUTINHIGHT };
	//===========================================

	//プレイヤー画像=============================
	m_PlayerSize = PlayerSIZE;
	m_PlayerPos = { PlayerMin,m_pos.y,m_pos.z };
	m_PlayerColor = { 1,1,1,1 };
	m_PlayerRect = { 64,0,64,64 };
	//===========================================

	m_brackColor = { 0,0,0,0.5f };  //背景
}
