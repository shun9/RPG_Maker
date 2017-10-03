//************************************************/
//* @file  :UITableBase.h
//* @brief :UIのUITableBaseクラス
//* @date  :2017/09/27
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <vector>
#include <memory>
#include <string>
#include "../UIBase.h"

class UITableBase :public UIBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	UITableBase(const std::string& name):UIBase(name){}

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UITableBase() override{}

	virtual void DrawUpdate() override{}

	virtual void ParamUpdate(int id) {}

	virtual void DataListIDUpdate() {}

	virtual void DrawImage() {};
};