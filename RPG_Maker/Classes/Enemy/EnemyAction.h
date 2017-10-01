//************************************************/
//* @file  :EnemyAction.h
//* @brief :“G‚Ìs“®ˆê——
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
};