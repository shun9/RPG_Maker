//************************************************/
//* @file  :DebugMap.cpp
//* @brief :�f�o�b�O���s�p�}�b�v�i�^�C���̏W���́j
//* @date  :2017/09/30
//* @author:S.Katou
//************************************************/
#include "DebugMap.h"
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

bool DebugMap::DebugCanMoveSpecifiedDir(Vec2 pos, DIRECTION_2D dir)
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
