//************************************************/
//* @file  :UIMenuBar.cpp
//* @brief :UIMenuBarのクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"
#include "UIMenuBar.h"

using namespace std;

UIMenuBar::UIMenuBar(const string& name)
	:UIBase(name)
{
	m_menuList = make_shared<map<string, shared_ptr<UIMenu>>>();
}

UIMenuBar::~UIMenuBar()
{
}

void UIMenuBar::SetMenuItemFunc(std::string menuKey, std::string itemKey, std::function<void()> func)
{
	auto& list = *m_menuList.get();
	if (!list[menuKey]) list[menuKey] = make_shared<UIMenu>(menuKey);
	auto& menu = list[menuKey]->GetItemList();
	menu[itemKey] = make_shared<UIMenuItem>(itemKey, func);
}

void UIMenuBar::DrawUpdate()
{
	if (!Active)return;

	ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.8f, 0.84f, 0.9f, 2.0f));
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 2.0f));
	ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.96f, 0.96f, 0.862f, 2.0f));

	ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.8f, 0.84f, 0.9f, 2.0f));

	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(1664.0f, 43), ImGuiSetCond_Once);

	// Styleの設定
	auto& style = ImGui::GetStyle();
	auto oldPadding = style.FramePadding;
	auto oldAlpha = style.Alpha;

	style.Alpha = 2.0f;
	style.FramePadding = ImVec2(10.0f, 1.0f);

	if(ImGui::Begin("config 1", nullptr
		, ImGuiWindowFlags_MenuBar 
		| ImGuiWindowFlags_ShowBorders
		| ImGuiWindowFlags_NoResize 
		| ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoMove))
	{
		ImGui::SetWindowFontScale(2.2f);

		if (ImGui::BeginMenuBar())
		{
			for each (auto menu in *m_menuList.get())
			{
				// 設定されているUIの更新描画
				menu.second->DrawUpdate();
			}
			ImGui::EndMenuBar();
		}
	}
	ImGui::End();

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	{
		// 設定したものを戻す
		style.Alpha = oldAlpha;
		style.FramePadding = oldPadding;
	}
}
