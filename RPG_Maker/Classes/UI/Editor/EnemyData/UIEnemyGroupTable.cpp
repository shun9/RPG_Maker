//************************************************/
//* @file  :UIEnemyGroupTable.cpp
//* @brief :UIEnemyGroupTableƒNƒ‰ƒX
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
	:UIBase(name)
	,m_selectId(-1)
{
	m_uiDataList = make_unique<UIDataList<EnemyGroupData>>(name);
	m_uiDataList->SetButtonUI(DB_EnemyGroup.GetList().size(), &DB_EnemyGroup);

	auto data = DB_EnemyGroup.GetData(0);
	m_uiDataParam = make_unique<UIEnemyGroupDataParam>("param", data);
	if (data != nullptr)m_selectId = 0;

	m_uiDataList->SetAddButtonFunc([this]() {
		ParamUpdate(DB_EnemyGroup.AddData(SVC_Enemy->CreateEnemyGroupData()));
	});
}

UIEnemyGroupTable::~UIEnemyGroupTable()
{
}

void UIEnemyGroupTable::DrawUpdate()
{
	if (!Active)return;
	if (DB_EnemyGroup.ChangeHolderCallBack()) m_uiDataList->SetButtonUI(DB_EnemyGroup.GetList().size(), &DB_EnemyGroup);

	auto currentId = m_uiDataList->ID();
	if (m_selectId != currentId)
	{
		m_uiDataParam->UIUpdate(DB_EnemyGroup.GetData(currentId));
		m_selectId = currentId;
	};

	auto x = ImGui::GetCursorPosX();
	auto y = ImGui::GetCursorPosY();

	m_uiDataList->DrawUpdate();
	ImGui::SetCursorPos(ImVec2(x, y));
	m_uiDataParam->DrawUpdate();

}

void UIEnemyGroupTable::DrawImage()
{
	m_uiDataParam->DrawImage();
}

