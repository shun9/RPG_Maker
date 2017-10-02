//************************************************/
//* @file  :UIEnemyGroupDataParam.h
//* @brief :UIEnemyGroupDataParamクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <vector>
#include <memory>
#include <string>
#include "../UIBase.h"
#include "../../../Data/EmeyGroupData.h"
#include "../UIButton.h"
#include "../UIInputIntBox.h"
#include "../UIInputStringBox.h"
#include "UIDataList.h"

class UIEnemyGroupDataParam :public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:
	EnemyGroupData* m_data;

	std::vector<std::unique_ptr<UIInputIntBox>> m_paramInputBox;
	std::unique_ptr<UIButton> m_enemyButton;
	std::unique_ptr<UIButton> m_enemyGroupButton;
	std::unique_ptr<UIButton> m_enemyAddButton;

	std::unique_ptr<UIInputStringBox> m_nameInputBox;

	std::unique_ptr<UIDataList<EnemyGroupAloneData>> m_groupAloneList;
	std::unique_ptr<UIDataList<EnemyData>> m_enemyList;

	// 現在選択しているグループデータのID
	int m_selectGroupID;
	// 現在選択しているグループアローンデータのID
	int m_selectGroupAloneID;
	// 現在選択している敵データのID
	int m_selectEnemyID;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UIEnemyGroupDataParam(const std::string& name, EnemyGroupData* data = nullptr);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UIEnemyGroupDataParam() override;

	void SetID(int id);
	void UIUpdate(EnemyGroupData* data);

	virtual void DrawUpdate() override;

	void AddEnemy();

	void DataListIDUpdate() { m_enemyList->SetID(m_data->enemyList.GetList().size() - 1); }

	void DrawImage();
};