#pragma once

class BestTime :public KdGameObject
{
public:
	BestTime() { Init(); }
	~BestTime()override{}

	void DrawSprite()override;
	void Init()override;

	void SetPos(Math::Vector2 a_pos) { m_pos = a_pos; }
	void SetSize(float a_size) { m_size = a_size; }

private:
	Math::Vector2   m_pos;
	Math::Rectangle m_rect;
	float           m_size;
	KdTexture       m_tex;
};