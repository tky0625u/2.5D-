#pragma once

class Camera :public KdGameObject
{
public:
	Camera() { Init(); }
	~Camera()override{}

	void Update()override;
	void Init()override;

	void SetPlayerAngle(float a_PlayerAngleX, float a_PlayerAngleY);
	void SetPlayerPos(Math::Vector3 a_PlayerPos);

private:
	float         m_angleX;        //角度 X軸
	float         m_angleY;        //角度 Y軸
	float         m_ViewingAngle;  //視野角
	Math::Vector3 m_pos;           //座標
	Math::Vector3 m_PlayerPos;     //座標
};