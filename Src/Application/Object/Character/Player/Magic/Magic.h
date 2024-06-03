#pragma once

#include"../PlayerBase.h"

#define COOLTIME 10.0f
#define SKILLNUN 2
#define NORMAL   0
#define ULT      1

class Ult;
class CutIn;
class Normal;
class Circle;

class Magic :public PlayerBase
{
public:
	Magic() { Init(); }
	~Magic()override{}

	void PreUpdate()override;
	void Update()override;
	void Draw()override;
	void DrawLit()override;
	void DrawBright()override;
	void DrawSprite()override;
	void Init()override;

	const bool GetStop()const { return m_bStop; }

private:
	//カットイン===========================================
	std::shared_ptr<CutIn>  m_cutIn = nullptr;
	KdTexture               m_cutInTex;
	KdTexture               m_pTex;  //プレイヤー画像
	//=====================================================

	//必殺技===============================================
	std::shared_ptr<Ult>    m_ult;
	bool                    m_bUlt;  //必殺技フラグ
	//=====================================================

	//通常技===============================================
	std::shared_ptr<KdModelData>          m_NormalModel;
	std::vector<std::shared_ptr<Normal>>  m_NormalList;
	int                                   m_CoolTime;
	bool                                  m_bNormal;
	//=====================================================

	//魔法陣===================================================================
	static const int             CircleNum = SKILLNUN;
	std::shared_ptr<Circle>      m_circle[CircleNum];
	//=========================================================================

	bool                    m_bStop;  //停止フラグ
};