//************************************************/
//* @file  :UIDataBase.h
//* @brief :UIDatabase�̃N���X
//* @date  :2017/10/02
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <SL_Vec2.h>
#include "UIBase.h"
#include <map>
#include <memory>
#include <string>
#include "EnemyData\UIEnemyGroupTable.h"
#include "EnemyData\UIEnemyTable.h"

class UIDataBase :public UIBase
{
	using Vector2 = ShunLib::Vec2;

	enum DATA_LIST
	{
		ENEMY,
		ENEMYGROUP
	};
private:
	std::vector<std::unique_ptr<UIBase>> m_uiList;

	std::unique_ptr<UIButton> m_enemyButton;
	std::unique_ptr<UIButton> m_enemyGroupButton;

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UIDataBase(const std::string& name);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~UIDataBase() override;

	virtual void DrawUpdate() override;

	void DrawImage();

	void ChangeActive(DATA_LIST data);
};