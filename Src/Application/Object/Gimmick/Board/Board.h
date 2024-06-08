#pragma once
#include"../GimmickBase/GimmickBase.h"

#define BOARDDISTANS 20.0f

class GimmickBase;

class Board :public GimmickBase
{
public:
	Board() { Init(); }
	~Board()override{}

	void Update()override;
	void Init()override;

	void SetPos(int i);
	void ChangeSpeed(int i);

private:
	float                        m_speed;      //速さ
};