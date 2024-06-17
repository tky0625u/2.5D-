#pragma once

class GoalUI :public KdGameObject
{
public:
	GoalUI() { Init(); }
	~GoalUI()override { m_Tex.Release(); }

	void Update()override;
	void DrawSprite()override;
	void Init()override;

private:
	Math::Vector2   m_pos;
	float           m_size;
	KdTexture       m_Tex;
};