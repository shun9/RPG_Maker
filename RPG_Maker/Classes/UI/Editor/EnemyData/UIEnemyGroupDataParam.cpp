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
	, m_enemyDeleteButton(nullptr)
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

	if (m_nameInputBox == nullptr) m_nameInputBox = std::make_unique<UIInputStringBox>("name", &data->Name, (size_t)40);
	else m_nameInputBox.reset(new UIInputStringBox("name", &data->Name, (size_t)40));

	if (m_groupAloneList == nullptr) m_groupAloneList = make_unique<UIDataList<EnemyGroupAloneData>>(string(m_name));
	else m_groupAloneList.reset(new UIDataList<EnemyGroupAloneData>(string(m_name)));

	if (m_enemyAddButton == nullptr) m_enemyAddButton = make_unique<UIButton>(string("               Enemy Add               "));
	else m_enemyAddButton.reset(new UIButton(string("           Enemy Add           ")));

	m_enemyAddButton->SetPressEvent([this]() {
		AddEnemyAlone();
	});

	if (m_enemyDeleteButton == nullptr) m_enemyDeleteButton = make_unique<UIButton>(string("               Enemy Delete               "));
	else m_enemyDeleteButton.reset(new UIButton(string("           Enemy Delete           ")));

	m_enemyDeleteButton->SetPressEvent([this]() {
		DeleteEnemyAlone();
		DataListIDUpdate();
	});

	m_groupAloneList->SetButtonUI(&data->enemyList.GetList());
	m_enemyList = make_unique<UIDataList<EnemyData>>("enemyList");
	m_enemyList->SetButtonUI(&DB_Enemy.GetList());

	m_selectGroupAloneID = m_groupAloneList->ID();
	m_selectEnemyID = m_enemyList->ID();
}

void UIEnemyGroupDataParam::DrawUpdate()
{
	if (!Active)return;
	//フォントサイズ変更 
	ImGui::SetWindowFontScale(1.4f);

	if (DB_Enemy.ChangeHolderCallBack()) m_enemyList->SetButtonUI(&DB_Enemy.GetList());
	auto currentEnemyId = m_enemyList->ID();
	if (m_selectEnemyID != currentEnemyId)
	{
		m_enemyList->SetButtonUI(&DB_Enemy.GetList());
		m_selectEnemyID = currentEnemyId;
		m_enemyList->SetID(m_selectEnemyID);
	};

	// グループアローンID判定
	if (m_data->enemyList.ChangeHolderCallBack()) m_groupAloneList->SetButtonUI(&m_data->enemyList.GetList());
	auto currentGroupAloneId = m_groupAloneList->ID();
	if (m_selectGroupAloneID != currentGroupAloneId)
	{
		m_groupAloneList->SetButtonUI(&m_data->enemyList.GetList());
		// 変わっている時
		m_selectGroupAloneID = currentGroupAloneId;
		m_groupAloneList->SetID(m_selectGroupAloneID);
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

	// 削除ボタン
	ImGui::NewLine();
	ImGui::SameLine(300.0f);
	UIACTIVEDRAW(m_enemyDeleteButton);

	// 敵データリスト
	ImGui::SetCursorPos(ImVec2(x+600, y));
	ImGui::Text("ENEMY DATA :");
	ImGui::NewLine();
	ImGui::SameLine(x+600);
	UIACTIVEDRAW(m_enemyList);
}

void UIEnemyGroupDataParam::AddEnemyAlone()
{
	// 上限数いたら追加されない
	if (GROUP_ENEMY_MAX <= m_data->enemyList.GetList().size())return;

	// 追加
	m_data->enemyList.AddData(SVC_Enemy->CreateEnemyGroupAloneData(m_selectEnemyID));

	// ボタンUI作成
	m_groupAloneList->SetButtonUI(&m_data->enemyList.GetList());
}

bool UIEnemyGroupDataParam::DeleteEnemyAlone()
{
	// 削除
	m_data->enemyList.DeleteData(m_selectGroupAloneID);
	if (0 < m_selectGroupAloneID) m_selectGroupAloneID = 0;
	else m_selectGroupAloneID = -1;

	// ボタンUI作成
	m_groupAloneList->SetButtonUI(&m_data->enemyList.GetList());
	return true;
}


void UIEnemyGroupDataParam::DrawImage()
{
	if (!Active)return;

}

