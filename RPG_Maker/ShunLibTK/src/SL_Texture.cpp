//************************************************/
//* @file  :SL_Texture.cpp
//* @brief :�摜�`��p�N���X
//* @date  :2017/07/10
//* @author:S.Katou
//************************************************/
#include <SL_Texture.h>
#include <SL_ConversionTK.h>
#include <SimpleMath.h>

using namespace ShunLib;

// �f�o�C�X
Microsoft::WRL::ComPtr<ID3D11Device>Texture::m_device;

//�f�o�C�X�R���e�L�X�g
Microsoft::WRL::ComPtr<ID3D11DeviceContext>Texture::m_context;


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�o�C�X�̐ݒ�
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
void Texture::SetDevice(Microsoft::WRL::ComPtr<ID3D11Device> device,
						Microsoft::WRL::ComPtr<ID3D11DeviceContext> context)
{
	m_device  = device;
	m_context = context;
}

//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�R���X�g���N�^
//�b����  :�摜�̃p�X(wchar_t*)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Texture::Texture(const wchar_t* texture)
{
	m_path = texture;

	//�e�N�X�`���ǂݍ���
	DirectX::CreateWICTextureFromFile(m_device.Get(), texture, nullptr, m_texture.ReleaseAndGetAddressOf());

	//�X�v���C�g�o�b�`�쐬
	m_spriteBatch = std::make_unique<DirectX::SpriteBatch>(m_context.Get());

	//�X�e�[�g�쐬
	m_state = std::make_unique<DirectX::CommonStates>(m_device.Get());
}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�f�X�g���N�^
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
Texture::~Texture()
{

}


//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
//�b�@�\  :�`�揈��
//�b����  :���W�w  (float)
//�b����  :���W�x  (float)
//�b����  :�g�嗦  (float)
//�b����  :�`���`(float)
//�b�߂�l:�Ȃ�(void)
//�{�[�[�[�[�[�[�[�[�[�[�[�[�[�[�{
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