//************************************************/
//* @file  :UIEnemyGroupTable.h
//* @brief :UIEnemyGroupTableクラス
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
#include "UITableBase.h"

class UIEnemyGroupTable :public UITableBase
{
	using Vector2 = ShunLib::Vec2;

private:

	std::unique_ptr<UIDataList<EnemyGroupData>> m_uiDataList;
	std::unique_ptr<UIButton> m_addButton;
	std::unique_ptr<UIEnemyGroupDataParam> m_uiDataParam;

	int m_selectId;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UIEnemyGroupTable(const std::string& name);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UIEnemyGroupTable() override;

	virtual void DrawUpdate() override;

	void ParamUpdate(int id) override;

	void DataListIDUpdate() override { m_uiDataList->SetID(DB_EnemyGroup.GetList().size() - 1); }

	void DrawImage() override;
};