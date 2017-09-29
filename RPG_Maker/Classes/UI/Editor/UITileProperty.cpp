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
#include "../../Map/MapEditor.h"
#include "../../../Utils/ImageLoader.h"
#include <SL_Texture.h>

using namespace ShunLib;
using namespace std;

UITileProperty::UITileProperty(const string& name,int id)
	:UIBase(name)
	,m_isView(true)
{
	SetID(id);
	m_textureChangeButton = make_unique<UIButton>(" Change Image ");
	m_removeGroupButton = make_unique<UIButton>(" Remove ");
	m_addGroupButton = make_unique<UIButton>("  Add  ");

	{
		m_textureChangeButton->SetPressEvent([this]() {ChangeTexture(); });
	}
}

UITileProperty::~UITileProperty()
{
}

void UITileProperty::SetID(int id)
{
	m_currentTileId = id;
	if (0 <= id) UIUpdate();
}

void UITileProperty::UIUpdate()
{
	m_tileData = TileDataHolder::GetInstance()->GetData(m_currentTileId);
	m_encountSlider = make_unique<UISlider>(" ", &m_tileData->encountRate);
	m_checkBoxIsMove = make_unique<UICheckBox>(" ", &m_tileData->canMove);
	m_groupSlider = make_unique<UITilePropertyEGroup>("EnemyGroup");
}

void UITileProperty::DrawUpdate()
{
	UIDrawUpdate();
}

void UITileProperty::UIDrawUpdate()
{
	if (!m_isView)
	{
		Active = false;
		m_isView = true;
	}

	if (!Active)return;

	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));
	ImGui::SetNextWindowPos(ImVec2(1250, 415), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(400, 510), ImGuiSetCond_Once);

	auto& style = ImGui::GetStyle();

	auto oldWindowPadding = style.WindowPadding;

	if(ImGui::Begin(m_name.c_str(),nullptr
		,ImGuiWindowFlags_NoResize 
		| ImGuiWindowFlags_NoCollapse))
	{
		// Styleの設定
		auto oldFramePadding = style.FramePadding;
	
		style.FramePadding = ImVec2(3.0f, 4.0f);

		//フォントサイズ変更 
		ImGui::SetWindowFontScale(1.4f);

		ImGui::Text("ID :");
		ImGui::SameLine(110);
		ImGui::Text("%d", m_currentTileId);

		if (m_encountSlider)
		{
			ImGui::Text("Encount : ");
			ImGui::SameLine(110);
			m_encountSlider->DrawUpdate();
		}

		if (m_checkBoxIsMove)
		{
			ImGui::Text("MoveFlag : ");
			ImGui::SameLine(110);
			m_checkBoxIsMove->DrawUpdate();
		}

		if (m_groupSlider)
		{
			ImGui::Text("EnemyGroup : ");
			m_groupSlider->DrawUpdate();
		}

		ImGui::Text(" ");
		ImGui::SameLine(10);
		m_textureChangeButton->DrawUpdate();
		ImGui::SameLine(235);
		m_removeGroupButton->DrawUpdate();
		ImGui::SameLine(325);
		m_addGroupButton->DrawUpdate();

		style.FramePadding = oldFramePadding;
	
		ImGui::End();
	}
	
	style.WindowPadding = oldWindowPadding;

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}

void UITileProperty::IdObservation()
{
	int id = MapEditor::GetInstance()->Id();
	if ( id != m_currentTileId)
	{
		SetID(id);
	}
}

void UITileProperty::ChangeTexture()
{
	auto Il = ImageLoader::GetInstance();
	auto str = Il->OpenLoadingDialog();

	if (str.c_str() != wstring(L"Image\\"))
	{
		m_tileData->texture.reset();
		m_tileData->texture = make_unique<Texture>(str.c_str());
	}

}
