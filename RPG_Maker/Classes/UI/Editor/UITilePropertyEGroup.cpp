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
#include "../../Data/DataBase.h"

using namespace std;

UITilePropertyEGroup::UITilePropertyEGroup(const string& name, int id)
	:UIBase(name)
	, m_currentId(id)
{
	auto& holder = DB_EnemyGroup.GetList();;
	m_buttonList.resize(holder.size());
	m_buttonList.shrink_to_fit();
	m_bool.resize(holder.size());
	m_bool.shrink_to_fit();

	auto& group = DB_Tile.GetData(m_currentId)->enemyGroup;
	for (int i = 0; i < (int)holder.size(); i++)
	{
		auto& list = holder;
		auto* dataTmp = list[i].get();
		const auto* data = dynamic_cast<Data*>(dataTmp);
		char title[500];
		sprintf_s(title, u8"%d : %s", i, data->Name.c_str());
		m_bool.at(i) = make_unique<bool>(false);
		
		
		if (!m_buttonList.at(i)) m_buttonList.at(i) = make_unique<UICheckBox>(title, m_bool.at(i).get());
		else m_buttonList.at(i).reset(new UICheckBox(title, m_bool.at(i).get()));
	}
	for each (auto id in group) {
		*m_bool.at(id).get() = true;
	}
}

UITilePropertyEGroup::~UITilePropertyEGroup()
{
}

void UITilePropertyEGroup::DrawUpdate()
{
	UIDrawUpdate();
}

void UITilePropertyEGroup::UIDrawUpdate()
{
	int i = 0;
	vector<int> tmp;
	auto& group = DB_Tile.GetData(m_currentId)->enemyGroup;
	for each (auto& flag in m_bool)
	{
		for (auto itr = group.begin(); itr != group.end(); ++itr) {
			// 内部に存在するか確認	
			if (*itr != i) continue;

			// 存在する場合
			if (*flag.get()) continue;

			// false の時は削除
			group.erase(itr);
			group.shrink_to_fit();
			break;
		}
		// trueの時は追加
		if(*flag.get()) tmp.push_back(i);
		
		i++;
	}
	group.resize(tmp.size());
	group.shrink_to_fit();
	group = tmp;

	if (ImGui::BeginChild("group", ImVec2(250.0f, 280.0f), true,ImGuiWindowFlags_NoTitleBar))
	{
		int i = 0;
		for each(auto& data in m_buttonList) {
			m_buttonList[i]->DrawUpdate();
			i++;
		}
	}
	ImGui::EndChild();
}