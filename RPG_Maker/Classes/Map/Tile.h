//************************************************/
//* @file  :Tile.h
//* @brief :�}�b�v�^�C��
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_ConstantNumber.h>
#include <SL_Texture.h>
#include <SL_MacroConstants.h>

class TileData;

class Tile
{
public:
	//�^�C����1�ӂ̒���
	static const float SIZE;

	//�^�C�����q����
	//�Q�[���J�n���Ɏg�p
	static void LinkTile(Tile** map,int row,int column);

private:
	int m_id;

public:
	Tile();
	~Tile();

	//�`��
	void Draw(const ShunLib::Vec2& pos, const ShunLib::Vec2& scale);

	//�G���J�E���g���邩�ǂ���
	//�^�C���̏�Ɉړ������Ƃ��Ɏg�p
	bool IsEncount();

	////�G�O���[�v���烉���_���Ɏ擾
	//Enemy* GetRandamEnemy();

	////�w�肵�������Ɉړ��ł��邩�ǂ���
	////�^�C���̏ォ��ړ����悤�Ƃ����Ƃ��Ɏg�p
	//bool CanMoveSpecifiedDir(ShunLib::ConstantNumber::DIRECTION_2D);

	////�w������̃^�C���̏���ݒ�
	//void SetContactTile(ShunLib::ConstantNumber::DIRECTION_2D,Tile*);


	////Get & Set
	////�G���J�E���g��
	//int EncountRate() { return m_encountRate; }
	//void EncountRate(int rate) {
	//	m_encountRate = rate;
	//	if (m_encountRate > 100){
	//		m_encountRate = 100;
	//	}
	//}

	////�ړ��\��
	//bool CanMove() { return m_canMove; }
	//void CanMove(bool isWalk) { m_canMove = isWalk; }

	////�摜
	//void Texture(ShunLib::Texture* tex) { m_texture = tex; }
};
