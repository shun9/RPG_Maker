//************************************************/
//* @file  :UIEnemyDataParam.h
//* @brief :UIEnemyDataParamクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <vector>
#include <memory>
#include <string>
#include "../UIBase.h"
#include "../../../Data/EnemyData.h"
#include "../UIButton.h"
#include "../UIInputIntBox.h"
#include "../UIInputStringBox.h"

class UIEnemyDataParam :public UIBase
{
	using Vector2 = ShunLib::Vec2;

private:
	EnemyData* m_data;
	std::unique_ptr<UIInputStringBox> m_nameInputBox;
	std::vector<std::unique_ptr<UIInputIntBox>> m_paramInputBox;
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UIEnemyDataParam(const std::string& name, EnemyData* data);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UIEnemyDataParam() override;

	void SetID(int id);
	void UIUpdate(EnemyData* data);

	virtual void DrawUpdate() override;

	void DrawImage();
};