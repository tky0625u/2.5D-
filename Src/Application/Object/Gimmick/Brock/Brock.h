#pragma once

class Brock :public KdGameObject
{
public:
	Brock() { Init(); }
	~Brock()override{}

	void Update()override;
	void Draw();
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;
	void Init()override;

private:
	std::shared_ptr<KdModelData> m_model = nullptr;  //モデル
	Math::Vector3 m_pos;
	float m_angle;
	float m_size;
};