#pragma once

class Particle :public KdGameObject
{
public:
	Particle() { Init(); }
	~Particle()override{}

	void Update()override;
	void DrawSprite()override;
	void Init()override;

	void SetTexture(std::shared_ptr<KdTexture> a_pTex) { m_pTex = a_pTex; }
	void Emit(Math::Vector2 a_pos, Math::Vector2 a_move, float a_size, int a_lifespan); //パーティクル発生(放出)関数
	float Rnd() { return rand() / (float)RAND_MAX; }

private:
	Math::Vector2 m_pos;      //座標
	Math::Vector2 m_move;     //移動量
	Math::Rectangle m_rect;   //切り取り
	float         m_size;     //サイズ
	int           m_lifespan; //有効期限（活動限界時間）

	std::shared_ptr<KdTexture> m_pTex;        //テクスチャ(アドレス)

	Math::Vector2 m_cursorPos;
};