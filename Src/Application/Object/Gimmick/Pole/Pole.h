#pragma once
#include"../GimmickBase/GimmickBase.h"

#define ROTATION_X 2.0f
#define POLEDISTANS 50.0f

class GimmickBase;

class Pole :public GimmickBase
{
public:
	Pole() { Init(); }
	~Pole()override {}

	void Update()override;
	void Init()override;

	void Rotation(int i);

	void SetPos(int i);

private:
	float                        m_angleX;      //角度X
	float                        m_angleY;      //角度Y
	float                        m_rotationX;   //回転X軸
};