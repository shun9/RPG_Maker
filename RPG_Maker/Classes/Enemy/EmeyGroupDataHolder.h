//************************************************/
//* @file  :EnemyGroupDataHolder.h
//* @brief :タイルの情報を保持する
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <vector>
#include <memory>
#include <string>
#include <utility>
#include <SL_Singleton.h>
#include <SL_Texture.h>
#include <SL_ConstantNumber.h>
#include "EnemyDataHolder.h"
#include <SL_Vec2.h>

class Enemy;

// 敵グループの情報
struct EnemyGroupData {
	int Id;

	std::string Name;

	// 画面表示座標とEnemyDataのリスト
	std::vector<std::pair<ShunLib::Vec2, EnemyData*>> enemyList;
};


// 敵グループの情報を保持する
class EnemyGroupDataHolder :public ShunLib::Singleton<EnemyGroupDataHolder>
{
	friend ShunLib::Singleton<EnemyGroupDataHolder>;

private:
	// 敵グループ種類一覧
	std::vector<std::unique_ptr<EnemyGroupData>> m_enemyGroupData;

public:
	EnemyGroupDataHolder() {}
	~EnemyGroupDataHolder() {}

	//データを追加する
	int AddData(std::unique_ptr<EnemyGroupData> data) {
		m_enemyGroupData.push_back(move(data));
		return (int)(m_enemyGroupData.size()) - 1;
	}

	//データ情報を返す
	//無ければnullptr
	EnemyGroupData* GetData(int id) {
		if (id > (int)(m_enemyGroupData.size()) - 1)return nullptr;
		return	m_enemyGroupData[id].get();
	}

	// 全データ取得
	const std::vector<std::unique_ptr<EnemyGroupData>>& GetTileList() {
		return m_enemyGroupData;
	}
};
