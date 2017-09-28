//************************************************/
//* @file  :UIMenu.cpp
//* @brief :UIMenu�̃N���X
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
		// �t�H���g�T�C�Y�ύX
		ImGui::SetWindowFontScale(2.0f);

		for each (auto item in *m_itemList.get())
		{
			// �ݒ肳��Ă���UI�̍X�V�`��
			item.second->DrawUpdate();
		}
		ImGui::EndMenu();
	}
}
