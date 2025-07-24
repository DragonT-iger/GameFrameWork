#pragma once
class Game : public NzWndBase
{
public:
	Game() = default;
	virtual ~Game() = default;

	bool Initialize();// NzWndBase 초기화 , Renderer 초기화
	void Run();
	void Release();

private:
	void LifeCycle(float deltaTime);
	void UpdateTime();

	// 윈도우 프로시저 재정의

	void OnResize(int width, int height) override;
	void OnClose() override;

	std::unique_ptr<GameTimer> m_timer;
};

