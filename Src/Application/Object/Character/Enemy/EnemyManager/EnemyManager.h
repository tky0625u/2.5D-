#pragma once

class EnemyManager :public KdGameObject
{
public:
	EnemyManager() { Init(); }
	~EnemyManager()override{}

	void PreUpdate()override;
	void Update()override;
	void Draw();
	void DrawLit()override;
	void GenerateDepthMapFromLight()override;
	void Init()override;

	void SetPlayerPos(Math::Vector3 a_PlayerPos) { m_PlayerPos = a_PlayerPos; }

private:
	Math::Vector3 m_PlayerPos;  //プレイヤー座標
};