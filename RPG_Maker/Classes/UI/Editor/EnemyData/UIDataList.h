//************************************************/
//* @file  :UIDataList.h
//* @brief :UIDataListクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <vector>
#include <memory>
#include <map>
#include <string>
#include "../UIBase.h"
#include "../UIButton.h"
#include "../../../Data/DataBase.h"

template<class T>
class UIDataList :public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:
	std::vector<std::unique_ptr<T>>* m_holder;

	std::vector<std::unique_ptr<UIButton>> m_buttonList;

	int m_selectId = -1;
public:
	UIDataList(const std::string& name)
		:UIBase(name)
	{
	}

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UIDataList() override{}

	template<class D>
	void SetButtonUI(std::vector<std::unique_ptr<D>>* holder) {
		m_holder = holder;

		m_buttonList.resize(m_holder->size());
		m_buttonList.shrink_to_fit();

		for (int i = 0; i < (int)m_holder->size(); i++)
		{
			auto& list = *m_holder;
			auto* dataTmp = list[i].get();
			const auto* data = dynamic_cast<Data*>(dataTmp);
			char title[500];
			sprintf_s(title, u8"%d : %s", i, data->Name.c_str());
			auto bind = std::bind(&UIDataList<D>::SetID, this, i);
			if(!m_buttonList.at(i)) m_buttonList.at(i) = make_unique<UIButton>(title, bind,ShunLib::Vec2(230.0f,30.0f));
			else m_buttonList.at(i).reset(new UIButton(title, bind, ShunLib::Vec2(230.0f, 30.0f)));
		}

		m_selectId = m_holder->size() - 1;
	}

	virtual void DrawUpdate(int id = 0, ShunLib::Vec2 size = Vec2(250, 500))
	{
		if (!Active)return;

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.7f, 0.2f, 0.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));

		// ここから描画処理
		// リスト表示

		auto& style = ImGui::GetStyle();

		ImGui::BeginChild(id, ImVec2(size.m_x, size.m_y), ImGuiWindowFlags_NoTitleBar);
		//フォントサイズ変更 
		ImGui::SetWindowFontScale(1.4f);

		int i = 0;
		for each(auto& data in m_buttonList) {
			if (m_selectId == i)
			{
				ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
				m_buttonList[i]->DrawUpdate();
				ImGui::PopStyleColor();
			}
			else {
				m_buttonList[i]->DrawUpdate();
			}
			i++;
		}

		ImGui::EndChild();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();

		// TODO:並び替え
	}

	int ID() { return m_selectId; }
	void SetID(const int i) { m_selectId = i; }
};