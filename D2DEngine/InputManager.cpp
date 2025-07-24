#include "pch.h"
#include "InputManager.h"
#include <array>



bool InputManager::Init(HWND hwnd)
{
	//RAWINPUT 안쓸거면 딱히 할 거 없는듯
	return true;
}

bool InputManager::OnHandleMessage(const MSG& msg)
{
	switch (msg.message)// wParam에 누른 키정보, lParam에 누른 키 상태 정보가 들어있음 
	{
	case WM_KEYDOWN:
	{
		HandleMsgKeyDown(msg.wParam, msg.lParam);
	}
	break;

	case WM_KEYUP:
	{
		HandleMsgKeyUp(msg.wParam, msg.lParam);
	}
	break;

	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	{
		HandleMsgMouse(msg);
	}
	break;

	default:
		return false; // Unhandled message
	}

	return true;
}

bool InputManager::GetKeyPressed(Keycode vk)
{
	bool p = m_keyEdge[static_cast<UINT>(vk)].pressed;

	return p;
}

bool InputManager::GetKeyDown(Keycode vk)
{
	return m_keyDown[static_cast<UINT>(vk)];
}

void InputManager::HandleMsgKeyDown(WPARAM wParam, LPARAM lParam)
{
	assert(wParam < 256); //wParam은 0~255 사이의 값이 들어옴

	bool wasPressed = (lParam & (1 << 30)) != 0; // lParam의 30번째 비트가 눌린 상태인지 여부를 나타냄
	m_keyDown[wParam] = true;

	if (!wasPressed)
	{
		m_keyEdge[wParam].pressed = true; // 처음 눌렸을 때만 true
	}

	m_keyEdge[wParam].released = false; //눌렸으니까 false
}

void InputManager::HandleMsgKeyUp(WPARAM wParam, LPARAM lParam)
{
	assert(wParam < 256); //wParam은 0~255 사이의 값이 들어옴

	m_keyDown[wParam] = false;
	m_keyEdge[wParam].pressed = false;	//때는 타이밍에 false인데 교수님 코드는 여기서 안하고 GetKeyPressed에서 처리했었음 뭐가 다른가?
	m_keyEdge[wParam].released = true;
}

void InputManager::HandleMsgMouse(const MSG& msg)
{
	int x = GetXFromLParam(msg.lParam);
	int y = GetYFromLParam(msg.lParam);

	m_CurMouse.pos = { x, y };

	if (msg.message == WM_LBUTTONDOWN)
	{
		m_CurMouse.LButtonPressed = true;
		SetCapture(msg.hwnd);
	}
	else if (msg.message == WM_RBUTTONDOWN)
	{
		m_CurMouse.RButtonPressed = true;
		SetCapture(msg.hwnd);
	}
	else if (msg.message == WM_LBUTTONUP)
	{
		m_CurMouse.LButtonPressed = false;
		ReleaseCapture();
	}
	else if (msg.message == WM_RBUTTONUP)
	{
		m_CurMouse.RButtonPressed = false;
		ReleaseCapture();
	}
}
