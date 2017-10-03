//************************************************/
//* @file  :UITableBase.h
//* @brief :UI��UITableBase�N���X
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
	/// �R���X�g���N�^
	/// </summary>
	UITableBase(const std::string& name):UIBase(name){}

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~UITableBase() override{}

	virtual void DrawUpdate() override{}

	virtual void ParamUpdate(int id) {}

	virtual void DataListIDUpdate() {}

	virtual void DrawImage() {};
};