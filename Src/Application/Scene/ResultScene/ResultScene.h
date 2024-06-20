#pragma once

#include"../BaseScene/BaseScene.h"

class TimerManager;

class ResultScene : public BaseScene
{
public:

	ResultScene() { Init(); }
	~ResultScene() {}

	void Update()override;
	void PostUpdate()override;
	void DrawSprite()override;
	void Load(std::string a_filePath);
	void BestWrite(std::string a_filePath,int Time);

private:

	void Event() override;
	void Init() override;

	std::shared_ptr<TimerManager> m_timer;
	int                           m_ResultTime;
	int                           m_frame;
	bool                          m_ramdomFlg;
	bool                          m_ramdomSoundFlg;
	bool                          m_StopSoundFlg;
};