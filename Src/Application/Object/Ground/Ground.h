#pragma once

//地面
class Ground :public KdGameObject
{
public:
	Ground() { Init(); }
	~Ground()override{}

	void DrawLit()override;
	void Init()override;

private:

	std::shared_ptr<KdModelData> m_model = nullptr;  //モデル

};