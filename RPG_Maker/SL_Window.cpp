//************************************************/
//* @file  :SL_Window.cpp
//* @brief :�E�B���h�E�֘A�̍쐬�A�Ǘ�
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
/// �R���X�g���N�^�@�����ݒ�
/// </summary>
ShunLib::Window::Window():
	m_width(640.0f),
	m_height(480.0f),
	m_name(L"�^�C�g��")
{
	for (int i = 0; i < typeNum; i++)
	{
		m_game[i] = nullptr;
		m_swapChain[i] = nullptr;
		m_renderTargetView[i] = nullptr;
		m_depthStencilView[i] = nullptr;
	}

	//�X���b�v�`�F�C���̐ݒ�
	ZeroMemory(&m_sd, sizeof(m_sd));
	m_sd.BufferCount = 1;
	m_sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//32bit�J���[
	m_sd.BufferDesc.RefreshRate.Numerator = 60;         //�t���b�V�����[�g�@60fps
	m_sd.BufferDesc.RefreshRate.Denominator = 1;        //�o�b�N�o�b�t�@�̐�
	m_sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	m_sd.SampleDesc.Count = 1;
	m_sd.SampleDesc.Quality = 0;
	m_sd.Windowed = TRUE;

	//�[�x�X�e���V���r���[�̐ݒ�
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
/// �f�X�g���N�^�@�I������
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
/// 1�ڂ̃E�B���h�E���쐬
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
/// ��ڈȍ~�̃E�B���h�E���쐬
/// </summary>
HRESULT ShunLib::Window::CreateSecondWindow()
{
	//���ɍ쐬���ꂽ���̂���������폜
	SAFE_RELEASE(m_swapChain[DEBUGGER]);
	SAFE_RELEASE(m_renderTargetView[DEBUGGER]);
	SAFE_RELEASE(m_depthStencilView[DEBUGGER]);
	if (IsWindow(m_hWnd[DEBUGGER]))
	{
		DestroyWindow(m_hWnd[DEBUGGER]);
	}

	//�E�B���h�E�쐬
	if (FAILED(MakeWindow(DEBUGGER)))
	{
		return E_FAIL;
	}

	// �X���b�v�`�F�[���̍쐬
	IDXGIDevice1* pDXGI = NULL;
	IDXGIAdapter* pAdapter = NULL;
	IDXGIFactory* pFactory = NULL;

	m_device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&pDXGI);
	pDXGI->GetAdapter(&pAdapter);
	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pFactory);

	m_sd.BufferDesc.Width = (UINT)m_width;              //��ʉ���
	m_sd.BufferDesc.Height = (UINT)m_height;            //��ʏc��
	m_sd.OutputWindow = m_hWnd[DEBUGGER];
	pFactory->CreateSwapChain(m_device, &m_sd, &m_swapChain[DEBUGGER]);

	//�X���b�v�`�F�C���������Ă���o�b�N�o�b�t�@���擾
	ID3D11Texture2D *backBuffer;
	m_swapChain[DEBUGGER]->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);

	//�����_�[�^�[�Q�b�g�r���[�̍쐬
	//�����_�[�^�[�Q�b�g�ƃ��\�[�X���q�������
	m_device->CreateRenderTargetView(backBuffer, NULL, &m_renderTargetView[DEBUGGER]);

	//�[�x�X�e���V���r���[�̍쐬
	//Z�o�b�t�@�ƃX�e���V���o�b�t�@�ɑ΂���r���[
	m_descDepth.Width = (UINT)m_width;
	m_descDepth.Height = (UINT)m_height;
	m_device->CreateTexture2D(&m_descDepth, NULL, &m_texture2D);
	m_device->CreateDepthStencilView(m_texture2D, NULL, &m_depthStencilView[DEBUGGER]);

	//�����_�[�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���r���[���p�C�v���C���Ɋ֘A�t����
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView[DEBUGGER], m_depthStencilView[DEBUGGER]);


	//�o�b�N�o�b�t�@�̎Q�ƃJ�E���^���P���炷
	//���j���ł͂Ȃ�
	SAFE_RELEASE(backBuffer);

	return S_OK;
}

