#pragma once

class Particle;
class ButtomBase;

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

	void SetButtom(std::vector<std::shared_ptr<ButtomBase>> a_buttomList) { m_buttomList = a_buttomList; }

	const Math::Vector2 GetMousePos()const { return Math::Vector2{ float(cursor.x - 640),float(cursor.y - 360) * -1 }; }
	bool GetKeyFlg()const { return m_keyFlg; }

private:
	POINT           cursor;
	Math::Vector2   m_pos;
	Math::Rectangle m_rect;
	float           m_size;
	bool            m_cursorFlg;
	bool            m_keyFlg;
	KdTexture       m_Tex;

	static const int ParticleNUM = 5;
	std::shared_ptr<KdTexture>                 m_particleTex;
	std::vector<std::shared_ptr<KdGameObject>> m_ptlList;
	std::vector<std::shared_ptr<ButtomBase>> m_buttomList;
};