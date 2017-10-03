//************************************************/
//* @file  :UIEnemyDataParam.cpp
//* @brief :UIEnemyDataParamクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include <SL_Texture.h>

#include "../../../imgui/imgui.h"
#include "../../../imgui/imgui_impl_dx11.h"
#include <vector>
#include <SL_Texture.h>
#include "UIEnemyDataParam.h"

using namespace ShunLib;
using namespace std;

UIEnemyDataParam::UIEnemyDataParam(const string& name, EnemyData* data)
	:UIBase(name)
	,m_data(data)
{


	UIUpdate(data);
}

UIEnemyDataParam::~UIEnemyDataParam()
{
}

void UIEnemyDataParam::SetID(int id)
{
}

void UIEnemyDataParam::UIUpdate(EnemyData* data)
{
	if (data == nullptr)return;

	if (m_nameInputBox == nullptr) m_nameInputBox = std::make_unique<UIInputStringBox>("name", &data->Name, (size_t)10);
	else m_nameInputBox.reset(new UIInputStringBox("name", &data->Name, (size_t)11));

	m_paramInputBox.resize(EnemyData::Param::length);
	for (int i = 0; i < EnemyData::Param::length; i++) {
		char title[16];
		sprintf_s(title, "param_%d", i);
		m_paramInputBox[i] = make_unique<UIInputIntBox>(title, &data->Param[i]);
	}
}

void UIEnemyDataParam::DrawUpdate()
{
	if (!Active)return;

	if (m_data == nullptr)return;

	//フォントサイズ変更
	ImGui::SetWindowFontScale(1.4f);

	ImGui::NewLine();
	ImGui::NewLine();

	// 名前入力欄
	float txtinitPos = 650.0f;
	float nextinitdir = 250.0f;

	ImGui::SameLine(300);
	ImGui::Text("name :");

	ImGui::PushItemWidth(150.0f);
	// param
	ImGui::SameLine(txtinitPos);
	ImGui::Text("HP :");
	ImGui::SameLine(txtinitPos +nextinitdir);
	ImGui::Text("MP :");
	ImGui::NewLine();
	ImGui::SameLine(300);
	UIACTIVEDRAW(m_nameInputBox);
	ImGui::SameLine(txtinitPos);
	UIVECTORDRAW(m_paramInputBox, EnemyData::Param::HP);
	ImGui::SameLine(txtinitPos + nextinitdir);
	UIVECTORDRAW(m_paramInputBox, EnemyData::Param::MP);

	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::SameLine(txtinitPos);
	ImGui::Text("ATK :");
	ImGui::SameLine(txtinitPos + nextinitdir);
	ImGui::Text("DEF :");
	ImGui::NewLine();
	ImGui::SameLine(txtinitPos);
	UIVECTORDRAW(m_paramInputBox, EnemyData::Param::ATK);
	ImGui::SameLine(txtinitPos + nextinitdir);
	UIVECTORDRAW(m_paramInputBox, EnemyData::Param::DEF);

	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::SameLine(txtinitPos);
	ImGui::Text("DEX :");
	ImGui::SameLine(txtinitPos + nextinitdir);
	ImGui::Text("EVA :");
	ImGui::NewLine();
	ImGui::SameLine(txtinitPos);
	UIVECTORDRAW(m_paramInputBox, EnemyData::Param::DEX);
	ImGui::SameLine(txtinitPos + nextinitdir);
	UIVECTORDRAW(m_paramInputBox, EnemyData::Param::EVA);

	ImGui::NewLine();
	ImGui::NewLine();
	ImGui::SameLine(txtinitPos);
	ImGui::Text("EXP :");
	ImGui::SameLine(txtinitPos + nextinitdir);
	ImGui::Text("MONEY :");
	ImGui::NewLine();
	ImGui::SameLine(txtinitPos);
	UIVECTORDRAW(m_paramInputBox, EnemyData::Param::EXP);
	ImGui::SameLine(txtinitPos + nextinitdir);
	UIVECTORDRAW(m_paramInputBox, EnemyData::Param::MONEY);
	// Save 

	// cansel

}

void UIEnemyDataParam::DrawImage()
{
	// 画像

}

