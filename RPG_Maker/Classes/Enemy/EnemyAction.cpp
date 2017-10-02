//************************************************/
//* @file  :EnemyAction.cpp
//* @brief :�G�̍s���ꗗ
//* @date  :2017/10/01
//* @author:S.Katou
//************************************************/
#include "EnemyAction.h"
#include "../Data/EnemyData.h"
#include "../Battle/BattleText.h"
#include "../Battle/BattleTextPreset.h"

bool EnemyAttackAction::Execute(BattleSystem * obj, void* own)
{
	auto text = BattleText::GetInstance();
	bool isEnded = false;

	auto data = (EnemyData*)own;

	//�U��
	if (!m_isSetText)
	{
		text->Reset();
		m_isSetText = true;
		std::string str = u8"�����X�^�[";
		text->SetString(ATTACK_TEXT(str));

	}
	else
	{
		isEnded = text->IsEnded();
	}
	return isEnded;
}
