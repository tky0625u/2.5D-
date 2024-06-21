#pragma once

#include"../BaseScene/BaseScene.h"

class TimerManager;

class ResultScene : public BaseScene
{
public:

	ResultScene() { Init(); }
	~ResultScene() {}

	void Update()override;
	void PostUpdate()override;
	void DrawSprite()override;
	void Load(std::string a_filePath);
	void BestWrite(std::string a_filePath,int Time);

private:

	void Event() override;
	void Init() override;

	//カメラ================================
	float         m_angleX;        //角度 X軸
	float         m_angleY;        //角度 Y軸
	float         m_ViewingAngle;  //視野角
	Math::Vector3 m_pos;           //座標
	//======================================

	std::shared_ptr<TimerManager> m_timer;
	int                           m_ResultTime;
	int                           m_frame;
	bool                          m_ramdomFlg;
	bool                          m_ramdomSoundFlg;
	bool                          m_StopSoundFlg;
	bool                          m_gameOverFlg;
};