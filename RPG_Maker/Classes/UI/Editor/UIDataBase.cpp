//************************************************/
//* @file  :UIDataBase.cpp
//* @brief :UIDataBaseのクラス
//* @date  :2017/10/02
//* @author:K.Yamamoto
//************************************************/
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"
#include "UIDataBase.h"

using namespace std;

UIDataBase::UIDataBase(const string& name)
	:UIBase(name)
{
	m_uiList.resize(2);

	m_uiList[DATA_LIST::ENEMY] = make_unique<UIEnemyTable>(string("Enemy DataBase"));
	m_uiList[DATA_LIST::ENEMYGROUP] = make_unique<UIEnemyGroupTable>(string("Enemy DataBase"));

	m_uiList[DATA_LIST::ENEMYGROUP]->Active = false;

	m_enemyButton = std::make_unique<UIButton>("Enemy", bind(&UIDataBase::ChangeActive,this, DATA_LIST::ENEMY));
	m_enemyGroupButton = std::make_unique<UIButton>("Enemy Group", bind(&UIDataBase::ChangeActive,this, DATA_LIST::ENEMYGROUP));

}

UIDataBase::~UIDataBase()
{
}

void UIDataBase::DrawUpdate()
{

	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));
	ImGui::SetNextWindowPos(ImVec2(350.0f, 55.0f), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(1200, 860), ImGuiSetCond_Once);

	auto& style = ImGui::GetStyle();

	auto oldWindowPadding = style.WindowPadding;

	if (ImGui::Begin(m_name.c_str(), nullptr
		, ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoCollapse))
	{
		// Styleの設定
		auto oldFramePadding = style.FramePadding;

		style.FramePadding = ImVec2(3.0f, 2.0f);

		auto x = ImGui::GetCursorPosX();
		auto y = ImGui::GetCursorPosY();

		// ここから描画処理
		// Data切り替え用UI
		ImGui::NewLine();
		ImGui::SameLine(300.0f);
		UIACTIVEDRAW(m_enemyButton);
		ImGui::SameLine(400.0f);
		UIACTIVEDRAW(m_enemyGroupButton);

		for each(auto& ui in m_uiList)
		{
			UIACTIVEDRAW(ui);
		}

		ImGui::End();
		{
			style.FramePadding = oldFramePadding;
		}
	}
	style.WindowPadding = oldWindowPadding;

	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}

void UIDataBase::DrawImage()
{

}

void UIDataBase::ChangeActive(DATA_LIST data)
{
	for each(auto& ui in m_uiList) {
		ui->Active = false;
	}
	m_uiList[data]->Active = true;
}
