#pragma once

#include"Bullet/Bullet.h"

#define COOL_TIME 2*60     //クールタイム 
#define DISTANS   10       //大砲の間隔
#define CorrectionX -0.5f  //X座標補正
#define CorrectionY 4.0f  //Y座標補正

class Cannon :public KdGameObject
{
public:
	Cannon() { Init(); }
	~Cannon()override{}

	void Update()override;
	void PostUpdate()override;
	void Draw();
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;
	void Init()override;

	void CoolTimeUP();

	void SetPos(int i);
	void SetCameraPos(Math::Vector3 a_cameraPos) { m_cameraPos = a_cameraPos; }

	const float GetCoolTime()const { return m_coolTime; }
	const std::shared_ptr<Bullet> GetBullet() const{ return m_bullet; }

private:
	std::shared_ptr<KdModelData> m_model;      //モデル
	Math::Vector3                m_pos;        //座標
	float                        m_size;       //大きさ
	float                        m_angle;      //角度
	float                        m_coolTime;   //発射クールタイム

	Math::Vector3                m_cameraPos;  //カメラ座標

	std::vector<std::shared_ptr<Bullet>>  m_bulletList;  //弾リスト
	std::shared_ptr<Bullet>               m_bullet;      //弾
};