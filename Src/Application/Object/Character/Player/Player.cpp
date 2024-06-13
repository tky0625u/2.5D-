#include "Player.h"
#include"../../../WindowUI/WindowUI.h"
#include"../../../Scene/SceneManager.h"
#include"../../Gimmick/GimmickManager/GimmickManager.h"

void Player::Update()
{
	//行動=========================================================================================

	//移動===========================================================
	m_dir = Math::Vector3::Zero;
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_dir.z = 1.0f;
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_dir.z = -1.0f;
	}
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_dir.x = -1.0f;
		m_size.x = -3.0f;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_dir.x = 1.0f;
		m_size.x = 3.0f;
	}
	//===============================================================

	//ジャンプ=======================================================
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (!m_jumpFlg)  //空中ジャンプ防止
		{
			m_move.y += JUMP;   //※移動変数にジャンプ力を代入
			m_jumpFlg = true;  
		}
	}
	//===============================================================
	
	//視点移動=======================================================
	POINT CurSor;
	GetCursorPos(&CurSor);
	if (CurSor.x != 640 || CurSor.y!=360)
	{
		m_angleX += (CurSor.y - 360) * VP_SPEED;
		m_angleY += (CurSor.x - 640) * VP_SPEED;
	}
	SetCursorPos(640,360);

	//角度制御===================================
	if (m_angleX >= 90.0f)m_angleX = 90.0f; 
	if (m_angleX <= -90.0f)m_angleX = -90.0f;
	if (m_angleY > 360.0f)m_angleY -= 360.0f; 
	if (m_angleY < 0.0f)m_angleY += 360.0f;
	//===========================================

	//===============================================================

	//デバッグ用=====================================================
	if (GetAsyncKeyState('P') & 0x8000)
	{
		if (!m_keyFlg)
		{
			if (!m_air)
			{
				m_air = true;
				m_move.y = 0;
			}
			else { m_air = false; }
			m_keyFlg = true;
		}
	}
	else
	{
		m_keyFlg = false;
	}
	//===============================================================

	m_dir.Normalize();
	if(!m_air)m_move.y -= m_gravity;  //重力と跳ね返りを与える
	m_pos.y += m_move.y;              //高さ
	m_pos += m_GmkMove;               //ギミックの移動量を合わせる

	//前後=============================================================================================================
															   //      ↓*速度制御*↓     //                     前 右 後 左
	m_pos.z += cos(DirectX::XMConvertToRadians(m_angleY)) * (SPEED * m_dir.z);  //速度代入  1  0 -1  0=cos
	m_pos.x += sin(DirectX::XMConvertToRadians(m_angleY)) * (SPEED * m_dir.z);  //速度代入  0  1  0 -1=sin
	//=================================================================================================================
	//左右=============================================================================================================
	m_pos.z += -sin(DirectX::XMConvertToRadians(m_angleY)) * (SPEED * m_dir.x); //速度代入  0 -1  0  1=-sin
	m_pos.x += cos(DirectX::XMConvertToRadians(m_angleY)) * (SPEED * m_dir.x);  //速度代入  1  0 -1  0=cos
	//=================================================================================================================

	//デバッグ用=====================================================
	if (GetAsyncKeyState('R')&0x8000)ReStart();
	if (m_pos.y <= -50)m_pos = { 300.0f,50.0f,0.0f };
	//===============================================================

	//=============================================================================================

	//アニメーション===============================================================================
	int Anime[][WALK_MAX] = { { 0,1,2,3 }, { 4,5,6,7,8,9,10 } };  //アニメーション配列

	//移動=======================================
	if (m_move.x != 0 || m_move.z != 0)
	{
		if (m_anime.m_motion != WALK)
		{
			m_anime.m_motion = WALK;
			m_anime.m_AnimeCnt = 0.0f;
			m_anime.m_CntMAX = WALK_MAX;
		}
	}
	//===========================================

	//立ち=======================================
	else if (!m_jumpFlg)
	{
		if (m_anime.m_motion != IDOL)
		{
			m_anime.m_motion = IDOL;
			m_anime.m_AnimeCnt = 0.0f;
			m_anime.m_CntMAX = IDOL_MAX;
		}
	}
	//===========================================

	m_anime.m_AnimeCnt += ANIME;  //アニメーション
	if (m_anime.m_AnimeCnt >= m_anime.m_CntMAX)m_anime.m_AnimeCnt = 0.0f;  //最大値になったら最初に戻す

	m_polygon->SetUVRect(Anime[m_anime.m_motion][(int)m_anime.m_AnimeCnt], 0);
	//=============================================================================================

	//行列更新=====================================================================================
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);                                  //拡縮 S
	Math::Matrix Rot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angleY));  //回転 R
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);                             //座標 T
	m_mWorld = Scale * Rot * Trans;                                                          //行列合成
	//=============================================================================================
}

