#pragma once
#include"../ButtomBase.h"

class Exit :public ButtomBase
{
public:
	Exit() { Init(); }
	~Exit()override {}

	void Update()override;
	void DrawSprite()override;
	void Init()override;

private:

};