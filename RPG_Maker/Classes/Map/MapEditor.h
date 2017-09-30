//************************************************/
//* @file  :MapEditor.h
//* @brief :�}�b�v�G�f�B�^�[
//* @date  :2017/09/27
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Singleton.h>
#include <SL_Vec2.h>

class Map;

class MapEditor:public ShunLib::Singleton<MapEditor>
{
	friend ShunLib::Singleton<MapEditor>;

private:
	//�ێ����Ă���^�C��ID
	int m_id;

	//����ւ���Ώ�
	Map* m_map;

public:
	//�^�C��ID
	void Id(int id) { m_id = id; }
	int Id() { return m_id; }

	//����ւ���Ώ�
	void Map(Map* map) { m_map = map; }

	//�w��ʒu�̃^�C����h��ւ���
	void ChangeTile(const ShunLib::Vec2& pos);

	// �w��ʒu�̃^�C��������
	void EraserTile(const ShunLib::Vec2& pos);
private:
	MapEditor():m_id(-1) {}
	~MapEditor() {}
};