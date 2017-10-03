//************************************************/
//* @file  :UIDataBase.cpp
//* @brief :UIDataBase‚ÌƒNƒ‰ƒX
//* @date  :2017/10/02
//* @author:K.Yamamoto
//************************************************/
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"
#include "UIDataBase.h"
#include "UIPlayer.h"

using namespace std;

UIDataBase::UIDataBase(const string& name,Player* player)
	:UIBase(name)
{
	m_uiList.resize(3);

	m_uiList[DATA_LIST::PLAYER] = make_unique<UIPlayer>(player);
	m_uiList[DATA_LIST::ENEMY] = make_unique<UIEnemyTable>(string("Enemy DataBase"));
	m_uiList[DATA_LIST::ENEMYGROUP] = make_unique<UIEnemyGroupTable>(string("Enemy DataBase"));

	m_uiList[DATA_LIST::ENEMY]->Active = false;
	m_uiList[DATA_LIST::ENEMYGROUP]->Active = false;

	m_playerButton = std::make_unique<UIButton>("Player", bind(&UIDataBase::ChangeActive, this, DATA_LIST::PLAYER));
	m_enemyButton = std::make_unique<UIButton>("Enemy", bind(&UIDataBase::ChangeActive, this, DATA_LIST::ENEMY));
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
		// Style‚ÌÝ’è
		auto oldFramePadding = style.FramePadding;

		style.FramePadding = ImVec2(3.0f, 2.0f);

		auto x = ImGui::GetCursorPosX();
		auto y = ImGui::GetCursorPosY();

		// ‚±‚±‚©‚ç•`‰æˆ—
		// DataØ‚è‘Ö‚¦—pUI
		ImGui::NewLine();
		ImGui::SameLine(300.0f);
		UIACTIVEDRAW(m_playerButton);
		ImGui::SameLine(400.0f);
		UIACTIVEDRAW(m_enemyButton);
		ImGui::SameLine(500.0f);
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
