#pragma once

#include"../BaseScene/BaseScene.h"

class CharacterBase;

class GameScene : public BaseScene
{
public :

	GameScene() { Init(); }
	~GameScene() {}

private:

	void Event() override;
	void Init() override;

	//カメラ================================
	float         m_angleX;        //角度 X軸
	float         m_angleY;        //角度 Y軸
	float         m_ViewingAngle;  //視野角
	Math::Vector3 m_pos;           //座標
	//======================================

	std::weak_ptr<KdGameObject> m_player;  //プレイヤー ※カメラ制御のため
};
