#pragma once
#include"../GimmickBase/GimmickBase.h"

class GimmickBase;
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

	const std::vector<std::shared_ptr<GimmickBase>> GetGimmickList(){ return m_GimmickList; }
	const std::vector<std::shared_ptr<KdGameObject>> GetBulletList(){ return m_BulletList; }

private:
	std::vector<std::shared_ptr<GimmickBase>> m_GimmickList;  //リスト
	std::vector<std::shared_ptr<KdGameObject>> m_BulletList;   //弾リスト　※当たり判定用
	
	static const int CANNONNUM = 5;
	static const int POLENUM = 3;
	static const int BOARDNUM = 3;
	static const int TRAMPOLINENUM = 5;

	std::weak_ptr<Cannon>                      m_cannon[CANNONNUM];       //大砲　※弾の削除処理のため
	std::shared_ptr<KdModelData>               m_BulletModel;
	Math::Vector3                              m_cameraPos;    //カメラ座標
};