/// <summary>
/// DirectX3D�̏�����
/// </summary>
HRESULT ShunLib::Window::InitD3D()
{
	// �f�o�C�X�ƃX���b�v�`�F�[���̍쐬
	m_sd.BufferDesc.Width = (UINT)m_width;              //��ʉ���
	m_sd.BufferDesc.Height = (UINT)m_height;            //��ʏc��
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


	//�X���b�v�`�F�C���������Ă���o�b�N�o�b�t�@���擾
	ID3D11Texture2D *backBuffer;
	m_swapChain[EDITOR]->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);

	//�����_�[�^�[�Q�b�g�r���[�̍쐬
	//�����_�[�^�[�Q�b�g�ƃ��\�[�X���q�������
	m_device->CreateRenderTargetView(backBuffer, NULL, &m_renderTargetView[EDITOR]);

	//�o�b�N�o�b�t�@�̎Q�ƃJ�E���^���P���炷
	//���j���ł͂Ȃ�
	SAFE_RELEASE(backBuffer);


	//�[�x�X�e���V���r���[�̍쐬
	//Z�o�b�t�@�ƃX�e���V���o�b�t�@�ɑ΂���r���[
	m_descDepth.Width = (UINT)m_width;
	m_descDepth.Height = (UINT)m_height;

	m_device->CreateTexture2D(&m_descDepth, NULL, &m_texture2D);
	m_device->CreateDepthStencilView(m_texture2D, NULL, &m_depthStencilView[EDITOR]);

	//�����_�[�^�[�Q�b�g�r���[�Ɛ[�x�X�e���V���r���[���p�C�v���C���Ɋ֘A�t����
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView[EDITOR], m_depthStencilView[EDITOR]);

	//�r���[�|�[�g�̐ݒ�
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)m_width;  //��ʕ�
	vp.Height = (FLOAT)m_height;//��ʕ�
	vp.MinDepth = 0.0f;         //Z���̕�
	vp.MaxDepth = 1.0f;         //Z���̕�
	vp.TopLeftX = 0;            //����̍��W
	vp.TopLeftY = 0;            //����̍��W
	m_deviceContext->RSSetViewports(1, &vp);

	//���X�^���C�Y�ݒ�
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
/// �E�B���h�E�v���V�[�W��
/// �EOS���烁�b�Z�[�W���󂯎�菈��������
/// </summary>
LRESULT ShunLib::Window::MsgProc(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam)
{
	auto window = ShunLib::Window::GetInstance();

	auto hWD = window->WindouHandle(ShunLib::Window::WINDOW_TYPE::DEBUGGER);

	//�f�o�b�O�p
	if (hWnd == hWD)
	{
		return window->MsgProcDebugger(hWnd, iMag, wParam, lParam);
	}

	//�G�f�B�^�[�p
	return window->MsgProcEditor(hWnd, iMag, wParam, lParam);
}

