#pragma once

class BigCloud :public KdGameObject
{
public:
	BigCloud() { Init(); }
	~BigCloud()override{}

	void Update()override;
	void DrawLit()override;
	void DrawBright()override;
	void Init()override;

private:
	std::shared_ptr<KdModelData> m_model;
	Math::Vector3                m_pos;
	float                        m_size;
};