#pragma once
#include"../GimmickBase/GimmickBase.h"

class Trampoline :public GimmickBase
{
public:
	Trampoline() { Init(); }
	~Trampoline()override{}

	void Update()override;
	void Init()override;

	void SetPos(Math::Vector3 a_pos) { m_pos += a_pos; }
	void SetSpeed(int i) { m_speed *= i; }

private:
	float m_reverse;
	float m_speed;
	float m_angleChange;
};