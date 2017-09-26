//************************************************/
//* @file  :BUttonBase.cpp
//* @brief :ボタンの基底クラス
//* @date  :2017/09/26
//* @author:K.Yamamoto
//************************************************/

#include "ButtonBase.h"

#include <simplemath.h>

#include <SL_Texture.h>

#include "../../Game/Game.h"
#include "../../SL_Window.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"

ButtonBase::ButtonBase()
{
}

ButtonBase::~ButtonBase()
{
}

void ButtonBase::Draw(const Vector2& position) const 
{
	// 1. Show a simple window
	// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"

	static float f = 0.0f;
	bool show_test_window;
	bool show_another_window;
	ImGui::Text("Hello, world!");
	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
	float color[3] = { 0.0f,0.0f,1.0f };
	ImGui::ColorEdit3("clear color", (float*)&color);
	if (ImGui::Button("Test Window")) show_test_window ^= 1;
	if (ImGui::Button("Another Window")) show_another_window ^= 1;
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

	// 2. Show another simple window, this time using an explicit Begin/End pair
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);
		ImGui::Text("Hello from another window!");
		ImGui::End();
	}

	// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
	if (show_test_window)
	{
		ImGui::SetNextWindowPos(ImVec2(500, 20), ImGuiCond_FirstUseEver);     // Normally user code doesn't need/want to call it because positions are saved in .ini file anyway. Here we just want to make the demo initial state a bit more friendly!
		ImGui::ShowTestWindow(&show_test_window);
	}
}
