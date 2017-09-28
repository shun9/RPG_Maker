//************************************************/
//* @file  :Map.h
//* @brief :�}�b�v�i�^�C���̏W���́j
//* @date  :2017/09/27
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
	Vec2 m_scrollNum;

	//�\���ʒu
	Vec2 m_firstPos;
	Vec2 m_displaySize;

public:
	Map();
	~Map();

	//�L�[���͂ŃX�N���[������
	void Update();

	//�X�N���[�������l
	void Scroll(const Vec2& num) { m_scrollNum = num; }
	ShunLib::Vec2* Scroll() { return &m_scrollNum; }

	//�^�C�����Z�b�g����
	void SetTileId(int id, int x, int y);

	//�`��
	void Draw();

	//�X�N���[����̍��W���}�b�v�̍��W�ɕϊ�����
	void ConvertMapPos(const Vec2& pos, int* bufX, int* bufY);

	/// �w������̃^�C���Ɉړ��ł��邩�ǂ���
	bool CanMoveSpecifiedDir(Vec2 pos,DIRECTION_2D dir);

	////�G���J�E���g���邩�ǂ���
	////�^�C���̏�Ɉړ������Ƃ��Ɏg�p
	//bool IsEncount();

	////�G�O���[�v���烉���_���Ɏ擾
	//Enemy* GetRandamEnemy();

	void DisplayRange(const Vec2& leftTop, const Vec2& rightBottom) {
		m_firstPos = leftTop;
		m_displaySize = rightBottom;
	};

private:
	bool IsInRangeTile(int x, int y, int dirTile[]);

	void DrawEdgeTile(int x,int y,float edge[], DIRECTION_2D dir,int dirTile[]);

	void ClampScroll();
};