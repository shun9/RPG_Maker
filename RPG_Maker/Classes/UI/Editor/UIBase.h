//************************************************/
//* @file  :UIBase.h
//* @brief :UI�̊��N���X
//* @date  :2017/09/26
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <SL_Vec2.h>
#include <list>
#include <string>

class UIBase
{
	using Vector2 = ShunLib::Vec2;

protected:
	std::string m_name;

public:
	bool Active;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UIBase(const std::string& name);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~UIBase();

	void ChangeName(std::string name) { m_name = name; }

	virtual void DrawUpdate();
};