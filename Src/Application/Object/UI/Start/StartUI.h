#pragma once

#define StartSIZECHANGE 0.4f
#define StartSIZEMAX    3.0f
#define Start_GO        3
#define Start_GO_SizeUP 0.05f
#define StartAlphaDOWN  0.02f

class StartUI :public KdGameObject
{
public:
	StartUI() { Init(); }
	~StartUI()override{}

	void Update()override;
	void DrawSprite()override;
	void Init()override;

	bool GetStart()const { return m_StartFlg; }

private:
	Math::Vector2   m_pos;
	Math::Rectangle m_rect;
	Math::Color     m_color;
	float           m_alpha;
	float           m_cutX;
	float           m_size;
	float           m_frame;
	bool            m_StartFlg;
	KdTexture       m_Tex;
};