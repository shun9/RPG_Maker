//************************************************/
//* @file  :BattleManager.cpp
//* @brief :�퓬�V�[�����Ǘ�����N���X
//* @date  :2017/09/30
//* @author:S.Katou
//************************************************/
#include "BattleManager.h"

#include "BattleText.h"

void BattleManager::Update()
{
	auto text = BattleText::GetInstance();
	text->Update();

	//�^�[�����Ƃ̏�����
	if (m_isTurnEnd)
	{
		m_system.Start();
		m_isTurnEnd = false;
	}

	//�s���̑I��
	if (!m_isSelected)
	{
		m_isSelected = m_system.SelectAction();
	}

	//�s�������s����
	if (m_isSelected)
	{
		m_isTurnEnd = m_system.ExecuteAction();
	}

	//�^�[�����I��������ŏ��ɖ߂�
	if (m_isTurnEnd)// || m_system.Enemy() == nullptr)
	{
		m_isSelected = false;
		m_isEnded = m_system.IsEnded();
	}

	//�o�g�����I�������猋�ʂ��󂯎��
	if (m_isEnded)
	{

	}

	//�����Ă�����I��
	if (!m_isEnded)
	{
		m_isEnded = m_system.IsEscape();
	}
}

void BattleManager::Draw(const ShunLib::Vec2 & pos)
{
	m_system.Draw(pos);
}
