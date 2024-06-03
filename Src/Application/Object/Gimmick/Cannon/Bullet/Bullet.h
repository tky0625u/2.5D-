#pragma once

#define BULLET_SPEED 0.5f  //弾のスピード

class Bullet :public KdGameObject
{
public:
	Bullet() { Init(); }
	~Bullet()override {}

	void Update()override;
	void PostUpdate()override;
	void Draw();
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;
	void Init()override;

	void SetPos(Math::Vector3 a_pos) { m_pos = a_pos; }
	void SetAngle(float a_angle) { m_angle = a_angle; }
	void SetCameraPos(Math::Vector3 a_cameraPos) { m_cameraPos = a_cameraPos; }

private:
	std::shared_ptr<KdModelData> m_model;  //モデル
	Math::Vector3                m_pos;    //座標
	Math::Vector3                m_move;   //移動
	float                        m_size;   //大きさ
	float                        m_angle;  //角度

	Math::Vector3                m_cameraPos;  //カメラ座標
};