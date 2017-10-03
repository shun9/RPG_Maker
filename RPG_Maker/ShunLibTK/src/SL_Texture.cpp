//************************************************/
//* @file  :SL_Texture.cpp
//* @brief :画像描画用クラス
//* @date  :2017/07/10
//* @author:S.Katou
//************************************************/
#include <SL_Texture.h>
#include <SL_ConversionTK.h>
#include <SimpleMath.h>

using namespace ShunLib;

// デバイス
Microsoft::WRL::ComPtr<ID3D11Device>Texture::m_device;

//デバイスコンテキスト
Microsoft::WRL::ComPtr<ID3D11DeviceContext>Texture::m_context;


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デバイスの設定
//＋ーーーーーーーーーーーーーー＋
void Texture::SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device,
						Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
{
	m_device  = device;
	m_context = context;
}

//＋ーーーーーーーーーーーーーー＋
//｜機能  :コンストラクタ
//｜引数  :画像のパス(wchar_t*)
//＋ーーーーーーーーーーーーーー＋
Texture::Texture(const wchar_t* texture)
{
	m_path = texture;

	//テクスチャ読み込み
	DirectX::CreateWICTextureFromFile(m_device.Get(), texture, nullptr, m_texture.ReleaseAndGetAddressOf());

	//スプライトバッチ作成
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_context.Get());

	//ステート作成
	m_state = std::make_unique<DirectX::CommonStates>(m_device.Get());
}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :デストラクタ
//＋ーーーーーーーーーーーーーー＋
Texture::~Texture()
{

}


//＋ーーーーーーーーーーーーーー＋
//｜機能  :描画処理
//｜引数  :座標Ｘ  (float)
//｜引数  :座標Ｙ  (float)
//｜引数  :拡大率  (float)
//｜引数  :描画矩形(float)
//｜戻り値:なし(void)
//＋ーーーーーーーーーーーーーー＋
void Texture::Draw(float x, float y, float scale,const RECT* rect)
{
	using namespace DirectX;

	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_state->NonPremultiplied());

	m_spriteBatch->Draw(m_texture.Get(), XMFLOAT2(x, y), rect, Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT2(scale, scale));

	m_spriteBatch->End();
}

void ShunLib::Texture::Draw(const Vec2& pos, const Vec2& scale, const RECT * rect,const Vec2& origin)
{
	using namespace DirectX;

	m_spriteBatch->Begin(SpriteSortMode_Deferred, m_state->NonPremultiplied());

	m_spriteBatch->Draw(m_texture.Get(), XMFLOAT2(pos.m_x, pos.m_y), rect, Colors::White, 0.0f, XMFLOAT2(0.0f, 0.0f), XMFLOAT2(scale.m_x, scale.m_y));

	m_spriteBatch->End();
}