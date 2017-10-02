//************************************************/
//* @file  :SerViceManager.h
//* @brief :ŠeService‚ğŠÇ—‚·‚éƒNƒ‰ƒX
//* @date  :2017/09/26
//* @author:K,Yamamoto
//************************************************/
#pragma once
#include <SL_Singleton.h>
#include <SL_Vec2.h>
#include "TileService.h"
#include "EnemyService.h"

class ServiceManager;

namespace {
	using namespace ShunLib;
	using namespace std;
}

#define SVC_Tile ServiceManager::GetInstance()->GetTileSVC()
#define SVC_Enemy ServiceManager::GetInstance()->GetEnemySVC()

class ServiceManager : public Singleton<ServiceManager>
{
	friend ShunLib::Singleton<ServiceManager>;

public:
	TileService* GetTileSVC(){ return TileService::GetInstance(); }
	EnemyService* GetEnemySVC() { return EnemyService::GetInstance(); }

};