//************************************************/
//* @file  :UIEnemyTable.h
//* @brief :UIのUIEnemyTableクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <vector>
#include <memory>
#include <string>
#include "../UIBase.h"
#include "UIDataList.h"
#include "UIEnemyDataParam.h"

class UIEnemyTable :public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:

	std::unique_ptr<UIDataList<EnemyData>> m_uiDataList;
	std::unique_ptr<UIButton> m_addButton;
	std::unique_ptr<UIEnemyDataParam> m_uiDataParam;

	int m_selectId;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UIEnemyTable(const std::string& name);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UIEnemyTable() override;

	virtual void DrawUpdate() override;

	void ParamUpdate(int id) { m_uiDataParam->UIUpdate(DB_Enemy.GetData(id)); }

	void DataListIDUpdate() { m_uiDataList->SetID(DB_Enemy.GetList().size() - 1); }

	void DrawImage();
};