/// <summary>
/// �E�B���h�E�v���V�[�W��
/// �EOS���烁�b�Z�[�W���󂯎�菈��������
/// </summary>
LRESULT CALLBACK ShunLib::Window::MsgProcEditor(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam)
{
	using namespace DirectX;

	switch (iMag)
	{
		//�L�[�������ꂽ
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

		//�E�B���h�E�������ꂽ
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	// ImGui�̃��b�Z�[�W
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

	//�s�v�ȃ��b�Z�[�W��OS�ɏ���������
	return DefWindowProc(hWnd, iMag, wParam, lParam);
}


/// <summary>
/// �E�B���h�E�v���V�[�W��
/// �EOS���烁�b�Z�[�W���󂯎�菈��������
/// </summary>
LRESULT CALLBACK ShunLib::Window::MsgProcDebugger(HWND hWnd, UINT iMag, WPARAM wParam, LPARAM lParam)
{
	using namespace DirectX;

	switch (iMag)
	{
		//�L�[�������ꂽ
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
		Keyboard::ProcessMessage(iMag, wParam, lParam);
		break;

	case WM_ACTIVATEAPP:
		Keyboard::ProcessMessage(iMag, wParam, lParam);


		//�E�B���h�E�������ꂽ
	case WM_DESTROY:
		this->DestroyDebugger();

		break;
	}

	//�s�v�ȃ��b�Z�[�W��OS�ɏ���������
	return DefWindowProc(hWnd, iMag, wParam, lParam);
}

/// <summary>
/// ���b�Z�[�W���[�v
/// </summary>
void ShunLib::Window::Run()
{
	//���b�Z�[�W�@0�ŏ�����
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	//���b�Z�[�W���[�v
	while (msg.message != WM_QUIT) {
		//OS���烁�b�Z�[�W������΃v���V�[�W���ɓn��
		//OS���烁�b�Z�[�W��������΃A�v���P�[�V�������X�V����
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {

			//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
			TranslateMessage(&msg);

			//���b�Z�[�W�𑗂�
			DispatchMessage(&msg);
		}
		else {
			ShunLib::KeyManager::GetInstance()->Update();

			//�Q�[���̍X�V
			GameUpdate();
			GameRender();
		}
	}
}

/// <summary>
/// �`�悷��E�B���h�E��ݒ�
/// </summary>
/// <param name="type"></param>
void ShunLib::Window::SetDrawingWindow(WINDOW_TYPE type)
{
	m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView[type], m_depthStencilView[type]);
}

/// <summary>
/// �A�v���P�[�V������ݒ�
/// </summary>
/// <param name="game"></param>
/// <param name="type"></param>
void ShunLib::Window::SetApp(AppBase * game, WINDOW_TYPE type)
{
	m_game[type] = game;
	m_game[type]->Initialize();
}

/// <summary>
/// �f�o�b�J�[���폜
/// </summary>
void ShunLib::Window::DestroyDebugger()
{
	DELETE_POINTER(m_game[DEBUGGER]);
}


/// <summary>
/// �Q�[���̍X�V
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
/// �Q�[���̕`��
/// </summary>
void ShunLib::Window::GameRender()
{
	//��ʃN���A
	Clear();

	//�Q�[���`��
	for (int i = 0; i < typeNum; i++)
	{
		if (m_game[i] != nullptr)
		{
			m_game[i]->Render();
		}
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@������
	for (int i = 0; i < typeNum; i++)
	{
		if (m_swapChain[i] != nullptr)
		{
			m_swapChain[i]->Present(0, 0);
		}
	}
}

/// <summary>
/// ��ʂ̃N���A
/// </summary>
void ShunLib::Window::Clear()
{
	//��ʂ̐F
	float color[4] = { 0,1,1,1 };

	for (int i = 0; i < typeNum; i++)
	{
		if (m_renderTargetView[i] != nullptr &&m_depthStencilView[i] != nullptr)
		{
			//��ʃN���A
			m_deviceContext->ClearRenderTargetView(m_renderTargetView[i], color);

			//�[�x�o�b�t�@�N���A
			m_deviceContext->ClearDepthStencilView(m_depthStencilView[i], D3D11_CLEAR_DEPTH, 1.0f, 0);
		}
	}
}


/// <summary>
/// �E�B���h�E�쐬
/// </summary>
HRESULT ShunLib::Window::MakeWindow(WINDOW_TYPE type)
{
	//�E�B���h�E���@0�ŏ�����
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(wc));

	//�E�B���h�E�̏���ݒ�
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = m_instApp;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = m_name;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//�E�B���h�E�̓o�^
	RegisterClassEx(&wc);

	//�E�B���h�E���쐬
	m_hWnd[type] = CreateWindow(m_name, m_name, WS_OVERLAPPEDWINDOW, 0, 0, (int)m_width, (int)m_height, 0, 0, m_instApp, 0);

	//�쐬�Ɏ��s������G���[
	if (!m_hWnd[type])return E_FAIL;

	//�E�B���h�E����ʂɕ\��
	ShowWindow(m_hWnd[type], SW_SHOW);
	UpdateWindow(m_hWnd[type]);
	return S_OK;
}