void Player::PostUpdate()
{
	//当たり判定===================================================================================



	//レイ判定=======================================================
	
	//レイ判定変数宣言=====================================
	KdCollider::RayInfo ray;                      //レイ判定用の変数作成
	ray.m_pos = m_pos;                            //レイのスタート地点
	ray.m_dir = Math::Vector3::Down;              //レイの方向
	ray.m_pos.y += 0.1f;                          //少し上から飛ばす
	float enableStepHight = 0.2f;                 //段差の許容範囲
	ray.m_pos.y += enableStepHight;               //許容範囲を加える
	ray.m_range = -(m_move.y) + enableStepHight;  //レイの長さ
	ray.m_type = KdCollider::Type::TypeGround;    //当たり判定したいタイプ

	//デバッグ表示
	Math::Color color = { 1,1,1,1 };
	m_pDebugWire->AddDebugLine(ray.m_pos, ray.m_dir, ray.m_range, color);
	//=====================================================

	//当たり判定===========================================

	//地面=======================================
	std::list<KdCollider::CollisionResult> retRayGroundList;
	for (auto ground : SceneManager::Instance().GetObjList())
	{
		ground->Intersects(ray, &retRayGroundList);
	}
	//===========================================

	//ギミック===================================
	std::list<KdCollider::CollisionResult> retRayGmkList;  //当たったオブジェクトの情報を格納するリスト
	std::vector<std::shared_ptr<GimmickBase>> GimmickList; //当たったオブジェクト自体を格納するリスト
	int ListNum = 0;  //現在のリストの大きさを計測する変数
	for (auto gimmick : m_GimmickList)
	{
		gimmick->Intersects(ray, &retRayGmkList);  //当たり判定
		if (ListNum != retRayGmkList.size())       //前のリストの大きさと違っていたら=ギミックに当たっていたら
		{
			GimmickList.push_back(gimmick);  //当たったギミックを格納
			ListNum = retRayGmkList.size();  //リストの大きさを更新
		}
	}
	//===========================================

	//=====================================================

	//レイに当たったオブジェクトで一番近いものを検出
	m_GmkMove = Math::Vector3::Zero;
	float maxOverLap = 0;  //レイがはみ出た長さ
	Math::Vector3 hitPos;  //当たった座標
	bool RayHit = false;    //当たり判定フラグ

	//地面=================================================
	for (auto& ret : retRayGroundList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			RayHit = true;
		}
	}
	//=====================================================

	//ギミック=============================================
	Math::Vector3 move = Math::Vector3::Zero;  //移動量
	float bound = 0.0f;						   //跳ね返り
	int Cnt = 0;							   //現在がリストの何番目の処理をしているかを計測する変数
	for (auto& ret : retRayGmkList)
	{
		//はみ出た長さが一番長いものを探す
		if (maxOverLap < ret.m_overlapDistance)
		{
			//情報を上書き=======================
			maxOverLap = ret.m_overlapDistance;
			hitPos = ret.m_hitPos;
			move = GimmickList[Cnt]->GetMove();    //移動量を上書き
			bound = GimmickList[Cnt]->GetBound();  //跳ね返りを上書き
			//===================================

			RayHit = true;  //当たり判定フラグtrue
		}
		Cnt++;  //カウントを増やす
	}

	if (RayHit)
	{
		m_pos = hitPos + Math::Vector3{ 0.0f,-0.1f,0.0f };  //座標更新
		m_GmkMove = move;                                   //移動量を更新
		m_move.y = bound;                                   //跳ね返りに更新
		m_jumpFlg = false;                                  //ジャンプフラグfalse
	}
	else
	{
		m_jumpFlg = true;
	}
	//=====================================================

	//===============================================================

	//球判定=========================================================
	KdCollider::SphereInfo sphere;                                              //球判定用の変数作成
	sphere.m_sphere.Center = { m_pos.x,m_pos.y + 1.5f,m_pos.z };                //球の中心
	sphere.m_sphere.Radius = 1.5f;                                              //球の半径
	sphere.m_type = KdCollider::Type::TypeBump;  //当たり判定したいタイプ

	//デバッグ用
	m_pDebugWire->AddDebugSphere(sphere.m_sphere.Center, sphere.m_sphere.Radius, color);

	std::list<KdCollider::CollisionResult> retSphereList;                           //当たったオブジェクトの情報を格納するリスト
	for (auto obj : SceneManager::Instance().GetObjList())obj->Intersects(sphere,&retSphereList);
	for (auto gimmick : m_GimmickList)gimmick->Intersects(sphere, &retSphereList);  //ギミック
	for (auto bullet : m_BulletList)bullet->Intersects(sphere, &retSphereList);     //弾

	//球に当たったもので一番近いものを検出=================
	maxOverLap = 0;
	Math::Vector3 hitDir;
	bool SphereHit = false;
	for (auto& ret : retSphereList)
	{
		if (maxOverLap < ret.m_overlapDistance)
		{
			maxOverLap = ret.m_overlapDistance;
			hitDir = ret.m_hitDir;
			SphereHit = true;
		}
	}
	//=====================================================

	if (SphereHit)
	{
		if (RayHit)
		{
			hitDir.y = 0.0f;
		}
		else
		{
			m_move.y = 0.0f;
		}
		hitDir.Normalize();

		if (fabs(hitDir.y) > fabs(hitDir.x) && fabs(hitDir.y) > fabs(hitDir.z))m_jumpFlg = false;

		m_pos += hitDir * maxOverLap;
	}
	//===============================================================

	//=============================================================================================
}

