//************************************************/
//* @file  :UIBase.cpp
//* @brief :UI�̊��N���X
//* @date  :2017/09/26
//* @author:K.Yamamoto
//************************************************/

#include "UIBase.h"

#include <SL_Texture.h>

#include "../../Game/Game.h"
#include "../../SL_Window.h"
#include "../../imgui/imgui.h"
#include "../../imgui/imgui_impl_dx11.h"

using namespace std;

UIBase::UIBase(const string& name)
	:m_name(name)
	,m_isActive(true)
{
}

UIBase::~UIBase()
{
}

void UIBase::DrawUpdate()
{

}

// �ݒ�\�p�����[�^�[ ===================================================
//Alpha;                      // Global alpha applies to everything in ImGui
//WindowPadding;              // Padding within a window
//WindowMinSize;              // Minimum window size
//WindowRounding;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows
//WindowTitleAlign;           // Alignment for title bar text
//ChildWindowRounding;        // Radius of child window corners rounding. Set to 0.0f to have rectangular windows
//FramePadding;               // Padding within a framed rectangle (used by most widgets)
//FrameRounding;              // Radius of frame corners rounding. Set to 0.0f to have rectangular frame (used by most widgets).
//ItemSpacing;                // Horizontal and vertical spacing between widgets/lines
//ItemInnerSpacing;           // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
//TouchExtraPadding;          // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
//IndentSpacing;              // Horizontal indentation when e.g. entering a tree node. Generally == (FontSize + FramePadding.x*2).
//ColumnsMinSpacing;          // Minimum horizontal spacing between two columns
//ScrollbarSize;              // Width of the vertical scrollbar, Height of the horizontal scrollbar
//ScrollbarRounding;          // Radius of grab corners for scrollbar
//GrabMinSize;                // Minimum width/height of a grab box for slider/scrollbar
//GrabRounding;               // Radius of grabs corners rounding. Set to 0.0f to have rectangular slider grabs.
//DisplayWindowPadding;       // Window positions are clamped to be visible within the display area by at least this amount. Only covers regular windows.
//DisplaySafeAreaPadding;     // If you cannot see the edge of your screen (e.g. on a TV) increase the safe area padding. Covers popups/tooltips as well regular windows.
//AntiAliasedLines;           // Enable anti-aliasing on lines/borders. Disable if you are really tight on CPU/GPU.
//AntiAliasedShapes;          // Enable anti-aliasing on filled shapes (rounded rectangles, circles, etc.)
//CurveTessellationTol;       // Tessellation tolerance. Decrease for highly tessellated curves (higher quality, more polygons), increase to reduce quality.
//Colors[ImGuiCol_COUNT];

// ���{��� =============================================
//�A���t�@;					  // �O���[�o���A���t�@��ImGui�̂��ׂĂɓK�p����܂�
//WindowPadding;			  // �E�B���h�E���̃p�f�B���O
//WindowMinSize;			  // �ŏ��E�B���h�E�T�C�Y
//WindowRounding;			  // �E�B���h�E�R�[�i�[�̊ۂ߂̔��a�B�����`�̃E�B���h�E�����悤��0.0f�ɐݒ�
//WindowTitleAlign;			  // �^�C�g���o�[�e�L�X�g�̐���
//ChildWindowRounding;		  // �q�E�B���h�E�̎l���̊ۂ߂̔��a�B�����`�̃E�B���h�E�����悤��0.0f�ɐݒ�
//FramePadding;				  // �t���[���t����`���̃p�f�B���O�i�قƂ�ǂ̃E�B�W�F�b�g�Ŏg�p����܂��j
//FrameRounding;			  // �t���[���R�[�i�[�̊ۂ߂̔��a�B�قƂ�ǂ̃E�B�W�F�b�g�Ŏg�p����钷���`�̃t���[�������ɂ́A0.0f�ɐݒ肵�܂��B
//ItemSpacing;				  // �E�B�W�F�b�g/���C���Ԃ̐��������Ɛ��������̊Ԋu
//ItemInnerSpacing;			  // �쐬���ꂽ�E�B�W�F�b�g�̗v�f���ł̐��������Ɛ��������̊Ԋu�i�X���C�_�Ƃ��̃��x���Ȃǁj
//TouchExtraPadding;		  // �^�b�`�ʒu�����m�ł͂Ȃ��^�b�`�x�[�X�̃V�X�e���̃��A�N�V�����o�E���f�B���O�{�b�N�X���g������B�c�O�Ȃ���A��X�̓E�B�W�F�b�g���\�[�g���Ȃ��̂ŁA�I�[�o�[���b�v�̗D�揇�ʂ͏�ɍŏ��̃E�B�W�F�b�g�ɗ^�����܂��B�����炱������܂�傫�����Ȃ��ł��������I
//�C���f���g�X�y�[�X�B		  // �Ⴆ�ΐ����̃C���f���g�B�c���[�m�[�h�ɓ���B��ʓI��==�iFontSize + FramePadding.x * 2�j�B
//ColumnsMinSpacing;		  // 2�̗�Ԃ̍ŏ������Ԋu
//ScrollbarSize;			  // �����X�N���[���o�[�̕��A�����X�N���[���o�[�̍���
//ScrollbarRounding;		  // �X�N���[���o�[�̃O���u�p�̔��a
//GrabMinSize;				  // �X���C�_/�X�N���[���o�[�̃O���u�{�b�N�X�̍ŏ���/����
//GrabRounding;				  // �O���u�p�̊ۂ߂̔��a�B�����`�̃X���C�_�[�O���u�����ɂ�0.0f�ɐݒ肵�܂��B
//DisplayWindowPadding;		  // �E�B���h�E�̈ʒu�́A���Ȃ��Ƃ����̗ʂ����\���̈���ɕ\�������悤�ɌŒ肳��܂��B�ʏ�̃E�B���h�E�݂̂��J�o�[���܂��B
//DisplaySafeAreaPadding;	  // ��ʂ̒[�������Ȃ��ꍇ�i���Ƃ��΁A�e���r�Łj�A���S�̈�̃p�f�B���O�𑝂₵�܂��B�ʏ�̃E�B���h�E�Ɠ��l�Ƀ|�b�v�A�b�v/�c�[���`�b�v���J�o�[���܂��B
//�A���`�G�C���A�V���O���C��;	  // ���C��/�{�[�_�[�ŃA���`�G�C���A�X��L���ɂ���B���Ȃ����{����CPU / GPU�Ń^�C�g�ȏꍇ�͖����ɂ��Ă��������B
//�A���`�G�C���A�V���O�V�F�C�v;  // �h��Ԃ��ꂽ�}�`�i�ۂ��l�p�`�A�~�Ȃǁj�ŃA���`�G�C���A�X��L���ɂ���
//CurveTessellationTol;		  //�e�b�Z���[�V�������e�l�B���x�Ƀe�b�Z���[�V�������ꂽ�J�[�u�i���i���A���p�`�j�����炵�A�i����ቺ�����܂��B
//�F[ImGuiCol_COUNT];