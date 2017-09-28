//************************************************/
//* @file  :UIMenu.h
//* @brief :UIMenu�̃N���X
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <SL_Vec2.h>
#include "UIBase.h"
#include <map>
#include <memory>
#include <string>

#include "UIMenuItem.h"

class UIMenu :public UIBase
{
	using Vector2 = ShunLib::Vec2;
private:
	std::shared_ptr<std::map<std::string, std::shared_ptr<UIMenuItem>>> m_itemList;
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UIMenu(const std::string& name);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~UIMenu() override;

	virtual void DrawUpdate() override;

	std::map<std::string, std::shared_ptr<UIMenuItem>>& GetItemList() { return *m_itemList.get(); }
};