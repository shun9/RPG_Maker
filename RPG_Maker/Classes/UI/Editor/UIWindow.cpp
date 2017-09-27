//************************************************/
//* @file  :UIWindow.cpp
//* @brief :ウインドウの基底クラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include <SL_Texture.h>

#include "../../Game/Game.h"
#include "../../SL_Window.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"
#include "UIWindow.h"

using namespace std;

UIWindow::UIWindow(const string& name, const Vector2 & windowSize)
	:UIBase(name)
	, m_windowSize(make_shared<ImVec2>(windowSize.m_x, windowSize.m_y))
{
	m_buttonList.push_back(make_shared<UIButton>(string("test")));
	m_buttonList.push_back(make_shared<UIButton>(string("test2")));
}

UIWindow::~UIWindow()
{
}

void UIWindow::DrawUpdate()
{
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));
	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(*m_windowSize.get(), ImGuiSetCond_Once);

	auto& style = ImGui::GetStyle();

	ImGui::Begin(m_name.c_str());

	for each (auto ui in m_buttonList)
	{
		// 設定されているUIの更新描画
		ui->DrawUpdate();
	}

	ImGui::End();

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}
