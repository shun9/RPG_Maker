//************************************************/
//* @file  :PlayerAction.cpp
//* @brief :�v���C���[�̍s���ꗗ
//* @date  :2017/10/01
//* @author:S.Katou
//************************************************/
#include "PlayerAction.h"
#include "../Battle/BattleSystem.h"

bool PlayerAttackAction::Execute(BattleSystem * obj)
{
	//�U��
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
