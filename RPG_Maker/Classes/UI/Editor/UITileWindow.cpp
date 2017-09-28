//************************************************/
//* @file  :UITileWindow.cpp
//* @brief :UIタイルウインドウの基底クラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include <SL_Texture.h>

#include "../../Game/Game.h"
#include "../../SL_Window.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"
#include "UITileWindow.h"
#include <vector>

using namespace std;

UITileWindow::UITileWindow(const string& name)
	:UIBase(name)
{
	m_buttonList.push_back(make_shared<UIButton>(string("test")));
	for (int i = 0; i < 100; i++)
	{
		m_buttonList.push_back(make_shared<UIButton>(string("yaju_senpai")));
	}
}

UITileWindow::~UITileWindow()
{
}

void UITileWindow::DrawUpdate()
{
	UIDrawUpdate();
}

void UITileWindow::UIDrawUpdate()
{
	if (!m_isActive)return;

	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));
	ImGui::SetNextWindowPos(ImVec2(10, 60), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(330.0f, 700.0f), ImGuiSetCond_Once);

	auto& style = ImGui::GetStyle();

	auto oldWindowPadding = style.WindowPadding;
	style.WindowPadding = ImVec2(100.0f, 30.0f);

	if(ImGui::Begin(m_name.c_str(),nullptr
		,ImGuiWindowFlags_NoResize 
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoCollapse))
	{
		ImGui::SetWindowFontScale(2.0f);

		style.WindowPadding = oldWindowPadding;

		// Styleの設定
		auto oldFramePadding = style.FramePadding;
		style.FramePadding = ImVec2(10.0f, 10.0f);

		if(ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(185, 600), ImGuiWindowFlags_NoTitleBar))
		{
			//フォントサイズ変更 
			ImGui::SetWindowFontScale(1.4f);
			for each (auto ui in m_buttonList)
			{
				// 設定されているUIの更新描画
				ui->DrawUpdate();
			}
		}
		ImGui::EndChild();

		style.FramePadding = oldFramePadding;
	}
	ImGui::End();

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}