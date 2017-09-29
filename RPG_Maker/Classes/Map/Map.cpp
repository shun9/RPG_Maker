//************************************************/
//* @file  :Map.cpp
//* @brief :�}�b�v�i�^�C���̏W���́j
//* @date  :2017/09/27
//* @author:S.Katou
//************************************************/
#include "Map.h"

#include <functional>
#include <SL_KeyManager.h>
#include "../../Utils/MouseManager.h"
#include "TileDataHolder.h"

using namespace ShunLib;

const int Map::WIDTH = 256;
const int Map::HEIGHT = 256;

/// <summary>
/// �R���X�g���N�^
/// </summary>
Map::Map()
{
	m_scrollNum = { 0.0f,0.0f };
	m_firstPos = { 0.0f,0.0f };
	m_displaySize = { 1200.0f,800.0f };
	m_map.resize(HEIGHT);
	for (int i = 0; i < HEIGHT; i++)
	{
		m_map[i].resize(WIDTH);
	}
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Map::~Map()
{

}

void Map::Update()
{
	auto key = ShunLib::KeyManager::GetInstance();

	if		(key->IsPushed(KeyManager::KEY_CODE::UP   ))
	{
		m_scrollNum.m_y -= 1.0f;
		ClampScroll();
	}
	else if (key->IsPushed(KeyManager::KEY_CODE::DOWN ))
	{
		m_scrollNum.m_y += 1.0f;
		ClampScroll();
	}
	else if (key->IsPushed(KeyManager::KEY_CODE::LEFT ))
	{
		m_scrollNum.m_x -= 1.0f;
		ClampScroll();
	}
	else if (key->IsPushed(KeyManager::KEY_CODE::RIGHT))
	{
		m_scrollNum.m_x += 1.0f;
		ClampScroll();
	}
}

/// <summary>
/// �w�肵�����W�̃^�C���𒣂�ւ���
/// </summary>
void Map::SetTileId(int id, int x, int y)
{
	//�}�b�v�̃T�C�Y�𒴂��Ă����甲����
	if (x > this->WIDTH - 1 || y > this->HEIGHT - 1)
	{
		return;
	}

	float edge[4] = { m_firstPos.m_y,m_displaySize.m_y,m_displaySize.m_x,m_firstPos.m_x };
	int edgeTile[DIRECTION_2D::num];

	//��ʒ[�̃}�b�v���W���擾
	ConvertMapPos(Vec2(edge[DIRECTION_2D::LEFT], edge[DIRECTION_2D::TOP]), &edgeTile[DIRECTION_2D::LEFT], &edgeTile[DIRECTION_2D::TOP]);
	ConvertMapPos(Vec2(edge[DIRECTION_2D::RIGHT], edge[DIRECTION_2D::BOTTOM]), &edgeTile[DIRECTION_2D::RIGHT], &edgeTile[DIRECTION_2D::BOTTOM]);
	if (IsInRangeTile(x, y, edgeTile))
	{
		//����ւ���
		m_map[y][x].Id(id);
	}
}


/// <summary>
/// �`��
/// </summary>
/// <param name="top">�`��͈͂̏���W</param>
/// <param name="bottom">�`��͈͂̉����W</param>
/// /// <param name="left">�`��͈͂̍����W</param>
/// <param name="right">�`��͈͂̉E���W</param>
void Map::Draw()
{
	using namespace ShunLib;

	float edge[4] = { m_firstPos.m_y,m_displaySize.m_y,m_displaySize.m_x,m_firstPos.m_x };
	int dirTile[DIRECTION_2D::num];
	int edgeTile[DIRECTION_2D::num];

	//��ʒ[�̃}�b�v���W���擾
	ConvertMapPos(Vec2(edge[DIRECTION_2D::LEFT], edge[DIRECTION_2D::TOP]), &dirTile[DIRECTION_2D::LEFT], &dirTile[DIRECTION_2D::TOP]);
	ConvertMapPos(Vec2(edge[DIRECTION_2D::RIGHT], edge[DIRECTION_2D::BOTTOM]), &dirTile[DIRECTION_2D::RIGHT], &dirTile[DIRECTION_2D::BOTTOM]);

	//�[�͈ꕔ�̂ݕ`��
	for (int i = 0; i < DIRECTION_2D::num; i++)
	{
		edgeTile[i] = dirTile[i];
	}

	edgeTile[DIRECTION_2D::TOP]--;
	edgeTile[DIRECTION_2D::BOTTOM]++;
	edgeTile[DIRECTION_2D::LEFT]--;
	edgeTile[DIRECTION_2D::RIGHT]++;

	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			//�^�C�����w��͈͓��ɂ���Ε`�悷��
			//�[�̃^�C���͈ꕔ�̂ݕ`��
			if (!IsInRangeTile(j, i, edgeTile))
			{
				continue;
			}

			//��[�ɂ���^�C����`��
			if (i == dirTile[DIRECTION_2D::TOP])
			{
				DrawEdgeTile(j, i, edge, DIRECTION_2D::TOP, dirTile);
				continue;
			}
			//���[�ɂ���^�C����`��
			if (i == dirTile[DIRECTION_2D::BOTTOM])
			{
				DrawEdgeTile(j, i, edge, DIRECTION_2D::BOTTOM, dirTile);
				continue;
			}

			//���[�ɂ���^�C����`��
			if (j == dirTile[DIRECTION_2D::LEFT])
			{
				DrawEdgeTile(j, i, edge, DIRECTION_2D::LEFT, dirTile);
				continue;
			}

			//�E�[�ɂ���^�C����`��
			if (j == dirTile[DIRECTION_2D::RIGHT])
			{
				DrawEdgeTile(j, i, edge, DIRECTION_2D::RIGHT, dirTile);
				continue;
			}

			Vec2 pos(j*Tile::SIZE, i*Tile::SIZE);
			m_map[i][j].Draw(pos - m_scrollNum, Vec2::One);
		}
	}
}


