//************************************************/
//* @file  :PlayerAction.cpp
//* @brief :プレイヤーの行動一覧
//* @date  :2017/10/01
//* @author:S.Katou
//************************************************/
#include "PlayerAction.h"
#include "../Battle/BattleSystem.h"

bool PlayerAttackAction::Execute(BattleSystem * obj)
{
	//攻撃
	obj->Player();
	return true;
}

bool PlayerDefenseAction::Execute(BattleSystem * obj)
{
	return true;
}

bool PlayerEscapeAction::Execute(BattleSystem * obj)
{
	return true;
}
