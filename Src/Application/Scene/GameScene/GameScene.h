#pragma once

#include"../BaseScene/BaseScene.h"

class GimmickManager;
class Player;
class GoalUI;

class GameScene : public BaseScene
{
public :

	GameScene() { Init(); }
	~GameScene() {}

	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;

	void DrawSprite()override;

private:

	void Event() override;
	void Init() override;

	//カメラ================================
	float         m_angleX;        //角度 X軸
	float         m_angleY;        //角度 Y軸
	float         m_ViewingAngle;  //視野角
	Math::Vector3 m_pos;           //座標
	//======================================

	std::weak_ptr<Player>         m_player;  //プレイヤー ※カメラ制御のため
	std::weak_ptr<GimmickManager> m_gimmick; //ギミック管理クラス　※弾の削除処理のため
	std::shared_ptr<GoalUI>       m_goalUI;
};
