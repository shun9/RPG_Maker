//************************************************/
//* @file  :MapEditor.h
//* @brief :マップエディター
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
	//保持しているタイルID
	int m_id;

	//張り替える対象
	Map* m_map;

public:
	//タイルID
	void Id(int id) { m_id = id; }
	int Id() { return m_id; }

	//張り替える対象
	void Map(Map* map) { m_map = map; }

	//指定位置のタイルを塗り替える
	void ChangeTile(const ShunLib::Vec2& pos);

	// 指定位置のタイルを消す
	void EraserTile(const ShunLib::Vec2& pos);
private:
	MapEditor():m_id(-1) {}
	~MapEditor() {}
};