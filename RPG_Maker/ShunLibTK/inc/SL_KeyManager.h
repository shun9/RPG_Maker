//************************************************/
//* @file  :KeyManager.h
//* @brief :キーボードの状態を管理するクラス
//* @date  :2017/08/02
//* @author:S.Katou
//************************************************/
#pragma once
#include <d3d11.h>
#include <Keyboard.h>
#include <vector>
#include <SL_Singleton.h>

namespace ShunLib
{
	class KeyManager : public Singleton<KeyManager>
	{
		friend Singleton<KeyManager>;

	public:
		enum KEY_CODE
		{
			A = DirectX::Keyboard::Keys::A,
			C = DirectX::Keyboard::Keys::C,
			E = DirectX::Keyboard::Keys::E,
			L = DirectX::Keyboard::Keys::L,
			P = DirectX::Keyboard::Keys::P,
			S = DirectX::Keyboard::Keys::S,
			Z     = DirectX::Keyboard::Keys::Z,
			X     = DirectX::Keyboard::Keys::X,
			LEFT  = DirectX::Keyboard::Keys::Left,
			UP    = DirectX::Keyboard::Keys::Up,
			RIGHT = DirectX::Keyboard::Keys::Right,
			DOWN  = DirectX::Keyboard::Keys::Down ,
			SPACE = DirectX::Keyboard::Keys::Space,
			L_CTRL = DirectX::Keyboard::Keys::LeftControl,
			R_CTRL = DirectX::Keyboard::Keys::LeftControl,
		};

	private:
		std::unique_ptr<DirectX::Keyboard>m_key;
		DirectX::Keyboard::State m_state;
		DirectX::Keyboard::KeyboardStateTracker m_tracker;

	public:
		//更新処理
		void Update() {
			m_state = m_key->GetState();
			m_tracker.Update(m_state);
		}

		//押されているかどうか
		bool IsPushed(KEY_CODE key) {
			bool pushed = false;
			pushed = m_state.IsKeyDown(static_cast<DirectX::Keyboard::Keys>(key));
			return pushed;
		}

		//トリガー
		bool IsTracker(KEY_CODE key) { return m_tracker.IsKeyPressed(static_cast<DirectX::Keyboard::Keys>(key)); }

	private:
		KeyManager() {
			m_key = std::make_unique<DirectX::Keyboard>();
		}

	};
}