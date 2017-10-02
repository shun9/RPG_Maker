//************************************************/
//* @file  :UIDataList.h
//* @brief :UIDataList�N���X
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
	DataHolder<T>* m_holder;

	std::vector<std::unique_ptr<UIButton>> m_buttonList;

	std::unique_ptr<UIButton> m_addButton;
	std::unique_ptr<UIButton> m_removeButton;

	int m_selectId = -1;
public:
	UIDataList(const std::string& name)
		:UIBase(name)
	{
		m_addButton = std::make_unique<UIButton>("                  Add                  ");
	}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~UIDataList() override{}

	template<class D>
	void SetButtonUI(int size, DataHolder<D>* holder) {
		m_holder = holder;

		m_buttonList.resize(size);
		for (int i = 0; i < size; i++)
		{
			auto* dataTmp = m_holder->GetData(i);
			const auto* data = dynamic_cast<Data*>(dataTmp);
			char title[24];
			sprintf_s(title, "%d : %s", i, data->Name.c_str());
			auto bind = std::bind(&UIDataList<D>::SetID, this, i);
			m_buttonList[i] = make_unique<UIButton>(title, bind);
		}
	}

	virtual void DrawUpdate() override
	{
		if (!Active)return;

		// ��������`�揈��
		// ���X�g�\��

		//�t�H���g�T�C�Y�ύX 
		ImGui::SetWindowFontScale(1.4f);

		ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(250, 500), ImGuiWindowFlags_NoTitleBar);
		int i = 0;
		for each(auto& data in m_buttonList) {
			auto* dataTmp = m_holder->GetData(i);
			const auto* data = dynamic_cast<Data*>(dataTmp);
			char title[24];
			sprintf_s(title, "ID %d : %s", i, data->Name.c_str());
			m_buttonList[i]->DrawUpdate(title);
			i++;
		}

		ImGui::EndChild();

		ImGui::NewLine();
		// �ǉ��{�^��
		ImGui::SameLine(12.0f);
		m_addButton->DrawUpdate();

		// TODO:���ёւ�
	}

	int ID() { return m_selectId; }
	void SetID(const int i) { m_selectId = i; }

	void SetAddButtonFunc(std::function<void()> func) {
		m_addButton->SetPressEvent(func);
		m_selectId = m_holder->GetList().size() - 1;
	}
};