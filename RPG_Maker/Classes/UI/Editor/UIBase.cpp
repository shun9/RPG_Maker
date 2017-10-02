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
	, Active(true)
{
}

UIBase::~UIBase()
{
}

void UIBase::DrawUpdate()
{

}

// ウインドウの設定パラメータ ================================================
//デフォルト：0
//ImGuiWindowFlags_NoTitleBar = 1 << 0、//タイトルバーを無効にする
//ImGuiWindowFlags_NoResize = 1 << 1、//右下のグリップでユーザーのサイズ変更を無効にする
//ImGuiWindowFlags_NoMove = 1 << 2、//ユーザーがウィンドウを移動するのを無効にする
//ImGuiWindowFlags_NoScrollbar = 1 << 3、//スクロールバーを無効にする（ウィンドウはマウスまたはプログラムでスクロールできる）
//ImGuiWindowFlags_NoScrollWithMouse = 1 << 4、//マウスホイールで垂直方向にスクロールするユーザーを無効にする
//ImGuiWindowFlags_NoCollapse = 1 << 5、//ユーザがダブルクリックして折り畳むことを無効にする
//ImGuiWindowFlags_AlwaysAutoResize = 1 << 6、//すべてのウィンドウをすべてのフレームのコンテンツにサイズ変更する
//ImGuiWindowFlags_ShowBorders = 1 << 7、//ウィンドウとアイテムの周りに罫線を表示する
//ImGuiWindowFlags_NoSavedSettings = 1 << 8、//設定を.iniファイルにロード/保存しない
//ImGuiWindowFlags_NoInputs = 1 << 9、//マウスまたはキーボード入力の捕捉を無効にする
//ImGuiWindowFlags_MenuBar = 1 << 10、//メニューバーがあります
//ImGuiWindowFlags_Horizo​​ntalScrollbar = 1 << 11、//水平スクロールバーが表示されるようにします（デフォルトではオフ）。 SetNextWindowContentSize（ImVec2（width、0.0f））を使用できます。 Begin（）を呼び出して幅を指定します。 imgui_demoのコードを「水平スクロール」セクションで読み込みます。
//ImGuiWindowFlags_NoFocusOnAppearing = 1 << 12、//非表示状態から可視状態に遷移するときにフォーカスを無効にする
//ImGuiWindowFlags_NoBringToFrontOnFocus = 1 << 13、//フォーカスを取るときにウィンドウを前面に移動しないようにします（例えば、クリックするか、フォーカスをプログラム的に与えるなど）
//ImGuiWindowFlags_AlwaysVerticalScrollbar = 1 << 14、//常に垂直スクロールバーを表示する（ContentSize.y <Size.yの場合でも）
//ImGuiWindowFlags_AlwaysHorizo​​ntalScrollbar = 1 << 15、//常に水平スクロールバーを表示する（ContentSize.x <Size.xの場合でも）
//ImGuiWindowFlags_AlwaysUseWindowPadding = 1 << 16、//境界線を持たない子ウィンドウにstyle.WindowPaddingを使用するようにしました。（ボーダーなしの子ウィンドウではデフォルトで無視されます。
// [内部]
//ImGuiWindowFlags_ChildWindow = 1 << 22、//使用しないでください！ BeginChild（）による内部使用については、
//ImGuiWindowFlags_ComboBox = 1 << 23、//使用しないでください！ ComboBox（）による内部使用については、
//ImGuiWindowFlags_Tooltip = 1 << 24、//使用しないでください！ BeginTooltip（）による内部使用については、
//ImGuiWindowFlags_Popup = 1 << 25、//使用しないでください！ BeginPopup（）による内部使用については、
//ImGuiWindowFlags_Modal = 1 << 26、//使用しないでください！ BeginPopupModal（）による内部使用については、
//ImGuiWindowFlags_ChildMenu = 1 << 27 //使用しないでください！ BeginMenu（）による内部使用については、

