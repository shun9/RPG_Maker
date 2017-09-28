//************************************************/
//* @file  :UITileProperty.cpp
//* @brief :UIタイルウインドウの基底クラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include <SL_Texture.h>

#include "../../Game/Game.h"
#include "../../SL_Window.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"
#include <vector>
#include "UITileProperty.h"

using namespace std;

UITileProperty::UITileProperty(const string& name)
	:UIBase(name)
	,m_isView(true)
{
	m_text = make_shared<UIText>("ID");
	//m_checkBoxIsMove = make_shared<UICheckBox>("IsMove");
}

UITileProperty::~UITileProperty()
{
}

void UITileProperty::DrawUpdate()
{
	UIDrawUpdate();
}

void UITileProperty::UIDrawUpdate()
{
	if (!m_isView)
	{
		m_isActive = false;
		m_isView = true;
	}

	if (!m_isActive)return;

	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));
	ImGui::SetNextWindowPos(ImVec2(880, 450), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(300, 310), ImGuiSetCond_Once);

	auto& style = ImGui::GetStyle();

	auto oldWindowPadding = style.WindowPadding;

	if(ImGui::Begin(m_name.c_str(),nullptr
		,ImGuiWindowFlags_NoResize 
		| ImGuiWindowFlags_NoCollapse))
	{

		// Styleの設定
		auto oldFramePadding = style.FramePadding;
	
		//フォントサイズ変更 
		ImGui::SetWindowFontScale(1.4f);
		
		m_text->DrawUpdate("ID %d", 1);
		//m_checkBoxIsMove->DrawUpdate();

		style.FramePadding = oldFramePadding;
	}
	
	ImGui::End();
	style.WindowPadding = oldWindowPadding;

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}