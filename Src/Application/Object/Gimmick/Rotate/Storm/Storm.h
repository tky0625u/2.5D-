#pragma once
#include"../../GimmickBase/GimmickBase.h"

class Storm :public GimmickBase
{
public:
	Storm() { Init(); }
	~Storm()override{}

	void Update()override;
	void Init()override;

	void SetPos(Math::Vector3 a_pos) { m_CirclePos = a_pos; }

private:
	Math::Vector3 m_CirclePos;
	float         m_MoveAngle;

	std::shared_ptr<KdSoundInstance3D> m_instance;
};