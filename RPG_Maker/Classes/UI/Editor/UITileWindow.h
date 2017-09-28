//************************************************/
//* @file  :UITileWindow.h
//* @brief :UI�̃^�C���E�C���h�E�N���X
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <list>
#include <memory>
#include <string>
#include "../../imgui/imgui.h"

#include "UIButton.h"

class UITileWindow :public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:
	std::list<std::shared_ptr<UIBase>> m_buttonList;
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UITileWindow(const std::string& name);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~UITileWindow() override;

	virtual void DrawUpdate() override;

	void AddUI(std::shared_ptr<UIBase> ui) { m_buttonList.push_back(ui); }

	void UIDrawUpdate();
};