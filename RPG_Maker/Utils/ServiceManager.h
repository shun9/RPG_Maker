//************************************************/
//* @file  :SerViceManager.h
//* @brief :各Serviceを管理するクラス
//* @date  :2017/09/26
//* @author:K,Yamamoto
//************************************************/
#pragma once
#include <SL_Singleton.h>
#include <SL_Vec2.h>
#include "TileService.h"

class ServiceManager;

namespace {
	using namespace ShunLib;
	using namespace std;
}

#define SVC_Tile ServiceManager::GetInstance()->GetTileSVC()

class ServiceManager : public Singleton<ServiceManager>
{
	friend ShunLib::Singleton<ServiceManager>;

public:
	TileService* GetTileSVC(){ return TileService::GetInstance(); }
};