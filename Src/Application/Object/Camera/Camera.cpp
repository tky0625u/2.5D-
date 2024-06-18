#include "Camera.h"

void Camera::Update()
{
	//行列更新=================================================================================================================
	Math::Matrix RotX = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(m_angleX));  //角度
	Math::Matrix RotY = Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_angleY));  //角度
	Math::Matrix Trans = Math::Matrix::CreateTranslation(m_pos);                                   //座標 (プレイヤーの少し前)
	Math::Matrix PlayerTrans = Math::Matrix::CreateTranslation(m_PlayerPos);                         //プレイヤー座標
	Math::Matrix Mat = RotX * Trans * RotY * PlayerTrans;                                          //行列合成
	//=========================================================================================================================
}

void Camera::Init()
{
	m_angleX = 0;
	m_angleY = 0;
	m_ViewingAngle = 60;
	m_pos = { 0,2,0 };
	m_PlayerPos = {};
}

void Camera::SetPlayerAngle(float a_PlayerAngleX, float a_PlayerAngleY)
{
	m_angleX = a_PlayerAngleX;
	m_angleY = a_PlayerAngleY;
}

void Camera::SetPlayerPos(Math::Vector3 a_PlayerPos)
{
	m_PlayerPos = a_PlayerPos;
}
