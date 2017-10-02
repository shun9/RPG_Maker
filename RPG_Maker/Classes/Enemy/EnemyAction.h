//************************************************/
//* @file  :EnemyAction.h
//* @brief :敵の行動一覧
//* @date  :2017/10/01
//* @author:S.Katou
//************************************************/
#pragma once
#include"../Battle/Action.h"

class EnemyAttackAction:public Action
{

public:
	EnemyAttackAction() {}
	~EnemyAttackAction() {}
	bool Execute(BattleSystem* obj)override;
	void Start()override {
		m_isSetText = false;
	};
};