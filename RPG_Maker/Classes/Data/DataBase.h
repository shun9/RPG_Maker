//************************************************/
//* @file  :DataBase.h
//* @brief :‘S‚Ä‚Ìã•û‚ğ•Û‚·‚é
//* @date  :2017/09/30
//* @author:K.Yamamoto
//************************************************/
#pragma once
#include <memory>
#include <SL_Singleton.h>
#include "DataHolder.h"
#include "EmeyGroupData.h"
#include "EnemyData.h"
#include "TileData.h"

#define DB DataBase::GetInstance()

#define DB_Enemy DataBase::GetInstance()->getEnemyData()
#define DB_EnemyGroup DataBase::GetInstance()->getEnemyGroupData()
#define DB_Tile DataBase::GetInstance()->getTileData()


class DataBase :public ShunLib::Singleton<DataBase>
{
	friend ShunLib::Singleton<DataBase>;

private:
	DataBase() {
		this->Reset();
	}

	std::unique_ptr<DataHolder<EnemyData>> m_enemy;
	std::unique_ptr<DataHolder<EnemyGroupData>> m_enemyGroup;
	std::unique_ptr<DataHolder<TileData>> m_tile;

public:
	~DataBase() {}

	void Reset() {
		if(m_enemy==nullptr) m_enemy = std::make_unique<DataHolder<EnemyData>>();
		else m_enemy.reset(new DataHolder<EnemyData>());

		if (m_enemyGroup == nullptr) m_enemyGroup = std::make_unique<DataHolder<EnemyGroupData>>();
		else m_enemyGroup.reset(new DataHolder<EnemyGroupData>());

		if (m_tile == nullptr) m_tile = std::make_unique<DataHolder<TileData>>();
		else m_tile.reset(new DataHolder<TileData>());
	}

	DataHolder<EnemyData>& getEnemyData() { return *m_enemy.get(); }
	DataHolder<EnemyGroupData>& getEnemyGroupData() { return *m_enemyGroup.get(); }
	DataHolder<TileData>& getTileData() { return *m_tile.get(); }
};