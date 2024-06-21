#pragma once

//アニメーション=================================
#define IDOL 0
#define IDOL_MAX 4
//===============================================

class ResultPlayer :public KdGameObject
{
public:
	ResultPlayer() { Init(); }
	~ResultPlayer()override{}

	struct Animation
	{
		int m_CntMAX;
		float m_AnimeCnt;
	};

	void Update()override;
	void PostUpdate()override;
	void Draw();
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;
	void Init()override;

	void SetGameOver(bool a_gameOverFlg) { m_gameOverFlg = a_gameOverFlg; }

private:
	std::shared_ptr<KdSquarePolygon> m_polygon;  //板ポリ
	Math::Vector3 m_pos;                         //座標
	Math::Vector3 m_size;                        //サイズ
	Math::Vector3 m_move;                        //移動
	float m_angleY;                              //角度
	float m_angleX;                              //角度
	float m_angleZ;                              //角度
	float m_angleMove;                           //角度変化
	float m_gravity;                             //重力
	bool  m_jumpFlg;                             //ジャンプフラグ
	bool  m_gameOverFlg;

	Animation m_anime;  //アニメーション

};