//************************************************/
//* @file  :PlayerAction.h
//* @brief :プレイヤーの行動一覧
//* @date  :2017/10/01
//* @author:S.Katou
//************************************************/
#pragma once
#include "../Battle/Action.h"
#include <SL_MacroConstants.h>

class PlayerAttackAction :public Action
{
public:
	PlayerAttackAction() { m_shouldSelectTarget = true; }
	~PlayerAttackAction() {}
	bool Execute(BattleSystem* obj, void* own)override;
	void Start()override {
		m_isSetText = false;
	};
};

class PlayerDefenseAction :public Action
{
public:
	PlayerDefenseAction() {}
	~PlayerDefenseAction() {}
	bool Execute(BattleSystem* obj, void* own)override;
	void Start()override {
		m_isSetText = false;
	};
};

class PlayerEscapeAction :public Action
{
public:
	PlayerEscapeAction() {}
	~PlayerEscapeAction() {}
	bool Execute(BattleSystem* obj, void* own)override;
	void Start()override {
		m_isSetText = false;
	};
};