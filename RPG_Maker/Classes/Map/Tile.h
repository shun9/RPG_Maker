//************************************************/
//* @file  :Tile.h
//* @brief :�}�b�v�^�C��
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once

#include <SL_ConstantNumber.h>

class Enemy;

class Tile
{
	//�^�C�����q����
	//�Q�[���J�n���Ɏg�p
	static void LinkTile(Tile** map,int row,int column);

private:
	//�G�̃G���J�E���g��
	int m_encountRate;

	//�o������G�̍\���ꗗ
	Enemy** m_enemyGroup;

	//�ڂ��Ă���^�C���@�㉺���E
	Tile* m_contactTile[ShunLib::ConstantNumber::DIRECTION_2D::num];

	//�v���C���[���������Ƃ��o���邩�ǂ���
	//������Ȃ� true
	bool m_canMove;

public:
	Tile() {}
	~Tile() {}

	//�G���J�E���g���邩�ǂ���
	//�^�C���̏�Ɉړ������Ƃ��Ɏg�p
	bool IsEncount();

	//�G�O���[�v���烉���_���Ɏ擾
	Enemy* GetRandamEnemy();

	//�w�肵�������Ɉړ��ł��邩�ǂ���
	//�^�C���̏ォ��ړ����悤�Ƃ����Ƃ��Ɏg�p
	bool CanMoveSpecifiedDir(ShunLib::ConstantNumber::DIRECTION_2D);

	//�w������̃^�C���̏���ݒ�
	void SetContactTile(ShunLib::ConstantNumber::DIRECTION_2D,Tile*);

	//Get & Set
	int EncountRate() { return m_encountRate; }
	void EncountRate(int rate) {
		m_encountRate = rate;
		if (m_encountRate > 100){
			m_encountRate = 100;
		}
	}

	bool CanMove() { return m_canMove; }
	void CanMove(bool isWalk) { m_canMove = isWalk; }
};
