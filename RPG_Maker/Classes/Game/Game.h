//************************************************/
//* @file  :Game.h
//* @brief :�G�f�B�^�[�ō쐬�����Q�[��
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include "../AppBase/AppBase.h"

class Map;
class Player;

//�Q�[���N���X
//���s�{�^���ō쐬
//�G�f�B�^�[�Ƃ͕ʂ̃E�B���h�E�ɕ`��
class Game : public AppBase
{
private:
	Map* m_map;
	Player* m_player;

public:
	Game();
	~Game();

	//��Ԃ̂��
	void Initialize()override;
	void Update    ()override;
	void Render    ()override;
	void Finalize  ()override;

	void SetMap(Map* map) {
		m_map = map;
	}
	void Player(Player* player) { m_player = player; }
private:

};