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
	bool DebugCanMoveSpecifiedDir(Vec2 pos, DIRECTION_2D dir);

};