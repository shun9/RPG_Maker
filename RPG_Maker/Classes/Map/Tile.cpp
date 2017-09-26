//************************************************/
//* @file  :Tile.cpp
//* @brief :�}�b�v�^�C��
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#include "Tile.h"
#include <SL_RandomNumber.h>

/// <summary>
/// �}�b�v�^�C���������N����
/// </summary>
void Tile::LinkTile(Tile ** map, int row, int column)
{
	for (int i = 0; i < column; i++)
	{
		for (int j = 0; j < row; j++)
		{
			map[column][row];
		}
	}
}

/// <summary>
/// �G���J�E���g���邩�ǂ���
/// </summary>
/// <returns>�G���J�E���g������ true</returns>
bool Tile::IsEncount()
{
	ShunLib::RandomNumber rn;

	//0 �` 100�������_���Ɏ擾
	int rate = rn(0, 100);

	//�G���J�E���g��
	if (rate <= m_encountRate)
	{
		return true;
	}

	return false;
}

/// <summary>
/// �G�O���[�v���烉���_���Ɏ擾
/// </summary>
Enemy * Tile::GetRandamEnemy()
{
	return nullptr;
}

/// <summary>
/// �w������̃^�C���Ɉړ��ł��邩�ǂ���
/// </summary>
/// <param name="dir">����</param>
/// <returns>�ړ��\ true</returns>
bool Tile::CanMoveSpecifiedDir(ShunLib::ConstantNumber::DIRECTION_2D dir)
{
	//�w������̃^�C��
	Tile* tile = m_contactTile[dir];

	//�^�C����������ΐi�߂Ȃ�
	if (tile == nullptr)
	{
		return false;
	}

	return tile->CanMove();
}
