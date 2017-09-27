//************************************************/
//* @file  :Map.h
//* @brief :�}�b�v�i�^�C���̏W���́j
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <SL_ConstantNumber.h>
#include <SL_Texture.h>
#include <SL_MacroConstants.h>

#include "Tile.h"

class Map
{
	using Vec2 = ShunLib::Vec2;
	using DIRECTION_2D = ShunLib::ConstantNumber::DIRECTION_2D;

public:
	//�}�b�v�T�C�Y
	static const int WIDTH;
	static const int HEIGHT;

private:
	std::vector<std::vector<Tile>>m_map;

	//�X�N���[�������l
	ShunLib::Vec2 m_scrollNum;

public:
	Map();
	~Map();

	void SetTileId(int id, int x, int y) { m_map[y][x].Id(id); }
	//�`��
	void Draw();

	/// <summary>
	/// �w������̃^�C���Ɉړ��ł��邩�ǂ���
	/// </summary>
	/// <param name="dir">����</param>
	/// <returns>�ړ��\ true</returns>
	bool CanMoveSpecifiedDir(Vec2 pos,DIRECTION_2D dir);

	//�G���J�E���g���邩�ǂ���
	//�^�C���̏�Ɉړ������Ƃ��Ɏg�p
	bool IsEncount();

	//�G�O���[�v���烉���_���Ɏ擾
	Enemy* GetRandamEnemy();

	//�w������̃^�C���̏���ݒ�
	void SetContactTile(ShunLib::ConstantNumber::DIRECTION_2D, Tile*);


	//Get & Set
	//�G���J�E���g��
	int EncountRate();
	void EncountRate(int rate);

	//�ړ��\��
	bool CanMove();
	void CanMove(bool isWalk);

	//�摜
	void Texture(ShunLib::Texture* tex);

};