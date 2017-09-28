//************************************************/
//* @file  :UIBase.cpp
//* @brief :UIの基底クラス
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

// 設定可能パラメーター ===================================================
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

// 日本語訳 =============================================
//アルファ;					  // グローバルアルファはImGuiのすべてに適用されます
//WindowPadding;			  // ウィンドウ内のパディング
//WindowMinSize;			  // 最小ウィンドウサイズ
//WindowRounding;			  // ウィンドウコーナーの丸めの半径。長方形のウィンドウを持つように0.0fに設定
//WindowTitleAlign;			  // タイトルバーテキストの整列
//ChildWindowRounding;		  // 子ウィンドウの四隅の丸めの半径。長方形のウィンドウを持つように0.0fに設定
//FramePadding;				  // フレーム付き矩形内のパディング（ほとんどのウィジェットで使用されます）
//FrameRounding;			  // フレームコーナーの丸めの半径。ほとんどのウィジェットで使用される長方形のフレームを持つには、0.0fに設定します。
//ItemSpacing;				  // ウィジェット/ライン間の水平方向と垂直方向の間隔
//ItemInnerSpacing;			  // 作成されたウィジェットの要素内での水平方向と垂直方向の間隔（スライダとそのラベルなど）
//TouchExtraPadding;		  // タッチ位置が正確ではないタッチベースのシステムのリアクションバウンディングボックスを拡張する。残念ながら、我々はウィジェットをソートしないので、オーバーラップの優先順位は常に最初のウィジェットに与えられます。だからこれをあまり大きくしないでください！
//インデントスペース。		  // 例えば水平のインデント。ツリーノードに入る。一般的に==（FontSize + FramePadding.x * 2）。
//ColumnsMinSpacing;		  // 2つの列間の最小水平間隔
//ScrollbarSize;			  // 垂直スクロールバーの幅、水平スクロールバーの高さ
//ScrollbarRounding;		  // スクロールバーのグラブ角の半径
//GrabMinSize;				  // スライダ/スクロールバーのグラブボックスの最小幅/高さ
//GrabRounding;				  // グラブ角の丸めの半径。長方形のスライダーグラブを持つには0.0fに設定します。
//DisplayWindowPadding;		  // ウィンドウの位置は、少なくともこの量だけ表示領域内に表示されるように固定されます。通常のウィンドウのみをカバーします。
//DisplaySafeAreaPadding;	  // 画面の端が見えない場合（たとえば、テレビで）、安全領域のパディングを増やします。通常のウィンドウと同様にポップアップ/ツールチップをカバーします。
//アンチエイリアシングライン;	  // ライン/ボーダーでアンチエイリアスを有効にする。あなたが本当にCPU / GPUでタイトな場合は無効にしてください。
//アンチエイリアシングシェイプ;  // 塗りつぶされた図形（丸い四角形、円など）でアンチエイリアスを有効にする
//CurveTessellationTol;		  //テッセレーション許容値。高度にテッセレーションされたカーブ（高品質、多角形）を減らし、品質を低下させます。
//色[ImGuiCol_COUNT];