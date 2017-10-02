//************************************************/
//* @file  :PlayerAction.cpp
//* @brief :�v���C���[�̍s���ꗗ
//* @date  :2017/10/01
//* @author:S.Katou
//************************************************/
#include "PlayerAction.h"
#include "../Battle/BattleSystem.h"
#include "../Battle/BattleText.h"
#include "../Battle/BattleTextPreset.h"

/// <summary>
/// �U��
/// </summary>
bool PlayerAttackAction::Execute(BattleSystem * obj)
{
	auto text = BattleText::GetInstance();
	bool isEnded = false;

	//�U��
	if (!m_isSetText)
	{
		text->Reset();
		m_isSetText = true;
		std::string str = u8"�v���C���[";
		text->SetString(ATTACK_TEXT(str));
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
bool PlayerDefenseAction::Execute(BattleSystem * obj)
{
	auto text = BattleText::GetInstance();
	bool isEnded = false;

	//�h��
	if (!m_isSetText)
	{
		text->Reset();
		m_isSetText = true;
		std::string str = u8"�v���C���[";
		text->SetString(DEFENCE_TEXT(str));
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
bool PlayerEscapeAction::Execute(BattleSystem * obj)
{
	auto text = BattleText::GetInstance();
	bool isEnded = false;

	//������
	if (!m_isSetText)
	{
		text->Reset();
		m_isSetText = true;
		std::string str = u8"�v���C���[";
		text->SetString(ESCAPE_TEXT(str));
	}
	else
	{
		isEnded = text->IsEnded();
	}
	return isEnded;
}

