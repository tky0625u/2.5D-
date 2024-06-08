#pragma once
#include"../GimmickBase/GimmickBase.h"

class GimmickBase;

class Brock :public GimmickBase
{
public:
	Brock() { Init(); }
	~Brock()override{}

	void Update()override;
	void Init()override;

private:
};