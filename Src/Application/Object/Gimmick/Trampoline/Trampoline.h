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
	void SetReverse(float a_reverse) { m_reverse += a_reverse; }

private:
	float m_reverse;
};