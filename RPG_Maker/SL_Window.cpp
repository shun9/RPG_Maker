//************************************************/
//* @file  :SL_Window.cpp
//* @brief :ウィンドウ関連の作成、管理
//* @date  :2017/09/26
//* @author:S.Katou
//************************************************/
#include "SL_Window.h"
#include <SL_KeyManager.h>
#include <SL_Texture.h>
#include <d3d11.h>
#include <Keyboard.h>
#include <Mouse.h>
#include "Classes\AppBase\AppBase.h"

#include "Classes\imgui\imgui.h"
#include "Classes\imgui\imgui_impl_dx11.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam);

/// <summary>
/// コンストラクタ　初期設定
/// </summary>
ShunLib::Window::Window():
	m_width(640.0f),
	m_height(480.0f),
	m_name(L"タイトル")
{
	for (int i = 0; i < typeNum; i++)
	{
		m_game[i] = nullptr;
		m_swapChain[i] = nullptr;
		m_renderTargetView[i] = nullptr;
		m_depthStencilView[i] = nullptr;
	}

	//スワップチェインの設定
	ZeroMemory(&m_sd, sizeof(m_sd));
	m_sd.BufferCount = 1;
	m_sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//32bitカラー
	m_sd.BufferDesc.RefreshRate.Numerator = 60;         //フレッシュレート　60fps
	m_sd.BufferDesc.RefreshRate.Denominator = 1;        //バックバッファの数
	m_sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	m_sd.SampleDesc.Count = 1;
	m_sd.SampleDesc.Quality = 0;
	m_sd.Windowed = TRUE;

	//深度ステンシルビューの設定
	m_descDepth.MipLevels = 1;
	m_descDepth.ArraySize = 1;
	m_descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	m_descDepth.SampleDesc.Count = 1;
	m_descDepth.SampleDesc.Quality = 0;
	m_descDepth.Usage = D3D11_USAGE_DEFAULT;
	m_descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	m_descDepth.CPUAccessFlags = 0;
	m_descDepth.MiscFlags = 0;

}

/// <summary>
/// デストラクタ　終了処理
/// </summary>
ShunLib::Window::~Window() {
	for (int i = 0; i < typeNum; i++)
	{
		SAFE_RELEASE(m_swapChain[i]);
		SAFE_RELEASE(m_renderTargetView[i]);
	}

	SAFE_RELEASE(m_deviceContext);
	SAFE_RELEASE(m_texture2D);

	for (int i = 0; i < typeNum; i++)
	{
		SAFE_RELEASE(m_depthStencilView[i]);
	}

	SAFE_RELEASE(m_device);

	m_game[EDITOR]->Finalize();

	for (int i = 0; i < typeNum; i++)
	{
		//if (m_game[i] != nullptr)
		{
			//m_game[i]->Finalize();
		}
	}
}

/// <summary>
/// 1つ目のウィンドウを作成
/// </summary>
HRESULT ShunLib::Window::Create(HINSTANCE hInst)
{
	m_instApp = hInst;

	if (FAILED(MakeWindow(EDITOR)))
	{
		return E_FAIL;
	}

	return S_OK;
}

/// <summary>
/// 二つ目以降のウィンドウを作成
/// </summary>
HRESULT ShunLib::Window::CreateSecondWindow()
{
	//既に作成されたものが合ったら削除
	SAFE_RELEASE(m_swapChain[DEBUGGER]);
	SAFE_RELEASE(m_renderTargetView[DEBUGGER]);
	SAFE_RELEASE(m_depthStencilView[DEBUGGER]);
	if (IsWindow(m_hWnd[DEBUGGER]))
	{
		DestroyWindow(m_hWnd[DEBUGGER]);
	}

	//ウィンドウ作成
	if (FAILED(MakeWindow(DEBUGGER)))
	{
		return E_FAIL;
	}

	// スワップチェーンの作成
	IDXGIDevice1* pDXGI = NULL;
	IDXGIAdapter* pAdapter = NULL;
	IDXGIFactory* pFactory = NULL;

	m_device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&pDXGI);
	pDXGI->GetAdapter(&pAdapter);
	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pFactory);

	m_sd.BufferDesc.Width = (UINT)m_width;              //画面横幅
	m_sd.BufferDesc.Height = (UINT)m_height;            //画面縦幅
	m_sd.OutputWindow = m_hWnd[DEBUGGER];
	pFactory->CreateSwapChain(m_device, &m_sd, &m_swapChain[DEBUGGER]);

	//スワップチェインが持っているバックバッファを取得
	ID3D11Texture2D *backBuffer;
	m_swapChain[DEBUGGER]->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);

	//レンダーターゲットビューの作成
	//レンダーターゲットとリソースを繋げるもの
	m_device->CreateRenderTargetView(backBuffer, NULL, &m_renderTargetView[DEBUGGER]);

	//深度ステンシルビューの作成
	//Zバッファとステンシルバッファに対するビュー
	m_descDepth.Width = (UINT)m_width;
	m_descDepth.Height = (UINT)m_height;
	m_device->CreateTexture2D(&m_descDepth, NULL, &m_texture2D);
	m_device->CreateDepthStencilView(m_texture2D, NULL, &m_depthStencilView[DEBUGGER]);

	//レンダーターゲットビューと深度ステンシルビューをパイプラインに関連付ける
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView[DEBUGGER], m_depthStencilView[DEBUGGER]);


	//バックバッファの参照カウンタを１つ減らす
	//※破棄ではない
	SAFE_RELEASE(backBuffer);

	return S_OK;
}

