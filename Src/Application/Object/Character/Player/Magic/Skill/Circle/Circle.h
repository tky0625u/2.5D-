#pragma once

#define CicleSizeUP   0.1f  //魔法陣増加量
#define CicleSizeDown 0.2f  //魔法陣減少量

class Circle :public KdGameObject
{
public:
	Circle() { Init(); }
	~Circle()override{}

	void PreUpdate()override;
	void Update()override;
	void Draw();
	void DrawLit()override;
	void DrawBright()override;
	void Init()override;

	void SizeUP() { m_size += CicleSizeUP; }
	void SizeDOWN() { m_size -= CicleSizeDown; }
	void RotationY();
	void RotationZ();

	void SetPos(Math::Vector3 a_pos) { m_pos = a_pos; }
	void SetSizeMAX(float a_SizeMAX) { m_SizeMAX = a_SizeMAX; }
	void SetAngleX(float a_angleX) { m_angleX = a_angleX; }
	void SetAngleY(float a_angleY) { m_angleY = a_angleY; }

	const float GetSize()const { return m_size; }

private:
	std::shared_ptr<KdSquarePolygon> m_polygon;
	Math::Vector3                    m_pos;
	float                            m_size;
	float                            m_SizeMAX;
	float                            m_angleX;
	float                            m_angleY;
	float                            m_angleZ;
};