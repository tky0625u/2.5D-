#pragma once

class GoalUI :public KdGameObject
{
public:
	GoalUI() { Init(); }
	~GoalUI()override { m_Tex.Release(); }

	void Update()override;
	void DrawSprite()override;
	void Init()override;

	const bool GetFinish()const { return m_finishFlg; }

private:
	Math::Vector2   m_pos;
	float           m_size;
	bool            m_finishFlg;
	KdTexture       m_Tex;
};