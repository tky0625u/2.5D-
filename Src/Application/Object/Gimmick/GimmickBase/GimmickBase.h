#pragma once

class GimmickBase :public KdGameObject
{
public:
	enum GimmickType
	{
		Normal,
		Bound
	};

	GimmickBase() {}
	~GimmickBase()override{}

	virtual void Update()override = 0;
	virtual void Draw();
	virtual void DrawLit()override;
	virtual void GenerateDepthMapFromLight()override;
	virtual void Init()override = 0;

	virtual const Math::Vector3 GetMove()const { return m_move; }
	virtual const float GetBound()const { return m_bound; }

	const GimmickType GetGmkType()const { return m_gmkType; }

protected:
	std::shared_ptr<KdModelData> m_model;                            //モデル
	Math::Vector3                m_pos = Math::Vector3::Zero;        //座標
	Math::Vector3                m_move = Math::Vector3::Zero;       //動き
	float                        m_size = 0.0f;                      //大きさ
	float                        m_angle = 0.0f;                     //角度
	float                        m_bound = 0.0f;                     //跳ね返り
	GimmickType                  m_gmkType = Normal;
};