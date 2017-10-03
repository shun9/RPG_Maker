//************************************************/
//* @file  :UIEnemyGroupDataParam.h
//* @brief :UIEnemyGroupDataParam�N���X
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

	// ���ݑI�����Ă���O���[�v�f�[�^��ID
	int m_selectGroupID;
	// ���ݑI�����Ă���O���[�v�A���[���f�[�^��ID
	int m_selectGroupAloneID;
	// ���ݑI�����Ă���G�f�[�^��ID
	int m_selectEnemyID;
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UIEnemyGroupDataParam(const std::string& name, EnemyGroupData* data = nullptr);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~UIEnemyGroupDataParam() override;

	void SetID(int id);
	void UIUpdate(EnemyGroupData* data);

	virtual void DrawUpdate() override;

	void AddEnemy();

	void DataListIDUpdate() { m_enemyList->SetID(m_data->enemyList.GetList().size() - 1); }

	void DrawImage();
};