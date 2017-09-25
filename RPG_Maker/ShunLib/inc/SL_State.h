//************************************************/
//* @file  :State.h
//* @brief :状態の基底クラス
//* @date  :2017/07/12
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_Singleton.h>

namespace ShunLib
{
	template <class T>
	class State
	{
	public:
		//開始処理
		virtual void Enter(T* obj) = 0;

		//実行処理
		virtual void Execute(T* obj) = 0;

		//終了処理
		virtual void Exit(T* obj) = 0;

	public:
		State(){}
		virtual ~State() {}

	};
}