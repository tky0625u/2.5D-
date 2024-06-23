#pragma once
#include"../../Gimmick/GimmickBase/GimmickBase.h"

#define WAALK_SPEED 0.3f  //歩く移動量
#define DASH_SPEED 0.5f   //走る移動量
#define JUMP  1.0f        //ジャンプ力

//アニメーション=================================
#define IDOL 0
#define WALK 1
#define DASH 2
#define IDOL_MAX 4
#define WALK_MAX 7
#define DASH_MAX 7
//===============================================

#define VP_SPEED 0.02f //振り向き速度

class GimmickBase;

class Player :public KdGameObject
{
public:
	struct Animation
	{
		int m_motion;
		int m_CntMAX;
		float m_AnimeCnt;
	};

	Player() { Init(); }
	~Player()override{}

	void Update()override;
	void PostUpdate()override;
	void Draw();
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;
	void Init()override;

	void ActionON() { m_actionFlg = true; }
	void ActionOFF() { m_actionFlg = false; }
	void ReStart();

	void SetGimmickList(std::vector<std::shared_ptr<GimmickBase>> a_GimmickList) { m_GimmickList = a_GimmickList; }
	void SetBulletList(std::vector<std::shared_ptr<KdGameObject>> a_BulletList) { m_BulletList = a_BulletList; }

	float GetAngleX()const { return m_angleX; }
	float GetAngleY()const { return m_angleY; }
	bool  GetGoal()  const { return m_goalFlg; }
	bool  GetGameOver()const { return m_gameOverFlg; }

private:
	std::shared_ptr<KdSquarePolygon> m_polygon;  //板ポリ
	Math::Vector3 m_pos;                         //座標
	Math::Vector3 m_move;                        //移動
	Math::Vector3 m_GmkMove;                     //ギミックの移動
	Math::Vector3 m_dir;                         //ベクトル
	Math::Vector3 m_size;                        //サイズ
	Math::Vector2 m_oldCursorPos;                //前のマウス座標
	float m_speed;                               //スピード
	float m_angleY;                              //角度
	float m_angleX;                              //角度
	float m_gravity;                             //重力
	bool  m_jumpFlg;                             //ジャンプフラグ
	bool  m_actionFlg;                           //行動可能フラグ
	bool  m_goalFlg;                             //ゴールフラグ
	bool  m_gameOverFlg;                         //ゲームオーバーフラグ

	Animation m_anime;  //アニメーション

	std::vector<std::shared_ptr<GimmickBase>> m_GimmickList;  //ギミックリスト　※当たり判定のため
	std::vector<std::shared_ptr<KdGameObject>> m_BulletList;  //弾リスト　※当たり判定のため

	bool m_air;
	bool m_keyFlg;
};