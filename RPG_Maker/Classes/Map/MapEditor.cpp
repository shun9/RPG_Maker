//************************************************/
//* @file  :MapEditor.cpp
//* @brief :マップエディター
//* @date  :2017/09/27
//* @author:S.Katou
//************************************************/
#include "MapEditor.h"
#include "Map.h"

void MapEditor::ChangeTile(const ShunLib::Vec2 & pos)
{
	int x = 0;
	int y = 0;
	m_map->ConvertMapPos(pos, &x, &y);
	m_map->SetTileId(m_id, x, y);
}
