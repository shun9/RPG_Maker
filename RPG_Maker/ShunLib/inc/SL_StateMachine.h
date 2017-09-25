//************************************************/
//* @file  :SL_StateMachine.h
//* @brief :状態管理用のクラス
//* @date  :2017/07/12
//* @author:S.Katou
//************************************************/
#pragma once
#include <SL_State.h>
#include <SL_MacroConstants.h>

namespace ShunLib
{

	template <class T>
	class StateMachine
	{
	private:

		//現在の状態
		State<T>* m_currentState;

		//状態を使用するオブジェクト
		T* m_obj;

	public:
		StateMachine(T* obj) :m_currentState(nullptr), m_obj(obj) {}
		~StateMachine() { DELETE_POINTER(m_currentState); }

		/// <summary>
		/// 状態の切り替え
		/// </summary>
		/// <param name="state">次の状態</param>
		void ChangeState(State<T>* state) {
			//現在の状態が存在するならば終了処理
			if (m_currentState != nullptr) {
				m_currentState->Exit(m_obj);
				DELETE_POINTER(m_currentState);
			}
			m_currentState = state;
			m_currentState->Enter(m_obj);
		}

		/// <summary>
		/// 状態の更新処理
		/// </summary>
		void Update() {
			//現在の状態が存在するならば更新処理
			if (m_currentState != nullptr) {
				m_currentState->Execute(m_obj);
			}
		}
	};
}