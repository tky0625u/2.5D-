#include "Cannon.h"
#include"../../../WindowUI/WindowUI.h"
#include"Bullet/Bullet.h"

void Cannon::Update()
{
	//発射=========================================================================================
	if (m_coolTime <= 0)
	{
		//弾===================================================================
		std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>();         //メモリ確保
		bullet->SetPos({m_pos.x+CorrectionX,m_pos.y+ CorrectionY,m_pos.z});  //座標格納
		bullet->SetAngle(m_angle);                                           //角度格納
		m_bulletList.push_back(bullet);                                      //リストに格納
		m_bullet = bullet;                                                   //変数に代入
		//=====================================================================
	}

	for (auto bullet : m_bulletList)bullet->Update();  //弾更新
	//=============================================================================================

	//行列更新=====================================================================================
	Math::Matrix Scale = Math::Matrix::CreateScale(m_size);                                    //拡縮
	Math::Matrix Rot = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angle));    //回転
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);                               //座標
	m_mWorld = Scale * Rot * Trans;                                                            //ワールド行列合成
	//=============================================================================================
}

void Cannon::PostUpdate()
{
	//弾===========================================================================================
	
	//後更新===================================================================
	for (auto bullet : m_bulletList)
	{
		bullet->SetCameraPos(m_cameraPos);  //カメラ座標格納
		bullet->PostUpdate();               //後更新
	}
	//=========================================================================

	//リスト削除===============================================================
	std::vector<std::shared_ptr<Bullet>>::iterator it = m_bulletList.begin();
	while (it != m_bulletList.end())
	{
		const bool m_bFlg = (*it)->IsExpired();
		if (m_bFlg)  //存在消滅フラグがオンだったら削除
		{
			it = m_bulletList.erase(it);
		}
		else
		{
			it++;
		}
	}
	//=========================================================================

	//=============================================================================================

	//クールタイム=================================================================================
	m_coolTime--;                        //クールタイム減少
	if (m_coolTime <= 0)m_coolTime = 0;  //0以下にならない
	//=============================================================================================
}

void Cannon::Draw()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_model, m_mWorld);
}

void Cannon::DrawLit()
{
	Draw();

	//弾===========================================================================================
	for (auto bullet : m_bulletList)bullet->DrawLit();
	//=============================================================================================
}

void Cannon::GenerateDepthMapFromLight()
{
	Draw();

	//弾===========================================================================================
	for (auto bullet : m_bulletList)bullet->GenerateDepthMapFromLight();
	//=============================================================================================
}

void Cannon::Init()
{
	m_model = std::make_shared<KdModelData>();
	m_model->Load("Asset/Models/Cannon/Cannon.gltf");
	m_pos = { 180.0f,0.0f,10.0f };
	m_size = 2.5f;
	m_angle = 180.0f;
}

void Cannon::CoolTimeUP()
{
	m_coolTime += COOL_TIME;
}

void Cannon::SetPos(int i)
{
	m_pos.x += CANNONDISTANS * i;
}
