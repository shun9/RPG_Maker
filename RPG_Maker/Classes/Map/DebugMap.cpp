//************************************************/
//* @file  :DebugMap.cpp
//* @brief :�f�o�b�O���s�p�}�b�v�i�^�C���̏W���́j
//* @date  :2017/10/01
//* @author:S.Katou
//************************************************/
#include "DebugMap.h"
#include <SL_RandomNumber.h>
#include "../Data/DataBase.h"

void DebugMap::DebugConvertScreenPos(int x, int y, Vec2 * buf)
{
	buf->m_x = x * Tile::SIZE;
	buf->m_y = y * Tile::SIZE;
}

void DebugMap::DebugConvertMapPos(const Vec2& pos, int * bufX, int * bufY)
{
	*bufX = (int)(pos.m_x / Tile::SIZE);
	*bufY = (int)(pos.m_y / Tile::SIZE);
}

bool DebugMap::DebugCanMoveSpecifiedDir(const Vec2& pos, DIRECTION_2D dir)
{
	const auto& holder = DB_Tile;

	//�^�C�����W�擾
	int x, y;
	this->DebugConvertMapPos(pos, &x, &y);

	//�w������̃^�C��
	switch (dir)
	{
	case ShunLib::ConstantNumber::TOP:
		y--;
		break;

	case ShunLib::ConstantNumber::BOTTOM:
		y++;
		break;

	case ShunLib::ConstantNumber::RIGHT:
		x++;
		break;

	case ShunLib::ConstantNumber::LEFT:
		x--;
		break;

	default:
		return false;
	}

	//�}�b�v�O�Ȃ�i�߂Ȃ�
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
	{
		return false;
	}

	int id = m_map[y][x].Id();

	auto data = holder.GetData(id);

	//�^�C����������ΐi�߂Ȃ�
	if (data == nullptr)
	{
		return false;
	}

	return data->canMove;
}

/// <summary>
/// �G���J�E���g���邩�ǂ���
/// </summary>
/// <param name="pos">���[���h���W</param>
/// <returns>�G���J�E���g������true</returns>
bool DebugMap::IsEncount(const Vec2& pos)
{
	const auto& holder = DB_Tile;

	//�}�b�v��̍��W���擾
	int x, y;
	this->DebugConvertMapPos(pos, &x, &y);

	//�^�C�������擾
	int id = m_map[y][x].Id();
	auto data = holder.GetData(id);

	//�����擾
	ShunLib::RandomNumber rn;
	int rate = rn(0, 99);

	//�G���J�E���g���邩�ǂ���
	if (data->encountRate > rate)
	{
		return true;
	}

	return false;
}

int DebugMap::GetRandamEnemy(const Vec2 & pos)
{
	const auto& holder = DB_Tile;

	//�}�b�v��̍��W���擾
	int x, y;
	this->DebugConvertMapPos(pos, &x, &y);

	//�^�C�������擾
	int id = m_map[y][x].Id();
	auto data = holder.GetData(id);
	int group = (int)data->enemyGroup.size();

	if (group > 0)
	{
		//�����擾
		ShunLib::RandomNumber rn;
		int rate = rn(0, group - 1);
		return rate;
	}
	return -1;
}
