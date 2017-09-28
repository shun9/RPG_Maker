//************************************************/
//* @file  :TileService.h
//* @brief :�^�C���֘A�̃T�[�r�X�N���X
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

	// path ����Texture�쐬
	Texture* CreateTexture(const wstring& path);

	// TileData�쐬
	TileData* CreateTileData(const wstring& path);

private:
	TileService(){}
};