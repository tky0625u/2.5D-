#pragma once

#define TIMERWIDESIZE 93   //横サイズ
#define TIMERHIGHTSIZE 50  //縦サイズ

class Timer:public KdGameObject
{
public:
	Timer() { Init(); }
	~Timer()override{}

	void PostUpdate()override;
	void DrawSprite()override;
	void Init()override;

	void Scroll() { m_cutX += TIMERWIDESIZE; }       //次の数字に変更
	void Reset() { m_cutX = 0; }                     //最初に戻す
	void SetPos(int Number,Math::Vector2 commaPos);  //座標指定
	void SetTexture(KdTexture* a_pTex) { m_pTex = a_pTex; }
	void SetSize(float a_size) { m_size = a_size; }

	const int GetCutX()const { return m_cutX; }      //切り取り範囲参照

private:
	Math::Vector2   m_pos;
	Math::Color     m_color;
	Math::Rectangle m_rect;
	Math::Matrix    m_Mat;
	KdTexture*      m_pTex;
	int             m_cutX;
	float           m_size;
};