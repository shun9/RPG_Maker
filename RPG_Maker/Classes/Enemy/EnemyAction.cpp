//************************************************/
//* @file  :EnemyAction.cpp
//* @brief :“G‚Ìs“®ˆê——
//* @date  :2017/10/01
//* @author:S.Katou
//************************************************/
#include "EnemyAction.h"
#include "../Data/EnemyData.h"
#include "../Battle/BattleText.h"
#include "../Battle/BattleTextPreset.h"
#include "../Battle/BattleSystem.h"

bool EnemyAttackAction::Execute(BattleSystem * obj, void* own)
{
	auto text = BattleText::GetInstance();
	bool isEnded = false;

	auto data = (EnemyData*)own;

	//UŒ‚
	if (!m_isSetText)
	{
		auto player = obj->Player();
		int damage = player->TakeDamage(data->Param[EnemyData::Param::ATK]);
		text->Reset();
		m_isSetText = true;
		std::string str = data->Name;
		text->SetString(ATTACK_TEXT(str));
		str = u8"ƒvƒŒƒCƒ„[";
		text->SetString(TAKE_DAMEGE_TEXT(str, GetNumberText(damage)));
		if (player->IsDead())
		{
			text->SetString(LOSE_TEXT(str));
		}
	}
	else
	{
		isEnded = text->IsEnded();
	}
	return isEnded;
}
