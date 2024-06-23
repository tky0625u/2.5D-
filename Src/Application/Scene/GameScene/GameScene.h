#pragma once

#include"../BaseScene/BaseScene.h"

class GimmickManager;
class Player;
class TimerManager;
class StartUI;

class GameScene : public BaseScene
{
public :

	GameScene() { Init(); }
	~GameScene() {}

	void PreUpdate()override;
	void Update()override;
	void PostUpdate()override;

	void DrawSprite()override;

	void Write(std::string a_filePath);

private:

	void Event() override;
	void Init() override;

	//カメラ================================
	float         m_angleX;        //角度 X軸
	float         m_angleY;        //角度 Y軸
	float         m_ViewingAngle;  //視野角
	bool          m_ViewFlg;
	bool          m_seFlg;
	Math::Vector3 m_pos;           //座標
	//======================================

	std::weak_ptr<Player>         m_player;  //プレイヤー ※カメラ制御のため
	std::weak_ptr<GimmickManager> m_gimmick; //ギミック管理クラス　※弾の削除処理のため
	std::weak_ptr<TimerManager>   m_timer;
	std::weak_ptr<StartUI>        m_startUI;

	bool                          m_bgmFlg;
	bool                          m_menuFlg;
	bool                          m_keyFlg;
};
