//************************************************/
//* @file  :TileService.cpp
//* @brief :タイル関連のサービスクラス
//* @date  :2017/09/26
//* @author:K,Yamamoto
//************************************************/
#include "TileService.h"

using namespace ShunLib;
using namespace std;

Texture * TileService::CreateTexture(const wstring& path)
{
	return new Texture(path.c_str());
}

TileData * TileService::CreateTileData(const wstring & path)
{
	auto* data = new TileData();

	data->texture = new Texture(path.c_str());
	data->encountRate = 50;
	data->enemyGroup = nullptr;
	data->canMove = true;
	return data;
}
