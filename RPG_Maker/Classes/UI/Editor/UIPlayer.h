#pragma once
#include <vector>
#include <memory>
#include "EnemyData\UITableBase.h"
#include "UIInputIntBox.h"

class Player;

class UIPlayer :public UITableBase
{
private:
	Player* m_player;
	std::vector<std::unique_ptr<UIInputIntBox>> m_paramInputBox;
	std::vector<std::unique_ptr<UIInputIntBox>> m_posInputBox;
	int m_playerPosX;
	int m_playerPosY;

public:
	UIPlayer(Player* player) :UITableBase("Player"), m_player(player) { UIUpdate(); }
	~UIPlayer() {}

	virtual void DrawUpdate() override;
	void UIUpdate();

};