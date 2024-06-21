#pragma once

class Cloud :public KdGameObject
{
public:
	Cloud() { Init(); }
	~Cloud()override{}

	void Update()override;
	void DrawLit()override;
	void DrawBright()override;
	void Init()override;

	void SetPos(Math::Vector3 a_pos) { m_pos = a_pos; }
	void SetMove(Math::Vector3 a_move) { m_move = a_move; }
	void SetSize(float a_size) { m_size = a_size; }

private:
	std::shared_ptr<KdModelData> m_model;
	Math::Vector3                m_pos;
	Math::Vector3                m_move;
	float                        m_size;
};