void Player::Draw()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_polygon, m_mWorld);
}

void Player::GenerateDepthMapFromLight()
{
	Draw();
}

void Player::Init()
{
	SetCursorPos(640, 360);

	m_polygon = std::make_shared<KdSquarePolygon>();
	m_polygon->SetMaterial("Asset/Textures/Character/Player/sheets/DinoSprites - doux.png");
	m_polygon->SetPivot(KdSquarePolygon::PivotType::Center_Bottom);
	m_polygon->SetSplit(24, 1);
	m_pos = { 300.0f,5,0 };
	m_move = Math::Vector3::Zero;
	m_GmkMove = Math::Vector3::Zero;
	m_dir = Math::Vector3::Zero;
	m_size = { 3.0f,3.0f,3.0f };
	m_oldCursorPos = { 640,360 };
	m_angleX = 0.0f;
	m_angleY = 90.0f;
	m_gravity = 0.05f;
	m_jumpFlg = false;

	//アニメーション
	m_anime.m_AnimeCnt = 0.0f;
	m_anime.m_CntMAX = IDOL_MAX;
	m_anime.m_motion = IDOL;

	//デバッグ用
	m_keyFlg = false;
	m_air = false;
	m_pDebugWire = std::make_unique<KdDebugWireFrame>();
}

void Player::ReStart()
{
	m_pos = { -50,0,0 };
}
