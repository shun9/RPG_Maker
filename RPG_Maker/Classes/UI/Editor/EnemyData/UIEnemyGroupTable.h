//************************************************/
//* @file  :UIEnemyGroupTable.h
//* @brief :UIEnemyGroupTable�N���X
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <vector>
#include <memory>
#include <string>
#include "../UIBase.h"
#include "UIDataList.h"
#include "UIEnemyGroupDataParam.h"

class UIEnemyGroupTable :public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:

	std::unique_ptr<UIDataList<EnemyGroupData>> m_uiDataList;
	std::unique_ptr<UIButton> m_addButton;
	std::unique_ptr<UIEnemyGroupDataParam> m_uiDataParam;

	int m_selectId;
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UIEnemyGroupTable(const std::string& name);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~UIEnemyGroupTable() override;

	virtual void DrawUpdate() override;

	void ParamUpdate(int id);

	void DataListIDUpdate() { m_uiDataList->SetID(DB_Enemy.GetList().size() - 1); }

	void DrawImage();
};