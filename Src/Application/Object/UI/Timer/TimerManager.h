#pragma once

class Timer;

#define SECOND 60
#define DEFAULT 4
#define MAXNUM  10
#define MINUTENUM 6

class TimerManager :public KdGameObject
{
public:
	TimerManager() { Init(); }
	~TimerManager()override{}

	void Update()override;
	void DrawSprite()override;
	void Init()override;

private:
	std::vector<std::shared_ptr<Timer>> m_timerList;
	int m_frame;

	Math::Vector2   m_pos;
	Math::Color     m_color;
	Math::Rectangle m_rect;
	KdTexture       m_Tex;

	KdTexture       m_timerTex;
};