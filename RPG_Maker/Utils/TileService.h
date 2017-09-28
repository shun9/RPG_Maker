//************************************************/
//* @file  :TileService.h
//* @brief :タイル関連のサービスクラス
//* @date  :2017/09/26
//* @author:K,Yamamoto
//************************************************/
#pragma once
#include <SL_Singleton.h>
#include <SL_Vec2.h>
#include <SL_Texture.h>
#include "../Classes/Map/TileDataHolder.h"

namespace {
	using namespace ShunLib;
	using namespace std;
}

class TileService : public Singleton<TileService>
{
	friend ShunLib::Singleton<TileService>;

public:

	~TileService(){}

	// path からTexture作成
	Texture* CreateTexture(const wstring& path);

	// TileData作成
	TileData* CreateTileData(const wstring& path);

private:
	TileService(){}
};