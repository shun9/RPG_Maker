//************************************************/
//* @file  :UIUnderBar.cpp
//* @brief :画面下部のバーUIクラス
//* @date  :2017/10/01
//* @author:K.Yamamoto
//************************************************/
#include <SL_Texture.h>
#include <vector>

#include "UIUnderBar.h"

using namespace ShunLib;
using namespace std;

UIUnderBar::UIUnderBar(const string& name)
	:UIBase(name)
{
}

UIUnderBar::~UIUnderBar()
{

}

void UIUnderBar::DataSetting(const std::string fileName, int x, int y)
{
}

void UIUnderBar::DrawUpdate(const std::string& fileName, int x, int y)
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
	ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 2.0f));
	ImGui::SetNextWindowPos(ImVec2(0, 906.0f), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(1764.0f, 30), ImGuiSetCond_Once);

	auto& style = ImGui::GetStyle();

	auto oldWindowPadding = style.WindowPadding;

	if (ImGui::Begin(m_name.c_str(), nullptr
		, ImGuiWindowFlags_NoTitleBar
		|ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoCollapse))
	{
		// Styleの設定
		auto oldFramePadding = style.FramePadding;

		style.FramePadding = ImVec2(3.0f, 4.0f);

		//フォントサイズ変更 
		ImGui::SetWindowFontScale(1.4f);

		ImGui::Text("");
		ImGui::SameLine(500);
		ImGui::Text("| File : %s", fileName.c_str());
		ImGui::SameLine(810);
		ImGui::Text("| %d , %d			|", x, y);

		style.FramePadding = oldFramePadding;

		ImGui::End();
	}

	style.WindowPadding = oldWindowPadding;

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}

