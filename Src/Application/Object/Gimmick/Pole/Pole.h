#pragma once

#define ROTATION_X 2.0f
#define POLEDISTANS 50.0f

class Pole :public KdGameObject
{
public:
	Pole() { Init(); }
	~Pole()override {}

	void Update()override;
	void PostUpdate()override;
	void Draw();
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;
	void Init()override;

	void SetPos(int i);

private:
	std::shared_ptr<KdModelData> m_model;      //モデル
	Math::Vector3                m_pos;        //座標
	float                        m_size;       //大きさ
	float                        m_angleX;      //角度X
	float                        m_angleY;      //角度Y
};