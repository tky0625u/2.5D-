#pragma once

class Timer;

#define SECOND     60
#define DEFAULTNUM 4
#define MAXNUM     10
#define MINUTENUM  6

class TimerManager :public KdGameObject
{
public:
	TimerManager()
		:m_pos(0,360),
		 m_frame(0),
		 m_size(1.0f),
		 m_second(0),
		 m_default(DEFAULTNUM),
		 m_startFlg(false)
	{}
	~TimerManager()override{}

	void Update()override;
	void PostUpdate()override;
	void DrawSprite()override;
	void Init()override;

	void Random();
	void Scroll();
	void TimeNO();
	void StartON() { m_startFlg = true; }
	void StartOFF() { m_startFlg = false; }
	
	void SetPos(Math::Vector2 a_pos) { m_pos = a_pos; }
	void SetSize(float a_size) { m_size = a_size; }

	const unsigned int GetSize()const { return m_timerList.size(); }
	const int GetSecond()const { return m_second; }

private:
	std::vector<std::shared_ptr<Timer>> m_timerList;
	int m_frame;

	Math::Vector2   m_pos;
	Math::Color     m_color;
	Math::Rectangle m_rect;
	KdTexture       m_Tex;
	float           m_size;
	int             m_second;
	int             m_default;

	KdTexture       m_timerTex;
	bool            m_startFlg;
};