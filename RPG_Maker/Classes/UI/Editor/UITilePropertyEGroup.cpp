//************************************************/
//* @file  :UITileWindow.cpp
//* @brief :UI�^�C���E�C���h�E�̊��N���X
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
//	ImGui::BeginChild("Sub1", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 300), false, ImGuiWindowFlags_HorizontalScrollbar);

	if (ImGui::BeginChild("group", ImVec2(ImGui::GetWindowContentRegionWidth() * 1.0f, 280), true,ImGuiWindowFlags_NoTitleBar))
	{
		//ImGui::Text("kari");
		////�t�H���g�T�C�Y�ύX 
		//ImGui::SetWindowFontScale(1.4f);
		//for each (auto button in *m_groupList.get())
		//{
		//	// �ݒ肳��Ă���UI�̍X�V�`��
		//	button.second->DrawUpdate();
		//}
	}
	ImGui::EndChild();
}