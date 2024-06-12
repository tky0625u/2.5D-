﻿#pragma once

#include"Bullet/Bullet.h"
#include"../GimmickBase/GimmickBase.h"

#define COOL_TIME 2*60     //クールタイム 
#define CANNONDISTANS   10       //大砲の間隔
#define CorrectionX -0.5f  //X座標補正
#define CorrectionY 4.0f  //Y座標補正

class GimmickBase;

class Cannon :public GimmickBase
{
public:
	Cannon() { Init(); }
	~Cannon()override{}

	void Update()override;
	void PostUpdate()override;
	virtual void Draw();
	virtual void DrawLit()override;
	virtual void GenerateDepthMapFromLight()override;
	void Init()override;

	void CoolTimeUP();

	void SetPos(int i);

	const float GetCoolTime()const { return m_coolTime; }
	const std::shared_ptr<Bullet> GetBullet() const{ return m_bullet; }

private:
	float                        m_coolTime;   //発射クールタイム

	std::vector<std::shared_ptr<Bullet>>  m_bulletList;  //弾リスト
	std::shared_ptr<Bullet>               m_bullet;      //弾
};