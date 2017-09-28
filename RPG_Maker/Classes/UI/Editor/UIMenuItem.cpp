//************************************************/
//* @file  :UIMenuItem.cpp
//* @brief :UIMenuItemのクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include "../../SL_Window.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"
#include "UIMenuItem.h"

using namespace std;

UIMenuItem::UIMenuItem(const string& name, std::function<void()> func)
	:UIBase(name)
{
	// 初期設定が無い場合デバッグ用イベント
	m_func = func ? func : [=]() {OutputDebugStringW(L"press button\n"); };
}

UIMenuItem::~UIMenuItem()
{
}

void UIMenuItem::DrawUpdate()
{
	if (ImGui::MenuItem(m_name.c_str())) {
		m_func();
	}
}
