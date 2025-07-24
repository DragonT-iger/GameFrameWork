#include "pch.h"
#include "InputManager.h"
#include <array>



bool InputManager::Init(HWND hwnd)
{
	//RAWINPUT �Ⱦ��Ÿ� ���� �� �� ���µ�
	return true;
}

bool InputManager::OnHandleMessage(const MSG& msg)
{
	switch (msg.message)// wParam�� ���� Ű����, lParam�� ���� Ű ���� ������ ������� 
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
	assert(wParam < 256); //wParam�� 0~255 ������ ���� ����

	bool wasPressed = (lParam & (1 << 30)) != 0; // lParam�� 30��° ��Ʈ�� ���� �������� ���θ� ��Ÿ��
	m_keyDown[wParam] = true;

	if (!wasPressed)
	{
		m_keyEdge[wParam].pressed = true; // ó�� ������ ���� true
	}

	m_keyEdge[wParam].released = false; //�������ϱ� false
}

void InputManager::HandleMsgKeyUp(WPARAM wParam, LPARAM lParam)
{
	assert(wParam < 256); //wParam�� 0~255 ������ ���� ����

	m_keyDown[wParam] = false;
	m_keyEdge[wParam].pressed = false;	//���� Ÿ�ֿ̹� false�ε� ������ �ڵ�� ���⼭ ���ϰ� GetKeyPressed���� ó���߾��� ���� �ٸ���?
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
