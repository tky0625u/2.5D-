#pragma once

#include"../BaseScene/BaseScene.h"

class TimerManager;
class BestTime;

class TitleScene : public BaseScene
{
public :

	TitleScene() { Init(); }
	~TitleScene() {}

	void Update()override;
	void PostUpdate()override;
	void DrawSprite()override;
	void Load(std::string a_filePath);

private :

	void Event() override;
	void Init() override;

	//カメラ================================
	float         m_angleX;        //角度 X軸
	float         m_angleY;        //角度 Y軸
	float         m_ViewingAngle;  //視野角
	Math::Vector3 m_pos;           //座標
	//======================================

	std::shared_ptr<TimerManager> m_timer;
	std::shared_ptr<BestTime>     m_best;
};