// 色の設定可能フラグ =====================================================
//ImGuiColorEditFlags_NoAlpha = 1 << 1、// // ColorEdit、ColorPicker、ColorButton：Alphaコンポーネントを無視する（入力ポインタから3つのコンポーネントを読み込む）。
//ImGuiColorEditFlags_NoPicker = 1 << 2、// // ColorEdit：色付きの四角をクリックするとピッカーを無効にします。
//ImGuiColorEditFlags_NoOptions = 1 << 3、// // ColorEdit：入力/小プレビューを右クリックするとトグルオプションメニューが無効になります。
//ImGuiColorEditFlags_NoSmallPreview = 1 << 4、// // ColorEdit、ColorPicker：入力の隣に色付きの四角形プレビューを無効にします。 （例えば、入力のみを表示する）
//ImGuiColorEditFlags_NoInputs = 1 << 5、// // ColorEdit、ColorPicker：入力スライダ/テキストウィジェットを無効にします（小さなプレビュー色の四角形のみを表示するなど）。
//ImGuiColorEditFlags_NoTooltip = 1 << 6、// // ColorEdit、ColorPicker、ColorButton：プレビューを表示するときにツールチップを無効にします。
//ImGuiColorEditFlags_NoLabel = 1 << 7、// // ColorEdit、ColorPicker：インラインテキストラベルの表示を無効にします（ラベルはツールチップとピッカーに転送されます）。
//ImGuiColorEditFlags_NoSidePreview = 1 << 8、// // ColorPicker：ピッカーの右側でより大きなカラープレビューを無効にし、代わりに小さい色の四角形のプレビューを使用します。

// User Options（ウィジェットを右クリックしてそれらの一部を変更します）。 SetColorEditOptions（）を使用してアプリケーションのデフォルトを設定できます。基本的な考え方は、起動時にユーザーがSetColorEditOptions（）を選択または呼び出せるように、ほとんどの呼び出しでオーバーライドしたくないということです。
//ImGuiColorEditFlags_AlphaBar = 1 << 9、// // ColorEdit、ColorPicker：ピッカーの垂直アルファベット/グラデーションを表示します。
//ImGuiColorEditFlags_AlphaPreview = 1 << 10、// // ColorEdit、ColorPicker、ColorButton：不透明ではなく、チェッカーボード上に透明な色としてプレビューを表示します。
//ImGuiColorEditFlags_AlphaPreviewHalf = 1 << 11、// // ColorEdit、ColorPicker、ColorButton：不透明ではなく、半透明/半透明を表示します。
//ImGuiColorEditFlags_HDR = 1 << 12、// //（WIP）ColorEdit：現在、RGBA版では0.0f..1.0fの制限を無効にしています（注：ImGuiColorEditFlags_Floatフラグも使用します）。
//ImGuiColorEditFlags_RGB = 1 << 13、// [入力] // ColorEdit：RGB / HSV / HEXから1つを選択します。 ColorPicker：RGB / HSV / HEXを使用して任意の組み合わせを選択します。
//ImGuiColorEditFlags_HSV = 1 << 14、// [入力] // "
//ImGuiColorEditFlags_HEX = 1 << 15、// [入力] // "
//ImGuiColorEditFlags_Uint8 = 1 << 16、// [DataType] // ColorEdit、ColorPicker、ColorButton：_display_の値は、0..255にフォーマットされています。
//ImGuiColorEditFlags_Float = 1 << 17、// [DataType] // ColorEdit、ColorPicker、ColorButton：0.0f..1.0fとしてフォーマットされた_display_の値は、0..255の整数の代わりに浮動小数点になります。整数による値のラウンドトリップはありません。
//ImGuiColorEditFlags_PickerHueBar = 1 << 18、// [PickerMode] // ColorPicker：色相のバー、Sat / Valueの四角形。
//ImGuiColorEditFlags_PickerHueWheel = 1 << 19、// [PickerMode] // ColorPicker：色相のホイール、Sat / Valueの三角形。

//内部/マスク
//ImGuiColorEditFlags__InputsMask = ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_HSV | ImGuiColorEditFlags_HEX、
//ImGuiColorEditFlags__DataTypeMask = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_Float、
//ImGuiColorEditFlags__PickerMask = ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_PickerHueBar、
//ImGuiColorEditFlags__OptionsDefault = ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_PickerHueBar // SetColorEditOptions（）を使用してアプリケーションのデフォルトを変更する

// スタイルの設定可能パラメーター ===================================================
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