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
protected:
	using Vec2 = ShunLib::Vec2;
	using DIRECTION_2D = ShunLib::ConstantNumber::DIRECTION_2D;

public:
	//�}�b�v�T�C�Y
	static const int WIDTH;
	static const int HEIGHT;

protected:
	// �O���b�h�w�i
	std::unique_ptr<ShunLib::Texture> m_bgTile;

	std::vector<std::vector<Tile>>m_map;

	//�X�N���[�������l
	Vec2 m_scrollNum;

	//�\���ʒu
	Vec2 m_firstPos;
	Vec2 m_displaySize;

	//�I������Ă���ID
	int m_choiceId;

	//��������̍ێg�p����摜�̃f�[�^
	std::unique_ptr<ShunLib::Texture> m_emphasisMap;

public:
	Map();
	virtual ~Map();

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

	//�}�b�v���W���X�N���[�����W�ɕϊ�����
	void ConvertScreenPos(int X, int Y, Vec2* buf);

	/// �w������̃^�C���Ɉړ��ł��邩�ǂ���
	bool CanMoveSpecifiedDir(Vec2 pos,DIRECTION_2D dir);

	std::vector<std::vector<Tile>>* GetMapData() { return &m_map; }

	void DisplayRange(const Vec2& leftTop, const Vec2& rightBottom) {
		m_firstPos = leftTop;
		m_displaySize = rightBottom;
	};

	//�I������Ă���ID�̃Z�b�g
	void SetChoiseId(int id) { m_choiceId = id; }

	//�I������Ă���}�b�v�̋���
	void EmphasisMapDraw(int id, const ShunLib::Vec2& pos, const ShunLib::Vec2& scale, RECT* rect = nullptr);

private:
	bool IsInRangeTile(int x, int y, int dirTile[]);

	void DrawEdgeTile(int x,int y,float edge[], DIRECTION_2D dir,int dirTile[]);

	virtual void ClampScroll();

public:
	void operator=(const Map& m);

};