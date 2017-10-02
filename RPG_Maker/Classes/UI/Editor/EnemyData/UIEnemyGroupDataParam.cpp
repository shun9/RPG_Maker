//************************************************/
//* @file  :UIEnemyGroupDataParam.cpp
//* @brief :UIEnemyGroupDataParamクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include <SL_Texture.h>

#include "../../../imgui/imgui.h"
#include "../../../imgui/imgui_impl_dx11.h"
#include <vector>
#include <SL_Texture.h>
#include "UIEnemyGroupDataParam.h"
#include "../../../../Utils/ServiceManager.h"

using namespace ShunLib;
using namespace std;

UIEnemyGroupDataParam::UIEnemyGroupDataParam(const string& name, EnemyGroupData* data)
	:UIBase(name)
	, m_data(data)
	, m_groupAloneList(nullptr)
	, m_enemyAddButton(nullptr)
	, m_selectGroupID(-1)
	, m_selectGroupAloneID(-1)
	, m_selectEnemyID(-1)

{
	UIUpdate(data);

}

UIEnemyGroupDataParam::~UIEnemyGroupDataParam()
{
}

void UIEnemyGroupDataParam::SetID(int id)
{
}

void UIEnemyGroupDataParam::UIUpdate(EnemyGroupData* data)
{
	if (data == nullptr)return;
	m_data = data;

	if (m_nameInputBox == nullptr) m_nameInputBox = std::make_unique<UIInputStringBox>("name", &data->Name, (size_t)10);
	else m_nameInputBox.reset(new UIInputStringBox("name", &data->Name, (size_t)11));

	if (m_groupAloneList == nullptr) m_groupAloneList = make_unique<UIDataList<EnemyGroupAloneData>>(string(m_name));
	else m_groupAloneList.reset(new UIDataList<EnemyGroupAloneData>(string(m_name)));

	if (m_enemyAddButton == nullptr) m_enemyAddButton = make_unique<UIButton>(string("               Enemy Add               "));
	else m_enemyAddButton.reset(new UIButton(string("           Enemy Add           ")));

	m_enemyAddButton->SetPressEvent([this]() {
		AddEnemy();
		DataListIDUpdate();
	});

	m_groupAloneList->SetButtonUI(data->enemyList.GetList().size(), &data->enemyList.GetList());
	m_enemyList = make_unique<UIDataList<EnemyData>>("enemyList");
	m_enemyList->SetButtonUI(DB_Enemy.GetList().size(), &DB_Enemy.GetList());

	auto eData = DB_EnemyGroup.GetData(0);
	if (eData != nullptr)m_selectGroupID = 0;

	auto egaData = m_data->enemyList.GetData(0);
	if (egaData != nullptr)m_selectGroupAloneID = 0;

	auto egData = DB_Enemy.GetData(0);
	if (egData != nullptr)m_selectEnemyID = 0;
}

void UIEnemyGroupDataParam::DrawUpdate()
{
	if (!Active)return;
	//フォントサイズ変更 
	ImGui::SetWindowFontScale(1.4f);

	if (DB_Enemy.ChangeHolderCallBack()) m_enemyList->SetButtonUI(DB_Enemy.GetList().size(), &DB_Enemy.GetList());
	auto currentEnemyId = m_enemyList->ID();
	if (m_selectEnemyID != currentEnemyId)
	{
		m_enemyList->SetButtonUI(DB_Enemy.GetList().size(), &DB_Enemy.GetList());
		m_selectEnemyID = currentEnemyId;
	};


	// グループアローンID判定
	if (m_data->enemyList.ChangeHolderCallBack()) m_groupAloneList->SetButtonUI(m_data->enemyList.GetList().size(), &m_data->enemyList.GetList());
	auto currentGroupAloneId = m_groupAloneList->ID();
	if (m_selectGroupID != currentGroupAloneId)
	{
		m_groupAloneList->SetButtonUI(m_data->enemyList.GetList().size(), &m_data->enemyList.GetList());
		// 変わっている時
		m_selectGroupID = currentGroupAloneId;
	};


	auto x = ImGui::GetCursorPosX();
	auto y = ImGui::GetCursorPosY();

	float txtinitPos = 650.0f;
	float nextinitdir = 250.0f;

	// 名前入力欄設定
	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::SameLine(300);
	ImGui::Text("name :");
	ImGui::PushItemWidth(150.0f);
	ImGui::NewLine();
	ImGui::SameLine(300);
	UIACTIVEDRAW(m_nameInputBox);
	ImGui::PopItemWidth();

	// 画像
	ImGui::NewLine();
	ImGui::SameLine(300);

	// グループの設定された敵リスト
	if(m_groupAloneList!=nullptr)
		m_groupAloneList->DrawUpdate(1);

	// 追加ボタン
	ImGui::NewLine();
	ImGui::SameLine(300.0f);
	UIACTIVEDRAW(m_enemyAddButton);

	// 敵データリスト
	ImGui::SetCursorPos(ImVec2(x+600, y));
	ImGui::Text("ENEMY DATA :");
	ImGui::NewLine();
	ImGui::SameLine(x+600);
	UIACTIVEDRAW(m_enemyList);
}

void UIEnemyGroupDataParam::AddEnemy()
{
	if (GROUP_ENEMY_MAX <= m_data->enemyList.GetList().size())return;

	m_data->enemyList.AddData(SVC_Enemy->CreateEnemyGroupAloneData());

	m_groupAloneList->SetButtonUI(m_data->enemyList.GetList().size(), &m_data->enemyList.GetList());
}

void UIEnemyGroupDataParam::DrawImage()
{
	if (!Active)return;

}

