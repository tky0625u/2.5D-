#pragma once

class GimmickBase :public KdGameObject
{
public:
	GimmickBase() {}
	~GimmickBase()override{}

	virtual void Update()override = 0;
	virtual void Draw();
	virtual void DrawLit()override;
	virtual void GenerateDepthMapFromLight()override;
	virtual void Init()override = 0;

	virtual const Math::Vector3 GetMove()const { return m_move; }

protected:
	std::shared_ptr<KdModelData> m_model;      //モデル
	Math::Vector3                m_pos;        //座標
	Math::Vector3                m_move;       //動き
	float                        m_size;       //大きさ
	float                        m_angle;      //角度
};