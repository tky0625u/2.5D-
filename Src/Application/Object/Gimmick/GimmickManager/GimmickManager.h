﻿#pragma once

class Cannon;

class GimmickManager :public KdGameObject
{
public:
	GimmickManager() { Init(); }
	~GimmickManager()override{}

	void Update()override;
	void PostUpdate()override;
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;
	void Init()override;

	void SetCameraPos(Math::Vector3 a_cameraPos) { m_cameraPos = a_cameraPos; }

private:
	std::vector<std::shared_ptr<KdGameObject>> m_GimmickList;  //リスト
	
	static const int CANNONNUM = 3;
	std::weak_ptr<Cannon>                      m_cannon[CANNONNUM];       //大砲　※弾の削除処理のため
	Math::Vector3                              m_cameraPos;    //カメラ座標
};