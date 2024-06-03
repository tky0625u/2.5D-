#pragma once

#include"../CharacterBase.h"

class EnemyBase :public CharacterBase
{
public:
	EnemyBase() { Init(); }
	~EnemyBase()override{}

	virtual void PreUpdate()override = 0;
	virtual void Update()override = 0;
	virtual void Draw() = 0;
	virtual void Init()override = 0;

	void SetPlayerPos(Math::Vector3 a_PlayerPos) { m_playerPos = a_PlayerPos; }

private:
	float         m_AtkRange;  //攻撃範囲
	bool          m_AtkFlg;    //攻撃フラグ
	Math::Vector3 m_playerPos; //プレイヤーの座標
};