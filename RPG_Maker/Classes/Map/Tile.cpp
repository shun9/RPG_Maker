//************************************************/
//* @file  :Tile.cpp
//* @brief :�}�b�v�^�C��
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#include "Tile.h"
#include <SL_RandomNumber.h>

//�^�C����1�ӂ̒���
const float Tile::SIZE = 32.0f;

/// <summary>
/// �}�b�v�^�C���������N����
/// �Q�[���J�n���Ɏg�p
/// </summary>
void Tile::LinkTile(Tile ** map, int row, int column)
{
	using DIRECTION_2D = ShunLib::ConstantNumber::DIRECTION_2D;

	//�c
	for (int i = 0; i < column; i++)
	{
		//��
		for (int j = 0; j < row; j++)
		{
			//��
			if (i == 0)         map[i][j].SetContactTile(DIRECTION_2D::TOP, nullptr);
			else                map[i][j].SetContactTile(DIRECTION_2D::TOP, &map[i +1][j]);

			//��
			if (i == column - 1)map[i][j].SetContactTile(DIRECTION_2D::BOTTOM, nullptr);
			else                map[i][j].SetContactTile(DIRECTION_2D::BOTTOM, &map[i + 1][j]);

			//�E
			if (j == 0)         map[i][j].SetContactTile(DIRECTION_2D::RIGHT, nullptr);
			else                map[i][j].SetContactTile(DIRECTION_2D::RIGHT, &map[i][j + 1]);

			//��
			if (j == row - 1)   map[i][j].SetContactTile(DIRECTION_2D::LEFT, nullptr);
			else                map[i][j].SetContactTile(DIRECTION_2D::LEFT, &map[i][j - 1]);
		}
	}
}


Tile::Tile() :
	m_texture(nullptr)
{
	m_texture = new ShunLib::Texture(L"Image\\brick.png");
}

Tile::~Tile()
{
	DELETE_POINTER(m_texture);
}

/// <summary>
/// �`��
/// </summary>
void Tile::Draw(const ShunLib::Vec2 & pos, const ShunLib::Vec2& scale)
{
	if (m_texture != nullptr)
	{
		m_texture->Draw(pos, scale);
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


/// <summary>
/// �w������̃^�C���̏���ݒ�
/// </summary>
void Tile::SetContactTile(ShunLib::ConstantNumber::DIRECTION_2D dir, Tile* tile)
{
	m_contactTile[dir] = tile;
}
