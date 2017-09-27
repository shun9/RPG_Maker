//************************************************/
//* @file  :MouseManager.h
//* @brief :�}�E�X�̏�Ԃ��Ǘ�����N���X
//* @date  :2017/09/26
//* @author:K,Yamamoto
//************************************************/
#pragma once
#include <d3d11.h>
#include <mouse.h>
#include <vector>
#include <SL_Singleton.h>
#include <SL_Vec2.h>
namespace {
	using Mouse = DirectX::Mouse;
	using Vector2 = ShunLib::Vec2;
	using namespace ShunLib;
	using namespace std;
}

enum MouseButton
{
	leftButton = 0,
	rightButton = 1,
	middleButton = 2,
};

class MouseManager : public Singleton<MouseManager>
{
	friend Singleton<MouseManager>;

private:
	// �}�E�X
	unique_ptr<Mouse> m_mouse;

	// �}�E�X�g���b�J�[
	Mouse::ButtonStateTracker m_tracker;

public:
	//�X�V����
	void Update() {
		auto state = m_mouse->GetState();
		m_tracker.Update(state);
	}

	// �}�E�X�̍��W���擾
	static Vector2 GetMousePosition()
	{
		float x = static_cast<float>(Mouse::Get().GetState().x);
		float y = static_cast<float>(Mouse::Get().GetState().y);
		return Vector2(x, y);
	}

	// �{�^����������Ă���� true ��Ԃ�
	bool GetMouseButton(MouseButton buttonNum)
	{
		Mouse::State mouseState = m_mouse->GetState();

		bool press = false;

		switch (buttonNum)
		{
		case leftButton:	// ��
			press = mouseState.leftButton;
			break;
		case rightButton:	// �E
			press = mouseState.rightButton;
			break;
		case middleButton:	// �^��
			press = mouseState.middleButton;
			break;
		default:
			assert(false);
			break;
		}

		return press;
	}

	// �{�^�����������t���[������ true ��Ԃ�
	bool GetMouseButtonDown(MouseButton buttonNum)
	{
		bool press = false;

		// �����ꂽ��
		Mouse::ButtonStateTracker::ButtonState checkState
			= Mouse::ButtonStateTracker::ButtonState::PRESSED;

		switch (buttonNum)
		{
		case leftButton:	// ��
			if (m_tracker.leftButton == checkState)
				press = true;
			break;
		case rightButton:	// �E
			if (m_tracker.rightButton == checkState)
				press = true;
			break;
		case middleButton:	// �^��
			if (m_tracker.middleButton == checkState)
				press = true;
			break;
		default:
			assert(false);
			break;
		}
		return press;
	}

	// �{�^���𗣂����t���[������ true ��Ԃ�
	bool GetMouseButtonUp(MouseButton buttonNum)
	{
		bool press = false;
		// ���ꂽ�Ƃ�
		Mouse::ButtonStateTracker::ButtonState checkState
			= Mouse::ButtonStateTracker::ButtonState::RELEASED;

		switch (buttonNum)
		{
		case leftButton:	// ��
			if (m_tracker.leftButton == checkState)
				press = true;
			break;
		case rightButton:	// �E
			if (m_tracker.rightButton == checkState)
				press = true;
			break;
		case middleButton:	// �^��
			if (m_tracker.middleButton == checkState)
				press = true;
			break;
		default:
			assert(false);
			break;
		}
		return press;
	}

	// �}�E�X�̃X�N���[���l�擾
	int GetMouseScrollWheelValue() { return DirectX::Mouse::Get().GetState().scrollWheelValue; }

	// �}�E�X�̃X�N���[���l���Z�b�g
	void MouseScrollWheelValueReset() { DirectX::Mouse::Get().ResetScrollWheelValue(); }

	// Windows procedure �p�@���b�Z�[�W
	static void ProcessMessage(const UINT& message, const WPARAM& wParam, const LPARAM& lParam)
	{
		// �}�E�X�֌W�̃��b�Z�[�W
		switch (message)
		{
		case WM_ACTIVATEAPP:
		case WM_INPUT:
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONDOWN:
		case WM_RBUTTONUP:
		case WM_MBUTTONDOWN:
		case WM_MBUTTONUP:
		case WM_MOUSEWHEEL:
		case WM_XBUTTONDOWN:
		case WM_XBUTTONUP:
		case WM_MOUSEHOVER:
			Mouse::ProcessMessage(message, wParam, lParam);
			break;
		}
	}

private:
	MouseManager() {
		m_mouse = std::make_unique<DirectX::Mouse>();
	}

};
