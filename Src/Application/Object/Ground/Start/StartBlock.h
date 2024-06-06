#pragma once

class StartBlock :public KdGameObject
{
public:
	StartBlock() { Init(); }
	~StartBlock()override{}

	void Update()override;
	void DrawLit()override;
	void Init()override;

private:
	std::shared_ptr<KdModelData> m_model = nullptr;  //モデル
	Math::Vector3 m_pos;
	float m_size;
};