/// <summary>
/// �X�N���[����̍��W���}�b�v�̍��W�ɕϊ�����
/// </summary>
/// <param name="pos">�X�N���[�����W</param>
/// <param name="bufX">X���W�i�[�ϐ�</param>
/// <param name="bufY">Y���W�i�[�ϐ�</param>
void Map::ConvertMapPos(const Vec2& pos, int* bufX, int* bufY)
{
	*bufX = (int)((pos.m_x + m_scrollNum.m_x) / Tile::SIZE);
	*bufY = (int)((pos.m_y + m_scrollNum.m_y) / Tile::SIZE);
}


/// <summary>
/// �w������ɐi�߂邩�ǂ���
/// </summary>
/// <param name="pos">���ݍ��W</param>
/// <param name="dir">�i�ޕ���</param>
bool Map::CanMoveSpecifiedDir(Vec2 pos, ConstantNumber::DIRECTION_2D dir)
{
	auto holder = TileDataHolder::GetInstance();

	//�^�C�����W�擾
	int x,y;
	ConvertMapPos(pos, &x, &y);

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

	auto data = holder->GetData(id);

	//�^�C����������ΐi�߂Ȃ�
	if (data == nullptr)
	{
		return false;
	}

	return data->canMove;
}


/// <summary>
/// �w����W�̃^�C�����w��͈͓����ǂ���
/// </summary>
bool Map::IsInRangeTile(int x ,int y,int dirTile[])
{
	if (x < dirTile[DIRECTION_2D::LEFT] || x >= dirTile[DIRECTION_2D::RIGHT])
	{
		return false;
	}

	if (y < dirTile[DIRECTION_2D::TOP] || y >= dirTile[DIRECTION_2D::BOTTOM])
	{
		return false;
	}

	//�^�C�����w��͈͓�
	return true;
}


/// <summary>
/// �[�̃^�C����`��
/// </summary>
void Map::DrawEdgeTile(int x, int y, float edge[], DIRECTION_2D dir, int dirTile[])
{
	int size = (int)(Tile::SIZE);
	Vec2 pos((float)x*size, (float)y*size);

	RECT rect = {0,0,(LONG)Tile::SIZE,(LONG)Tile::SIZE };

	//�`�悷��T�C�Y
	float rectSize;

	auto SetRectSize = [=](DIRECTION_2D dire, float pos) {
		return edge[dire] + pos - size*(int)((edge[dire] + pos) / size);
	};

	//�[�ɂ���^�C����`��
	switch (dir)
	{
	case DIRECTION_2D::TOP:
		rectSize = SetRectSize(dir,m_scrollNum.m_y);
		rect.top = (LONG)(rectSize);
		pos.m_y += rectSize;
		break;

	case DIRECTION_2D::BOTTOM:
		rectSize = SetRectSize(dir, m_scrollNum.m_y);
		rect.bottom = (LONG)(rectSize);
		break;

	case DIRECTION_2D::LEFT:
		rectSize = SetRectSize(dir, m_scrollNum.m_x);
		rect.left = (LONG)(rectSize);
		pos.m_x += rectSize;
		break;

	case DIRECTION_2D::RIGHT:
		rectSize = SetRectSize(dir, m_scrollNum.m_x);
		rect.right = (LONG)(rectSize);
		break;

	default:
		break;
	}

	//�l���̏ꍇ�͏���ǉ�
	if (y == dirTile[DIRECTION_2D::TOP] && dir != DIRECTION_2D::TOP) {
		rectSize = SetRectSize(DIRECTION_2D::TOP,m_scrollNum.m_y);
		rect.top = (LONG)(rectSize);
		pos.m_y += rectSize;
	}

	if (y == dirTile[DIRECTION_2D::BOTTOM] && dir != DIRECTION_2D::BOTTOM) {
		rectSize = SetRectSize(DIRECTION_2D::BOTTOM,m_scrollNum.m_y);
		rect.bottom = (LONG)(rectSize);
	}

	if (x == dirTile[DIRECTION_2D::LEFT] && dir != DIRECTION_2D::LEFT){
		rectSize = SetRectSize(DIRECTION_2D::LEFT,m_scrollNum.m_x);
		rect.left = (LONG)(rectSize);
		pos.m_x += rectSize;
	}

	if (x == dirTile[DIRECTION_2D::RIGHT] && dir != DIRECTION_2D::RIGHT) {
		rectSize = SetRectSize(DIRECTION_2D::RIGHT,m_scrollNum.m_x);
		rect.right = (LONG)(rectSize);
	}

	m_map[y][x].Draw(pos - m_scrollNum, Vec2::One, &rect);

}


void Map::ClampScroll()
{
	//��[
	if (m_scrollNum.m_y < 0.0f)
	{
		m_scrollNum.m_y = 0.0f;
	}
	//���[
	else if (m_scrollNum.m_y > Map::HEIGHT*Tile::SIZE - m_displaySize.m_y)
	{
		m_scrollNum.m_y = Map::HEIGHT*Tile::SIZE - m_displaySize.m_y;
	}
	//���[
	else if (m_scrollNum.m_x < 0.0f)
	{
		m_scrollNum.m_x = 0.0f;
	}
	//�E�[
	else if(m_scrollNum.m_x > Map::WIDTH*Tile::SIZE - m_displaySize.m_x)
	{
		m_scrollNum.m_x = Map::WIDTH*Tile::SIZE - m_displaySize.m_x;
	}

}
