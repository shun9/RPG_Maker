//************************************************/
//* @file  :DebugMap.h
//* @brief :�f�o�b�O���s�p�}�b�v�i�^�C���̏W���́j
//* @date  :2017/09/30
//* @author:S.Katou
//************************************************/
#pragma once
#include "Map.h"

class DebugMap :public Map
{
public:
	DebugMap() {}
	~DebugMap() {}

	//�}�b�v���W���X�N���[�����W�ɕϊ�����
	void DebugConvertScreenPos(int x, int y, Vec2* buf);

	//�X�N���[����̍��W���}�b�v�̍��W�ɕϊ�����
	void DebugConvertMapPos(const Vec2& pos, int* bufX, int* bufY);

	//�w������ɐi�߂邩�ǂ���
	bool DebugCanMoveSpecifiedDir(const Vec2& pos, DIRECTION_2D dir);

	//�G���J�E���g���邩�ǂ���
	//�^�C���̏�Ɉړ������Ƃ��Ɏg�p
	bool IsEncount(const Vec2& pos);

	//�G�O���[�v���烉���_���Ɏ擾
	int GetRandamEnemy(const Vec2& pos);
};