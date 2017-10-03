//************************************************/
//* @file  :UIEnemyGroupTable.cpp
//* @brief :UIEnemyGroupTableクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include <SL_Texture.h>

#include "../../../imgui/imgui.h"
#include "../../../imgui/imgui_impl_dx11.h"
#include <vector>
#include <SL_Texture.h>
#include "UIEnemyGroupTable.h"
#include "../../../Data/DataBase.h"
#include "../../../../Utils/ServiceManager.h"

using namespace ShunLib;
using namespace std;

UIEnemyGroupTable::UIEnemyGroupTable(const string& name)
	:UITableBase(name)
	,m_selectId(-1)
	,m_uiDataParam(nullptr)
{
	m_uiDataList = make_unique<UIDataList<EnemyGroupData>>(name);
	m_uiDataList->SetButtonUI(&DB_EnemyGroup.GetList());


	m_addButton = std::make_unique<UIButton>("                  Add                  ", [this]() {
		ParamUpdate(DB_EnemyGroup.AddData(SVC_Enemy->CreateEnemyGroupData()));
		DataListIDUpdate();
	});

	auto data = DB_EnemyGroup.GetData(0);
	m_uiDataParam = make_unique<UIEnemyGroupDataParam>("param");
	if (!data)m_selectId = -1;
}

UIEnemyGroupTable::~UIEnemyGroupTable()
{
}

void UIEnemyGroupTable::DrawUpdate()
{
	if (!Active)return;
	if (DB_EnemyGroup.ChangeHolderCallBack()) m_uiDataList->SetButtonUI(&DB_EnemyGroup.GetList());

	auto currentId = m_uiDataList->ID();
	if (m_selectId != currentId)
	{
		//m_uiDataList->SetButtonUI(&DB_EnemyGroup.GetList());
		m_uiDataParam->UIUpdate(DB_EnemyGroup.GetData(currentId));
		m_selectId = currentId;
	};

	auto x = ImGui::GetCursorPosX();
	auto y = ImGui::GetCursorPosY();

	m_uiDataList->DrawUpdate(ImGui::GetID((void*)0));

	// 追加ボタン
	ImGui::NewLine();
	ImGui::SameLine(12.0f);
	UIACTIVEDRAW(m_addButton);

	if (currentId < 0) return;

	ImGui::SetCursorPos(ImVec2(x, y));
	UIACTIVEDRAW(m_uiDataParam);

}

void UIEnemyGroupTable::ParamUpdate(int id)
{
	if (m_uiDataParam == nullptr) m_uiDataParam = make_unique<UIEnemyGroupDataParam>("param");
	m_uiDataParam->UIUpdate(DB_EnemyGroup.GetData(id));
}

void UIEnemyGroupTable::DrawImage()
{
	if (!Active)return;
	m_uiDataParam->DrawImage();
}

