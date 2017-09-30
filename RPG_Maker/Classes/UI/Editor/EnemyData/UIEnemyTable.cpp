//************************************************/
//* @file  :UITileProperty.cpp
//* @brief :UIタイルウインドウの基底クラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include <SL_Texture.h>

#include "../../../imgui/imgui.h"
#include "../../../imgui/imgui_impl_dx11.h"
#include <vector>
#include <SL_Texture.h>
#include "UIEnemyTable.h"

using namespace ShunLib;
using namespace std;

UIEnemyTable::UIEnemyTable(const string& name)
	:UIBase(name)
	,m_isView(true)
{
}

UIEnemyTable::~UIEnemyTable()
{
}

void UIEnemyTable::SetID(int id)
{
}

void UIEnemyTable::UIUpdate()
{
}

void UIEnemyTable::DrawUpdate()
{
	if (!Active)return;

	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));
	ImGui::SetNextWindowPos(ImVec2(350.0f, 66.0f), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(898, 860), ImGuiSetCond_Once);

	auto& style = ImGui::GetStyle();

	auto oldWindowPadding = style.WindowPadding;

	if (ImGui::Begin(m_name.c_str(), nullptr
		, ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoCollapse))
	{
		// Styleの設定
		auto oldFramePadding = style.FramePadding;

		style.FramePadding = ImVec2(3.0f, 4.0f);

		//フォントサイズ変更 
		ImGui::SetWindowFontScale(1.4f);


		{
			style.FramePadding = oldFramePadding;
		}

		ImGui::End();
	}

	style.WindowPadding = oldWindowPadding;

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

}

