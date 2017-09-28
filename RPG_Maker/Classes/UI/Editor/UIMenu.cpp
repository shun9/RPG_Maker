//************************************************/
//* @file  :UIMenu.cpp
//* @brief :UIMenuのクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"
#include "UIMenu.h"

using namespace std;

UIMenu::UIMenu(const string& name)
	:UIBase(name)
{
	m_itemList = make_shared<map<string, shared_ptr<UIMenuItem>>>();
}

UIMenu::~UIMenu()
{
}

void UIMenu::DrawUpdate()
{
	if (ImGui::BeginMenu(m_name.c_str()))
	{
		// フォントサイズ変更
		ImGui::SetWindowFontScale(2.0f);

		for each (auto item in *m_itemList.get())
		{
			// 設定されているUIの更新描画
			item.second->DrawUpdate();
		}
		ImGui::EndMenu();
	}
}
