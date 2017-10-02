//************************************************/
//* @file  :UITileProperty.cpp
//* @brief :UIタイルウインドウの基底クラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include <SL_Texture.h>
#include <vector>

#include "UITileProperty.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"

#include "../../../Utils/ImageLoader.h"
#include "../../Map/MapEditor.h"
#include "../../Data/DataBase.h"
#include "../../Map/Tile.h"

using namespace ShunLib;
using namespace std;

UITileProperty::UITileProperty(const string& name)
	:UIBase(name)
	,m_tileData(nullptr)
{
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
	else UIErase();
}

void UITileProperty::UIUpdate()
{
	m_tileData = DB_Tile.GetData(m_currentTileId);
	m_encountSlider = make_unique<UISlider>(" ", &m_tileData->encountRate);
	m_checkBoxIsMove = make_unique<UICheckBox>(" ", &m_tileData->canMove);
	m_groupSlider = make_unique<UITilePropertyEGroup>("EnemyGroup");
}

void UITileProperty::UIErase()
{
	m_tileData = nullptr;
	m_encountSlider.release();
	m_encountSlider = nullptr;
	m_checkBoxIsMove.release();
	m_checkBoxIsMove = nullptr;
	m_groupSlider.release();
	m_groupSlider = nullptr;
}

void UITileProperty::DrawUpdate()
{
	UIDrawUpdate();
}

void UITileProperty::UIDrawUpdate()
{
	if (!Active)return;

	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));
	ImGui::SetNextWindowPos(ImVec2(1250, 415), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(400, 510), ImGuiSetCond_Once);

	auto& style = ImGui::GetStyle();

	auto oldWindowPadding = style.WindowPadding;

	if(ImGui::Begin(m_name.c_str(),nullptr
		, ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoCollapse))
	{
		// Styleの設定
		auto oldFramePadding = style.FramePadding;
	
		style.FramePadding = ImVec2(3.0f, 4.0f);

		//フォントサイズ変更 
		ImGui::SetWindowFontScale(1.4f);

		if (0 < m_currentTileId)
		{
			ImGui::Text("ID :");
			ImGui::SameLine(110);
			ImGui::Text("%d", m_currentTileId);
		}
		else 
		{
			ImGui::Text("ID :");
			ImGui::SameLine(110);
			ImGui::Text("No Data");
		}

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
	if (m_tileData == nullptr) return;

	auto Il = ImageLoader::GetInstance();
	auto str = Il->OpenLoadingDialog();

	if (str.c_str() != wstring(Tile::PATH))
	{
		m_tileData->texture.reset();
		m_tileData->texture = make_unique<Texture>(str.c_str());
	}

}
