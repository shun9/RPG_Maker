//************************************************/
//* @file  :PlayerAction.h
//* @brief :�v���C���[�̍s���ꗗ
//* @date  :2017/10/01
//* @author:S.Katou
//************************************************/
#pragma once
#include "../Battle/Action.h"
#include <SL_MacroConstants.h>

class PlayerAtackAction :public Action
{
public:
	PlayerAtackAction() {}
	~PlayerAtackAction() {}
	bool Execute(BattleSystem* obj)override;
};