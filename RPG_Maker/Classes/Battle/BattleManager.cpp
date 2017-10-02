//************************************************/
//* @file  :BattleManager.cpp
//* @brief :�퓬�V�[�����Ǘ�����N���X
//* @date  :2017/09/30
//* @author:S.Katou
//************************************************/
#include "BattleManager.h"

void BattleManager::Update()
{
	//�s���̑I��
	if (!m_isSelected)
	{
		m_isSelected = m_system.SelectAction();
	}

	//�s�������s����
	if (m_isSelected)
	{
		m_isExecuted = m_system.ExecuteAction();
	}

	//�^�[�����I��������ŏ��ɖ߂�
	if (m_isExecuted || m_system.Enemy() == nullptr)
	{
		m_isSelected = false;
		m_isExecuted = false;
		m_isEnded = m_system.IsEnded();
	}

	//�o�g�����I�������猋�ʂ��󂯎��
	if (m_isEnded)
	{

	}
}

void BattleManager::Draw(const ShunLib::Vec2 & pos)
{
	m_system.Draw(pos);
}
