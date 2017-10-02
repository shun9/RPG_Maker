//************************************************/
//* @file  :UIBase.h
//* @brief :UIの基底クラス
//* @date  :2017/09/26
//* @author:K.Yamamoto
//************************************************/
#pragma once

#include <SL_Vec2.h>
#include <list>
#include <string>

#define UIACTIVEDRAW(ui) if(ui!=nullptr){ui->DrawUpdate();} 
#define UIVECTORDRAW(ui,index) if(index < ui.size() ){ if(ui.at(index) != nullptr) ui.at(index)->DrawUpdate();} 

class UIBase
{
	using Vector2 = ShunLib::Vec2;

protected:
	std::string m_name;

public:
	bool Active;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	UIBase(const std::string& name);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~UIBase();

	void ChangeName(std::string name) { m_name = name; }

	virtual void DrawUpdate();

	static void ActiveChange(UIBase& ui, bool state) { ui.Active = state; }
};