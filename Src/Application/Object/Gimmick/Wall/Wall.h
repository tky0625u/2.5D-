#pragma once
#include"../GimmickBase/GimmickBase.h"

class Wall :public GimmickBase
{
public:
	Wall() { Init(); }
	~Wall()override{}

	void Update()override;
	void Init()override;

private:
};