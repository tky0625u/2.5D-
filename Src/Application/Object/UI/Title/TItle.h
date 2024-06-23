#pragma once

class Title :public KdGameObject
{
public:
	Title() { Init(); }
	~Title()override {}

	void Update()override;
	void DrawSprite()override;
	void Init()override;

private:
	Math::Vector2   m_pos;
	Math::Vector2   m_move;
	Math::Rectangle m_rect;
	float           m_size;
	float           m_angle;
	KdTexture       m_tex;
};
