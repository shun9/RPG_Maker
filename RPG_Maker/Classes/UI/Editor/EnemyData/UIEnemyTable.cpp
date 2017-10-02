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
#include "../../../Data/DataBase.h"
#include "../../../../Utils/ServiceManager.h"

using namespace ShunLib;
using namespace std;

UIEnemyTable::UIEnemyTable(const string& name)
	:UIBase(name)
	,m_selectId(-1)
{
	m_uiDataList = make_unique<UIDataList<EnemyData>>(name);
	m_uiDataList->SetButtonUI(DB_Enemy.GetList().size(), &DB_Enemy.GetList());
	m_addButton = std::make_unique<UIButton>("                  Add                  ", [this]() {
		ParamUpdate(DB_Enemy.AddData(SVC_Enemy->CreateEnemyData()));
		DataListIDUpdate();
	});

	auto data = DB_Enemy.GetData(0);
	m_uiDataParam = make_unique<UIEnemyDataParam>("param", data);
	if (data != nullptr)m_selectId = 0;

}

UIEnemyTable::~UIEnemyTable()
{
}

void UIEnemyTable::DrawUpdate()
{
	if (!Active)return;
	if (DB_Enemy.ChangeHolderCallBack()) m_uiDataList->SetButtonUI(DB_Enemy.GetList().size(), &DB_Enemy.GetList());

	auto currentId = m_uiDataList->ID();
	if (m_selectId != currentId)
	{
		m_uiDataParam->UIUpdate(DB_Enemy.GetData(currentId));
		m_selectId = currentId;
	};

	auto x = ImGui::GetCursorPosX();
	auto y = ImGui::GetCursorPosY();

	m_uiDataList->DrawUpdate();

	// 追加ボタン
	ImGui::NewLine();
	ImGui::SameLine(12.0f);
	m_addButton->DrawUpdate();

	ImGui::SetCursorPos(ImVec2(x, y));
	m_uiDataParam->DrawUpdate();
}

void UIEnemyTable::DrawImage()
{
	m_uiDataParam->DrawImage();
}

