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

	public:
		enum WINDOW_TYPE{
			EDITOR = 0,
			DEBUGGER,
			typeNum,
		};

	private:
		//ウィンドウサイズ
		float m_width[typeNum];         //横
		float m_height[typeNum];        //縦
		WCHAR* m_name[typeNum];//ウィンドウ名
		HWND m_hWnd[typeNum];  //ウィンドウハンドル
		HINSTANCE m_instApp;   //このウィンドウを作成したアプリケーション

		//全体で１つ
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_deviceContext;
		ID3D11Texture2D* m_texture2D;
		DXGI_SWAP_CHAIN_DESC m_sd;//スワップチェインの設定
		D3D11_TEXTURE2D_DESC m_descDepth;//深度ステンシルビューの設定

		//ウィンドウの数だけ必要
		IDXGISwapChain* m_swapChain[typeNum];
		ID3D11RenderTargetView* m_renderTargetView[typeNum];
		ID3D11DepthStencilView* m_depthStencilView[typeNum];

		//エディターと作成したゲーム
		AppBase* m_game[typeNum];

	public:
		//ウィンドウ作成
		HRESULT Create(HINSTANCE);

		//二つ目以降のウィンドウ作成
		HRESULT CreateSecondWindow();

		//DirectX関連の初期化
		HRESULT InitD3D();

		//受け取り用プロシージャ
		LRESULT CALLBACK MsgProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam);

		//エディター用
		LRESULT CALLBACK MsgProcEditor(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam);

		//デバッガー用プロシージャ
		LRESULT CALLBACK MsgProcDebugger(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam);

		//メッセージループ
		void Run();

		//描画するウィンドウの設定
		void SetDrawingWindow(WINDOW_TYPE);

		//Setter
		void Width(float width) { m_width[EDITOR] = width; }
		void Height(float height) { m_height[EDITOR] = height; }
		void Name(WCHAR* name,WINDOW_TYPE type) { m_name[type] = name; }
		void SetApp(AppBase* game, WINDOW_TYPE type);

		//Getter
		float Width() { return m_width[EDITOR]; }
		float Height() { return m_height[EDITOR]; }
		WCHAR* Name(WINDOW_TYPE type) { return m_name[type]; }
		HWND WindouHandle(WINDOW_TYPE type) { return m_hWnd[type]; }  //ウィンドウハンドル

		ID3D11Device* Device() { return m_device; }
		ID3D11DeviceContext* DeviceContext() { return m_deviceContext; }


		//デバッガーを消す
		void DestroyDebugger();

	private:
		//コンストラクタ＆デストラクタ
		//シングルトンのため隠蔽
		Window();

		~Window();

		//ゲームの更新
		void GameUpdate();
		void GameRender();

		//画面クリア
		void Clear();

		HRESULT MakeWindow(WINDOW_TYPE type);

	};
}