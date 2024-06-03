#pragma once

//必殺技=========================================
#define SIZEMAX   4.0f   //最大サイズ
#define SIZEUP    0.01f  //サイズ増加量
#define ULTSPEED     1.0f   //速さ
#define DEFAULTPOS 5     //プレイヤーの少し前
//===============================================

#define UltCircleAngleX 90  //魔法陣の角度X

class Circle;

class Ult:public KdGameObject
{
public:
	Ult() { Init(); }
	~Ult()override{}

	void PreUpdate()override;
	void Update()override;
	void Draw();
	void DrawLit()override;
	void DrawBright()override;
	void Init();

	void SetPos(Math::Vector3 a_pos);  //必殺技座標
	void SetAngle(float a_angle) { m_angle = a_angle; }
	void SetAtk(int a_Atk) { m_PlayerAtk = a_Atk; }
	void FlgOFF();

	const float GetSize()const { return m_size; }
	const int   GetDamage()const { return m_Atk * m_PlayerAtk; }

private:
	//必殺技===================================================================
	std::shared_ptr<KdModelData> m_model;
	Math::Vector3                m_pos;
	int                          m_AliveTime;  //生存時間
	int                          m_Atk;        //攻撃力
	int                          m_PlayerAtk;  //プレイヤー攻撃力
	float                        m_size;
	float                        m_angle;
	//=========================================================================
	
	//魔法陣===================================================================
	std::shared_ptr<Circle>      m_circle;
	//=========================================================================
};