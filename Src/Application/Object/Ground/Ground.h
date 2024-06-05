#pragma once

//地面
class Ground :public KdGameObject
{
public:
	Ground() { Init(); }
	~Ground()override{}

	void Update()override;
	void DrawLit()override;
	void Init()override;

private:

	std::shared_ptr<KdModelData> m_model = nullptr;  //モデル
	Math::Vector3 m_pos;
	float m_size;
};