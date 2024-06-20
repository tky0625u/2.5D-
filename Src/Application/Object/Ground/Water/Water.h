#pragma once

class Water :public KdGameObject
{
public:
	Water() { Init(); }
	~Water()override{}

	void Update()override;
	void DrawLit()override;
	void Init()override;

	void SetPos(Math::Vector3 a_pos) { m_pos = a_pos; }

private:
	std::shared_ptr<KdModelData> m_model;
	Math::Vector3                m_pos;
	float                        m_size;
};