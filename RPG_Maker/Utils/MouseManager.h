//************************************************/
//* @file  :MouseManager.h
//* @brief :マウスの状態を管理するクラス
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
	// マウス
	unique_ptr<Mouse> m_mouse;

	// マウストラッカー
	Mouse::ButtonStateTracker m_tracker;

public:
	//更新処理
	void Update() {
		auto state = m_mouse->GetState();
		m_tracker.Update(state);
	}

	// マウスの座標を取得
	static Vector2 GetMousePosition()
	{
		float x = static_cast<float>(Mouse::Get().GetState().x);
		float y = static_cast<float>(Mouse::Get().GetState().y);
		return Vector2(x, y);
	}

	// ボタンを押されている間 true を返す
	bool GetMouseButton(MouseButton buttonNum)
	{
		Mouse::State mouseState = m_mouse->GetState();

		bool press = false;

		switch (buttonNum)
		{
		case leftButton:	// 左
			press = mouseState.leftButton;
			break;
		case rightButton:	// 右
			press = mouseState.rightButton;
			break;
		case middleButton:	// 真ん中
			press = mouseState.middleButton;
			break;
		default:
			assert(false);
			break;
		}

		return press;
	}

	// ボタンを押したフレームだけ true を返す
	bool GetMouseButtonDown(MouseButton buttonNum)
	{
		bool press = false;

		// 押された時
		Mouse::ButtonStateTracker::ButtonState checkState
			= Mouse::ButtonStateTracker::ButtonState::PRESSED;

		switch (buttonNum)
		{
		case leftButton:	// 左
			if (m_tracker.leftButton == checkState)
				press = true;
			break;
		case rightButton:	// 右
			if (m_tracker.rightButton == checkState)
				press = true;
			break;
		case middleButton:	// 真ん中
			if (m_tracker.middleButton == checkState)
				press = true;
			break;
		default:
			assert(false);
			break;
		}
		return press;
	}

	// ボタンを離したフレームだけ true を返す
	bool GetMouseButtonUp(MouseButton buttonNum)
	{
		bool press = false;
		// 離れたとき
		Mouse::ButtonStateTracker::ButtonState checkState
			= Mouse::ButtonStateTracker::ButtonState::RELEASED;

		switch (buttonNum)
		{
		case leftButton:	// 左
			if (m_tracker.leftButton == checkState)
				press = true;
			break;
		case rightButton:	// 右
			if (m_tracker.rightButton == checkState)
				press = true;
			break;
		case middleButton:	// 真ん中
			if (m_tracker.middleButton == checkState)
				press = true;
			break;
		default:
			assert(false);
			break;
		}
		return press;
	}

	// マウスのスクロール値取得
	int GetMouseScrollWheelValue() { return DirectX::Mouse::Get().GetState().scrollWheelValue; }

	// マウスのスクロール値リセット
	void MouseScrollWheelValueReset() { DirectX::Mouse::Get().ResetScrollWheelValue(); }

	// Windows procedure 用　メッセージ
	static void ProcessMessage(const UINT& message, const WPARAM& wParam, const LPARAM& lParam)
	{
		// マウス関係のメッセージ
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
