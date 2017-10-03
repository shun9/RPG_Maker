#pragma once
#include <SL_Singleton.h>
#include "Player.h"

class PlayerHolder:public ShunLib::Singleton<PlayerHolder>
{
	friend ShunLib::Singleton<PlayerHolder>;
private:
	Player* m_player;

public:
	Player* Get() { return m_player; }
	void Set(Player* p) { m_player = p; }

private:
	PlayerHolder() {}
	~PlayerHolder() {}
};
