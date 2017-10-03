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
#include "../../Player/Player.h"

class UIDataBase :public UIBase
{
	using Vector2 = ShunLib::Vec2;

	enum DATA_LIST
	{
		PLAYER,
		ENEMY,
		ENEMYGROUP,
		length
	};
private:
	std::vector<std::unique_ptr<UITableBase>> m_uiList;

	std::unique_ptr<UIButton> m_playerButton;
	std::unique_ptr<UIButton> m_enemyButton;
	std::unique_ptr<UIButton> m_enemyGroupButton;
	std::unique_ptr<UIButton> m_saveButton;

	DATA_LIST m_viewData;
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UIDataBase(const std::string& name, Player* player);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~UIDataBase() override;

	virtual void DrawUpdate() override;

	void DrawImage();

	void ChangeActive(DATA_LIST data);
};