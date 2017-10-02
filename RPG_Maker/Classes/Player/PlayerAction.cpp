//************************************************/
//* @file  :PlayerAction.cpp
//* @brief :�v���C���[�̍s���ꗗ
//* @date  :2017/10/02
//* @author:S.Katou
//************************************************/
#include "PlayerAction.h"
#include "Player.h"
#include "../Battle/BattleSystem.h"
#include "../Battle/BattleText.h"
#include "../Battle/BattleTextPreset.h"

/// <summary>
/// �U��
/// </summary>
bool PlayerAttackAction::Execute(BattleSystem * obj, void* own)
{
	auto text = BattleText::GetInstance();
	bool isEnded = false;

	auto player = (Player*)own;

	//�U��
	if (!m_isSetText)
	{
		text->Reset();
		m_isSetText = true;
		std::string str = u8"�v���C���[";
		text->SetString(ATTACK_TEXT(str));
		player->ChangeDefence(false);
	}
	else
	{
		isEnded = text->IsEnded();
	}

	return isEnded;
}


/// <summary>
/// �h��
/// </summary>
bool PlayerDefenseAction::Execute(BattleSystem * obj, void* own)
{
	auto text = BattleText::GetInstance();
	bool isEnded = false;
	auto player = (Player*)own;

	//�h��
	if (!m_isSetText)
	{
		text->Reset();
		m_isSetText = true;
		std::string str = u8"�v���C���[";
		text->SetString(DEFENCE_TEXT(str));

		player->ChangeDefence(true);
	}
	else
	{
		isEnded = text->IsEnded();
	}
	return isEnded;
}


/// <summary>
/// ������
/// </summary>
bool PlayerEscapeAction::Execute(BattleSystem * obj, void* own)
{
	auto text = BattleText::GetInstance();
	bool isEnded = false;
	auto player = (Player*)own;

	//������
	if (!m_isSetText)
	{
		text->Reset();
		m_isSetText = true;
		std::string str = u8"�v���C���[";
		text->SetString(ESCAPE_TEXT(str));
		player->ChangeDefence(false);

		obj->Escape();
	}
	else
	{
		isEnded = text->IsEnded();
	}
	return isEnded;
}

