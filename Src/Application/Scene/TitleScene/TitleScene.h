#pragma once

#include"../BaseScene/BaseScene.h"

class TimerManager;
class BestTime;

class TitleScene : public BaseScene
{
public :

	TitleScene() { Init(); }
	~TitleScene() {}

	void Update()override;
	void PostUpdate()override;
	void DrawSprite()override;
	void Load(std::string a_filePath);

private :

	void Event() override;
	void Init() override;

	std::shared_ptr<TimerManager> m_timer;
	std::shared_ptr<BestTime>     m_best;
};
