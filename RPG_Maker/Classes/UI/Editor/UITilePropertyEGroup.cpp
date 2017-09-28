//************************************************/
//* @file  :UITileWindow.cpp
//* @brief :UIタイルウインドウの基底クラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include <SL_Texture.h>

#include "../../Game/Game.h"
#include "../../SL_Window.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"
#include "UITilePropertyEGroup.h"
#include <vector>

using namespace std;

UITilePropertyEGroup::UITilePropertyEGroup(const string& name)
	:UIBase(name)
{
	//m_groupList = make_shared<list<int, shared_ptr<UIButton>>>();
}

UITilePropertyEGroup::~UITilePropertyEGroup()
{
}

void UITilePropertyEGroup::AddGroup(int id)
{
	//auto& list = *m_groupList.get();
	//list.push_back(make_shared<UIButton>(buttonKey, func));
}

void UITilePropertyEGroup::DrawUpdate()
{
	UIDrawUpdate();
}

void UITilePropertyEGroup::UIDrawUpdate()
{
	if (ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(280, 100), ImGuiWindowFlags_NoTitleBar))
	{
		////フォントサイズ変更 
		//ImGui::SetWindowFontScale(1.4f);
		//for each (auto button in *m_groupList.get())
		//{
		//	// 設定されているUIの更新描画
		//	button.second->DrawUpdate();
		//}
		ImGui::EndChild();
	}
}