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

class UIEnemyGroupDataParam :public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:
	EnemyGroupData* m_data;

	std::unique_ptr<UIButton> m_enemyButton;
	std::unique_ptr<UIButton> m_enemyGroupButton;

	std::unique_ptr<UIInputStringBox> m_nameInputBox;
	std::vector<std::unique_ptr<UIInputIntBox>> m_paramInputBox;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UIEnemyGroupDataParam(const std::string& name, EnemyGroupData* data);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UIEnemyGroupDataParam() override;

	void SetID(int id);
	void UIUpdate(EnemyGroupData* data);

	virtual void DrawUpdate() override;

	void DrawImage();
};