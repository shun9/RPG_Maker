//************************************************/
//* @file  :UIButton.cpp
//* @brief :UIButtonのクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include <SL_Texture.h>

#include "../../Game/Game.h"
#include "../../SL_Window.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"
#include "UIButton.h"

using namespace std;

UIButton::UIButton(const string& name, std::function<void()> func)
	:UIBase(name)
{
	// 初期設定が無い場合デバッグ用イベント
	m_func = func ? func : [=]() {OutputDebugStringW(L"press button\n"); };
}

UIButton::~UIButton()
{
}

void UIButton::DrawUpdate()
{
	// ボタンの描画と押されたときの処理
	if (ImGui::Button(m_name.c_str())) {
		m_func();
	}
}
