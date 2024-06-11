#pragma once
#include"../GimmickBase/GimmickBase.h"

class Trampoline :public GimmickBase
{
public:
	Trampoline() { Init(); }
	~Trampoline()override{}

	void Update()override;
	void Init()override;

private:

};