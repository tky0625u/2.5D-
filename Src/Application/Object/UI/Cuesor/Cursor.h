#pragma once

class Particle;

class Cursor :public KdGameObject
{
public:
	Cursor() { Init(); }
	~Cursor()override{}

	void Update()override;
	void PostUpdate()override;
	void DrawSprite()override;
	void Init()override;

	void FlgChange(bool Flg);

private:
	Math::Vector2   m_pos;
	Math::Rectangle m_rect;
	float           m_size;
	bool            m_cursorFlg;
	bool            m_keyFlg;
	KdTexture       m_Tex;

	static const int ParticleNUM = 5;
	std::shared_ptr<KdTexture>                 m_particleTex;
	std::vector<std::shared_ptr<KdGameObject>> m_ptlList;
};