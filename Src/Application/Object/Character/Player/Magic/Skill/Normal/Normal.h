#pragma once

//通常技===============================
#define NORMALSPEED      2.0f
#define NORMALDEFAULTPOS 1.0f
#define NORMALALIVE      1*60
//=====================================

#define NORMALCircleAngleX  0
#define NORMALCircleSizeMAX 2.0f

class Normal :public KdGameObject
{
public:
	Normal() { Init(); }
	~Normal()override {}

	void PreUpdate()override;
	void Update()override;
	void Draw();
	void DrawBright()override;
	void Init()override;

	void SetPos(Math::Vector3 a_pos) { m_pos = a_pos; }
	void SetAtk(int a_Atk) { m_PlayerAtk = a_Atk; }
	void SetModel(std::shared_ptr<KdModelData> a_model) { m_model = a_model; }
	void SetAngle(float a_angle) { m_angle = a_angle; }

	const int   GetDamage()const { return m_Atk * m_PlayerAtk; }

private:
	std::shared_ptr<KdModelData> m_model;
	Math::Vector3                m_pos;
	int                          m_Atk;        //攻撃力
	int                          m_PlayerAtk;  //プレイヤー攻撃力
	int                          m_AliveTime;
	float                        m_angle;
};