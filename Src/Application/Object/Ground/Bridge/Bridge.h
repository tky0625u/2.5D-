#pragma once

class Bridge :public KdGameObject
{
public:
	Bridge() { Init(); }
	~Bridge()override{}

	void Update()override;
	void DrawLit()override;
	void Init()override;

private:
	std::shared_ptr<KdModelData> m_model;
	Math::Vector3 m_pos;
	float m_size;
};