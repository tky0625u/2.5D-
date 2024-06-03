#pragma once

class Player :public KdGameObject
{
public:
	Player() { Init(); }
	~Player()override{}

	void Update()override;
	void PostUpdate()override;
	void Draw();
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;
	void Init()override;

private:
	std::shared_ptr<KdSquarePolygon> m_polygon;
	Math::Vector3 m_pos;
	Math::Vector3 m_move;
	Math::Vector3 m_dir;
	float m_size;                                //サイズ
	float m_angle;                               //角度
	float m_gravity;
	bool  m_jumpFlg;
};