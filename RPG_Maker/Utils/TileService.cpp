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

std::unique_ptr<TileData> TileService::CreateTileData(const wstring & path)
{
	auto data = make_unique<TileData>();

	data->texture = make_unique<Texture>(path.c_str());
	data->encountRate = 50;
	data->canMove = true;
	return move(data);
}
