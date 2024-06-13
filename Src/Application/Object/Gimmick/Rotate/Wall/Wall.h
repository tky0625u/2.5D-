#pragma once
#include"../../GimmickBase/GimmickBase.h"

class Wall :public GimmickBase
{
public:
	Wall() { Init(); }
	~Wall()override{}

	void Update()override;
	void Init()override;

	void SetPos(Math::Vector3 a_pos) { m_pos = a_pos; }

private:

};