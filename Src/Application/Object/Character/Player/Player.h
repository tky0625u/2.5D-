#pragma once

#define SPEED 0.2f  //移動量
#define JUMP  1.0f  //ジャンプ力

class Player :public KdGameObject
{
public:
	Player() { Init(); }
	~Player()override{}

	void Update()override;
	void PostUpdate()override;
	void Draw();
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;
	void Init()override;

	void SetGimmickList(std::vector<std::shared_ptr<KdGameObject>> a_GimmickList) { m_GimmickList = a_GimmickList; }

private:
	std::shared_ptr<KdSquarePolygon> m_polygon;  //板ポリ
	Math::Vector3 m_pos;                         //座標
	Math::Vector3 m_move;                        //移動
	Math::Vector3 m_dir;                         //ベクトル
	Math::Vector3 m_size;                        //サイズ
	float m_angle;                               //角度
	float m_gravity;                             //重力
	bool  m_jumpFlg;                             //ジャンプフラグ

	std::vector<std::shared_ptr<KdGameObject>> m_GimmickList;  //ギミックリスト　※当たり判定のため
};