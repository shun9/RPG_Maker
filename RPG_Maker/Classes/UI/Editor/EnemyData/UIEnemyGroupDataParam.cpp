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

using namespace ShunLib;
using namespace std;

UIEnemyGroupDataParam::UIEnemyGroupDataParam(const string& name, EnemyGroupData* data)
	:UIBase(name)
	,m_data(data)
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
}

void UIEnemyGroupDataParam::DrawUpdate()
{
	if (!Active)return;
	//フォントサイズ変更 
	ImGui::SetWindowFontScale(1.4f);


}

void UIEnemyGroupDataParam::DrawImage()
{
	// 画像

}

