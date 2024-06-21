#pragma once

class Goal :public KdGameObject
{
public:
	Goal() { Init(); }
	~Goal()override{}

	void Update()override;
	void DrawLit()override;
	void Init()override;

	void SetPos(Math::Vector3 a_pos) { m_pos = a_pos; }
	void SetAngle(float a_angle) { m_angle = a_angle; }

private:
	std::shared_ptr<KdModelData> m_model = nullptr;  //モデル
	Math::Vector3                m_pos;
	float                        m_size;
	float                        m_angle;
};