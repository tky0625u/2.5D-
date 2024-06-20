#pragma once

class BackGround :public KdGameObject
{
public:
	BackGround() { Init(); }
	~BackGround()override{}

	void Update()override;
	void DrawUnLit()override;
	void Init()override;

	void SetPos(Math::Vector3 a_pos) { m_pos = a_pos; }
	void SetAngle(float a_angleX, float a_angleY) { m_angleX = a_angleX, m_angleY = a_angleY; }
	void SetPolygon(std::shared_ptr<KdSquarePolygon> a_polygon) { m_polygon = a_polygon; }
private:
	std::shared_ptr<KdSquarePolygon> m_polygon;
	Math::Vector3                    m_pos;
	float                            m_size;
	float                            m_angleX;
	float                            m_angleY;
};