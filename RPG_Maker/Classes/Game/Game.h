//************************************************/
//* @file  :Game.h
//* @brief :エディターで作成したゲーム
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include "../AppBase/AppBase.h"

//ゲームクラス
//実行ボタンで作成
//エディターとは別のウィンドウに描画
class Game : public AppBase
{
public:
	Game();
	~Game();

	//定番のやつ
	void Initialize()override;
	void Update    ()override;
	void Render    ()override;
	void Finalize  ()override;

private:

};