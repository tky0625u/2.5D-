#pragma once

class Road :public KdGameObject
{
public:
	Road() { Init(); }
	~Road()override{}

	void Update()override;
	void Draw();
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;
	void Init()override;

private:
	std::shared_ptr<KdModelData>  m_model;
	Math::Vector3                 m_pos;
	float                         m_size;
};