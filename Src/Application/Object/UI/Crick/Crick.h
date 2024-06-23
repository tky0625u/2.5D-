#pragma once

class Crick :public KdGameObject
{
public:
	Crick() { Init(); }
	~Crick()override {}

	void Update()override;
	void DrawSprite()override;
	void Init()override;

private:
	Math::Vector2   m_pos;
	Math::Color     m_color;
	Math::Rectangle m_rect;
	float           m_size;
	float           m_angle;
	float           m_alpha;
	KdTexture       m_tex;
};
