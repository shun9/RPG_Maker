//************************************************/
//* @file  :SL_Window.h
//* @brief :ウィンドウ関連の作成、管理
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#pragma once
#include <Windows.h>
#include <SL_Singleton.h>

#include <d3d11.h>
#include <d3dcompiler.h>

class AppBase;

namespace ShunLib
{
	class Window :public Singleton<Window>
	{
		friend Singleton<Window>;

		enum WINDOW_TYPE{
			EDITOR = 0,
			DEBUGER,
			typeNum,
		};

	private:
		//ウィンドウサイズ
		float m_width;         //横
		float m_height;        //縦
		WCHAR* m_name;         //ウィンドウ名
		HWND m_hWnd[typeNum];  //ウィンドウハンドル
		HINSTANCE m_instApp;   //このウィンドウを作成したアプリケーション

		//全体で１つ
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_deviceContext;
		IDXGISwapChain* m_swapChain;
		ID3D11RenderTargetView* m_recderTargetView;
		ID3D11DepthStencilView* m_depthStencilView;
		ID3D11Texture2D* m_texture2D;

		//エディターと作成したゲーム
		AppBase* m_game[typeNum];

	public:
		//ウィンドウ作成
		HRESULT Create(HINSTANCE);

		HRESULT CreateSecondWindow();

		//DirectX関連の初期化
		HRESULT InitD3D();

		//プロシージャ
		LRESULT CALLBACK MsgProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam);

		//メッセージループ
		void Run();

		//Setter
		void Width(float width) { m_width = width; }
		void Height(float height) { m_height = height; }
		void Name(WCHAR* name) { m_name = name; }
		void SetApp(AppBase* game, WINDOW_TYPE type);

		//Getter
		float Width() { return m_width; }
		float Height() { return m_height; }
		WCHAR* Name() { return m_name; }
		ID3D11Device* Device() { return m_device; }
		ID3D11DeviceContext* DeviceContext() { return m_deviceContext; }

	private:
		//コンストラクタ＆デストラクタ
		//シングルトンのため隠蔽
		Window() :
			m_width (640.0f),
			m_height(480.0f),
			m_name  (L"タイトル"){
			for (int i = 0; i < typeNum; i++)
			{
				m_game[i] = nullptr;

			}
		}

		~Window();

		//ゲームの更新
		void GameUpdate();
		void GameRender();

		//画面クリア
		void Clear();
	};
}