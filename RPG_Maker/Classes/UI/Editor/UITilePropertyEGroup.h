//************************************************/
//* @file  :UITilePropertyEGroup.h
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

class UITilePropertyEGroup :public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:
	//std::shared_ptr<std::list<int, std::shared_ptr<UIButton>>> m_groupList;
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UITilePropertyEGroup(const std::string& name);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~UITilePropertyEGroup() override;

	void AddGroup(int id);

	virtual void DrawUpdate() override;

	void UIDrawUpdate();
};