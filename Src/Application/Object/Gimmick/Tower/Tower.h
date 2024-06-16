#pragma once
#include"../GimmickBase/GimmickBase.h"

class Tower :public GimmickBase
{
public:
	Tower() { Init(); }
	~Tower()override{}

	void Update()override;
	void Init()override;

private:

};