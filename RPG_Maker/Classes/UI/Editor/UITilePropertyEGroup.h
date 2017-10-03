//************************************************/
//* @file  :UITilePropertyEGroup.h
//* @brief :UI�̃^�C���E�C���h�E�N���X
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <vector>
#include <memory>
#include <string>
#include "../../imgui/imgui.h"

#include "UICheckBox.h"

class UITilePropertyEGroup :public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:
	int m_currentId;

	std::vector<std::unique_ptr<UICheckBox>> m_buttonList;
	std::vector<std::unique_ptr<bool>> m_bool;
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UITilePropertyEGroup(const std::string& name, int id);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~UITilePropertyEGroup() override;

	virtual void DrawUpdate() override;

	void UIDrawUpdate();

	void Event(int i){}
};