/// <summary>
/// DirectX3Dの初期化
/// </summary>
HRESULT ShunLib::Window::InitD3D()
{
	// デバイスとスワップチェーンの作成
	m_sd.BufferDesc.Width = (UINT)m_width;              //画面横幅
	m_sd.BufferDesc.Height = (UINT)m_height;            //画面縦幅
	m_sd.OutputWindow = m_hWnd[EDITOR];

	D3D_FEATURE_LEVEL featureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL* featureLevel = NULL;


	auto result = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		&featureLevels,
		1,
		D3D11_SDK_VERSION,
		&m_sd,
		&m_swapChain[EDITOR],
		&m_device,
		featureLevel,
		&m_deviceContext);

	if (FAILED(result))return FALSE;


	//スワップチェインが持っているバックバッファを取得
	ID3D11Texture2D *backBuffer;
	m_swapChain[EDITOR]->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);

	//レンダーターゲットビューの作成
	//レンダーターゲットとリソースを繋げるもの
	m_device->CreateRenderTargetView(backBuffer, NULL, &m_renderTargetView[EDITOR]);

	//バックバッファの参照カウンタを１つ減らす
	//※破棄ではない
	SAFE_RELEASE(backBuffer);


	//深度ステンシルビューの作成
	//Zバッファとステンシルバッファに対するビュー
	m_descDepth.Width = (UINT)m_width;
	m_descDepth.Height = (UINT)m_height;

	m_device->CreateTexture2D(&m_descDepth, NULL, &m_texture2D);
	m_device->CreateDepthStencilView(m_texture2D, NULL, &m_depthStencilView[EDITOR]);

	//レンダーターゲットビューと深度ステンシルビューをパイプラインに関連付ける
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView[EDITOR], m_depthStencilView[EDITOR]);

	//ビューポートの設定
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)m_width;  //画面幅
	vp.Height = (FLOAT)m_height;//画面幅
	vp.MinDepth = 0.0f;         //Z軸の幅
	vp.MaxDepth = 1.0f;         //Z軸の幅
	vp.TopLeftX = 0;            //左上の座標
	vp.TopLeftY = 0;            //左上の座標
	m_deviceContext->RSSetViewports(1, &vp);

	//ラスタライズ設定
	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));

	rd.CullMode = D3D11_CULL_NONE;
	rd.FillMode = D3D11_FILL_SOLID;

	ID3D11RasterizerState* irs = NULL;
	m_device->CreateRasterizerState(&rd, &irs);
	m_deviceContext->RSSetState(irs);
	SAFE_RELEASE(irs);

	return S_OK;
}

/// <summary>
/// ウィンドウプロシージャ
/// ・OSからメッセージを受け取り処理をする
/// </summary>
LRESULT ShunLib::Window::MsgProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam)
{
	auto window = ShunLib::Window::GetInstance();

	auto hWD = window->WindouHandle(ShunLib::Window::WINDOW_TYPE::DEBUGGER);

	//デバッグ用
	if (hWnd == hWD)
	{
		return window->MsgProcDebugger(hWnd, iMag, wParam, lParam);
	}

	//エディター用
	return window->MsgProcEditor(hWnd, iMag, wParam, lParam);
}

