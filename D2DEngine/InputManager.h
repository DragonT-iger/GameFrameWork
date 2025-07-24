#pragma once
#include <array>

/// 날짜 / 이름 / 수정내용
/// 2025-07-09 최초버전 작성중
/// 
/// <summary>
/// 엔진에서 기반으로 쓸 InputManager 
/// <summary>



struct MouseState
{
	POINT pos{ 0, 0 };// 마우스 포지션

	bool LButtonPressed{ false };	// 마우스 왼쪽 버튼 눌림 상태
	bool RButtonPressed{ false };	// 마우스 오른쪽 버튼 눌림 상태
};

struct KeyEdge
{
	bool pressed{ false };	// 눌림 상태	
	bool released{ false };	// 평소 상태	
};

class InputManager	//싱글톤으로 쓸거임
{
	InputManager() = default;

	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
public:
	virtual ~InputManager() = default;

	static InputManager& Instance()
	{
		static InputManager instance;

		return instance;
	}

	bool Init(HWND hwnd);

	bool OnHandleMessage(const MSG& msg);

	bool GetKeyPressed(Keycode vk);

	bool GetKeyDown(Keycode vk);

	MouseState GetMouseState() const { return m_CurMouse; }

private:

	void HandleMsgKeyDown(WPARAM wParam, LPARAM lParam);

	void HandleMsgKeyUp(WPARAM wParam, LPARAM lParam);

	void HandleMsgMouse(const MSG& msg);

	MouseState m_CurMouse;	// 현재 마우스 상태

	std::array<bool, 256> m_keyDown;	// 현재 Down 상태
	std::array<KeyEdge, 256> m_keyEdge;	// 이번 프레임 Edge 결과
};

inline int GetXFromLParam(LPARAM lp) { return (int)(short)(LOWORD(lp)); }
inline int GetYFromLParam(LPARAM lp) { return (int)(short)(HIWORD(lp)); }

inline InputManager& Input = InputManager::Instance();