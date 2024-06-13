#pragma once
#include"../../GimmickBase/GimmickBase.h"

class Circle :public GimmickBase
{
public:
	Circle() { Init(); }
	~Circle()override{}

	void Update()override;
	void Init();

	Math::Vector3 GetPos()const { return m_pos; }

private:

};