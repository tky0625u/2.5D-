#pragma once

class ButtomBase :public KdGameObject
{
public:
	ButtomBase() { Init(); }
	~ButtomBase()override{}

	virtual void Update()override;
	virtual  void DrawSprite()override;
	virtual void Init()override;

	void HitON() { m_hitFlg = true; }
	void HitOFF() { m_hitFlg = false; }
	void PushON() { m_pushFlg = true; }
	void PushOFF() { m_pushFlg = false; }

	const Math::Vector2 GetPos() { return m_pos; }
	const Math::Rectangle GetRectangle() { return m_rect; }
	const bool GetHit() { return m_hitFlg; }
	const bool GetPush() { return m_pushFlg; }

protected:
	Math::Vector2   m_pos;
	Math::Color     m_color;
	Math::Rectangle m_rect;
	float           m_size;
	float           m_angle;
	float           m_alpha;
	bool            m_hitFlg;
	bool            m_pushFlg;
	KdTexture       m_Tex;
};