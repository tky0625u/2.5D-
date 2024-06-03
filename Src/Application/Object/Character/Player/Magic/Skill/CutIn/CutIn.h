#pragma once

//カットイン==============================================================
#define CUTINHIGHT 480    //カットインの高さ
#define CUTINCutNUM 5     //カットインの最大枚数
#define CUTINCNTNUM 1     //カットインが最大サイズになった時の停滞時間
#define FLUCT        0.01  //カットインの増減サイズ
#define CUTINSIZEMAX       0.1   //カットインの最大サイズ
#define CUTINSIZEMIN       0.0   //カットインの最小サイズ
//========================================================================

//プレイヤー画像==========================================================
#define PLAYERSPEED        50    //プレイヤー画像移動量
#define PlayerMin          -700  //プレイヤー画像移動距離左端
#define PlayerMax          700   //プレイヤー画像移動距離右端
#define PlayerSIZE         0.5f  //プレイヤー画像サイズ
//========================================================================

class CutIn :public KdGameObject
{
public:
	CutIn() { Init(); }
	~CutIn()override {}

	void PreUpdate()override;
	void Update()override;
	void DrawSprite()override;
	void Init()override;

	void SetTexture(KdTexture* a_pTex, KdTexture* a_pPlayerTex) {
																	m_pTex = a_pTex;
																	m_pPlayerTex = a_pPlayerTex;
																}

private:
	float animeCnt;   //アニメーション間隔
	float m_size;     //カットインサイズ
	float CutInCnt;  //カットインアニメーション間隔
	int   cutY;
	bool  fluctFlg;   //カットイン増減フラグ
	Math::Vector3   m_pos;
	Math::Color     m_color;
	Math::Rectangle m_rect;
	Math::Matrix    m_scale;
	Math::Matrix    m_trans;
	Math::Matrix    m_mat;
	KdTexture*      m_pTex;

	float           m_PlayerSize;
	Math::Vector3   m_PlayerPos;
	Math::Color     m_PlayerColor;
	Math::Rectangle m_PlayerRect;
	Math::Matrix    m_PlayerMat;
	KdTexture*      m_pPlayerTex;

	Math::Color     m_brackColor;
	Math::Matrix    m_blackMat;

	std::shared_ptr<KdSoundEffect> se;
	std::shared_ptr<KdSoundInstance> seInst;
};