/// <summary>
/// ウィンドウプロシージャ
/// ・OSからメッセージを受け取り処理をする
/// </summary>
LRESULT CALLBACK ShunLib::Window::MsgProcEditor(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam)
{
	using namespace DirectX;

	switch (iMag)
	{
		//キーが押された
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard::ProcessMessage(iMag, wParam, lParam);
		break;

	case WM_ACTIVATEAPP:
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
		Keyboard::ProcessMessage(iMag, wParam, lParam);
		Mouse::ProcessMessage(iMag, wParam, lParam);
		break;

		//ウィンドウが消された
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	// ImGuiのメッセージ
	ImGuiIO& io = ImGui::GetIO();
	switch (iMag)
	{
	case WM_LBUTTONDOWN:
		io.MouseDown[0] = true;
		break;
	case WM_LBUTTONUP:
		io.MouseDown[0] = false;
		break;
	case WM_RBUTTONDOWN:
		io.MouseDown[1] = true;
		break;
	case WM_RBUTTONUP:
		io.MouseDown[1] = false;
		break;
	case WM_MBUTTONDOWN:
		io.MouseDown[2] = true;
		break;
	case WM_MBUTTONUP:
		io.MouseDown[2] = false;
		break;
	case WM_MOUSEWHEEL:
		io.MouseWheel += GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? +1.0f : -1.0f;
		break;
	case WM_MOUSEMOVE:
		io.MousePos.x = (signed short)(lParam);
		io.MousePos.y = (signed short)(lParam >> 16);
		break;
	case WM_KEYDOWN:
		if (wParam < 256)
			io.KeysDown[wParam] = 1;
		break;
	case WM_KEYUP:
		if (wParam < 256)
			io.KeysDown[wParam] = 0;
		break;
	case WM_CHAR:
		// You can also use ToAscii()+GetKeyboardState() to retrieve characters.
		if (wParam > 0 && wParam < 0x10000)
			io.AddInputCharacter((unsigned short)wParam);
		break;
	}

	//不要なメッセージをOSに処理させる
	return DefWindowProc(hWnd, iMag, wParam, lParam);
}


/// <summary>
/// ウィンドウプロシージャ
/// ・OSからメッセージを受け取り処理をする
/// </summary>
LRESULT CALLBACK ShunLib::Window::MsgProcDebugger(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam)
{
	using namespace DirectX;

	switch (iMag)
	{
		//キーが押された
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard::ProcessMessage(iMag, wParam, lParam);
		break;

	case WM_ACTIVATEAPP:
		Keyboard::ProcessMessage(iMag, wParam, lParam);


		//ウィンドウが消された
	case WM_DESTROY:
		this->DestroyDebugger();

		break;
	}

	//不要なメッセージをOSに処理させる
	return DefWindowProc(hWnd, iMag, wParam, lParam);
}

/// <summary>
/// メッセージループ
/// </summary>
void ShunLib::Window::Run()
{
	//メッセージ　0で初期化
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	//メッセージループ
	while (msg.message != WM_QUIT) {
		//OSからメッセージがあればプロシージャに渡す
		//OSからメッセージが無ければアプリケーションを更新する
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

			//仮想キーメッセージを文字メッセージへ変換
			TranslateMessage(&msg);

			//メッセージを送る
			DispatchMessage(&msg);
		}
		else {
			ShunLib::KeyManager::GetInstance()->Update();

			//ゲームの更新
			GameUpdate();
			GameRender();
		}
	}
}

/// <summary>
/// 描画するウィンドウを設定
/// </summary>
/// <param name="type"></param>
void ShunLib::Window::SetDrawingWindow(WINDOW_TYPE type)
{
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView[type], m_depthStencilView[type]);
}

/// <summary>
/// アプリケーションを設定
/// </summary>
/// <param name="game"></param>
/// <param name="type"></param>
void ShunLib::Window::SetApp(AppBase * game, WINDOW_TYPE type)
{
	m_game[type] = game;
	m_game[type]->Initialize();
}

/// <summary>
/// デバッカーを削除
/// </summary>
void ShunLib::Window::DestroyDebugger()
{
	DELETE_POINTER(m_game[DEBUGGER]);
}


/// <summary>
/// ゲームの更新
/// </summary>
void ShunLib::Window::GameUpdate()
{
	for (int i = 0; i < typeNum; i++)
	{
		if (m_game[i] != nullptr)
		{
			m_game[i]->Update();
		}
	}
}

/// <summary>
/// ゲームの描画
/// </summary>
void ShunLib::Window::GameRender()
{
	//画面クリア
	Clear();

	//ゲーム描画
	for (int i = 0; i < typeNum; i++)
	{
		if (m_game[i] != nullptr)
		{
			m_game[i]->Render();
		}
	}

	//バックバッファとフロントバッファを交換
	for (int i = 0; i < typeNum; i++)
	{
		if (m_swapChain[i] != nullptr)
		{
			m_swapChain[i]->Present(0, 0);
		}
	}
}

/// <summary>
/// 画面のクリア
/// </summary>
void ShunLib::Window::Clear()
{
	//画面の色
	float color[4] = { 0,1,1,1 };

	for (int i = 0; i < typeNum; i++)
	{
		if (m_renderTargetView[i] != nullptr &&m_depthStencilView[i] != nullptr)
		{
			//画面クリア
			m_deviceContext->ClearRenderTargetView(m_renderTargetView[i], color);

			//深度バッファクリア
			m_deviceContext->ClearDepthStencilView(m_depthStencilView[i], D3D11_CLEAR_DEPTH, 1.0f, 0);
		}
	}
}


/// <summary>
/// ウィンドウ作成
/// </summary>
HRESULT ShunLib::Window::MakeWindow(WINDOW_TYPE type)
{
	//ウィンドウ情報　0で初期化
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	//ウィンドウの情報を設定
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = m_instApp;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = m_name;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//ウィンドウの登録
	RegisterClassEx(&wc);

	//ウィンドウを作成
	m_hWnd[type] = CreateWindow(m_name, m_name, WS_OVERLAPPEDWINDOW, 0, 0, (int)m_width, (int)m_height, 0, 0, m_instApp, 0);

	//作成に失敗したらエラー
	if (!m_hWnd[type])return E_FAIL;

	//ウィンドウを画面に表示
	ShowWindow(m_hWnd[type], SW_SHOW);
	UpdateWindow(m_hWnd[type]);
	return S_OK;
}
