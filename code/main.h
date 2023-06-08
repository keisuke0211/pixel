//========================================
// *** main.h ***
//========================================

#ifndef _MAIN_H_
#define _MAIN_H_             

#include<windows.h>
#include<stdlib.h>
#include<stdio.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<time.h>
#include<stdio.h>
#include<string.h>
#include<string>
#include"XInput.h"
#include"d3dx9.h"  //描画処理に必要
#define DIRECTINPUT_VERSION (0X0800) //ビルド時の警告対処用のマクロ
#include"dinput.h"//入力処理に必要//２重インクルード帽子のマクロを定義する
//========================================
// ライブラリ
//========================================

#pragma comment(lib,"d3d9.lib")		//描画処理に必要
#pragma comment(lib,"d3dx9.lib")	//[d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")	//DirectXコンポーネント（部品）使用に必要
#pragma comment(lib,"winmm.lib")	//システム時刻所得に必要
#pragma comment(lib,"dinput8.lib")	//入力処理に必要
#pragma comment(lib,"xinput.lib")	//入力処理に必要
#pragma comment(lib,"Opengl32.lib")	//フォグ処理に必要
#include"xaudio2.h"					//サウンド処理に必要
//========================================
// マクロ定義
//========================================
#define SCREEN_WIDTH		(1280.0f)														// ウインドウの幅
#define SCREEN_HEIGHT		(720.0f)														// ウインドウの高さ
#define SWITCH_TIME			(600)															// 切り替わる時間(1秒 = 60)
#define WINDOW_MODE			(false)															// ウインドウモードの切り替え
#define INIT_FLOAT			(0.0f)															// floatの初期値
#define INIT_RHW			D3DXVECTOR3(0.0f,1.0f,0.0f)										// RHWの初期化
#define INIT_D3DXVECTOR2	D3DXVECTOR2(0.0f,0.0f)											// D3DXVECTOR2の初期値
#define INIT_D3DXVECTOR3	D3DXVECTOR3(0.0f,0.0f,0.0f)										// D3DXVECTOR3の初期値
#define INIT_D3DXCOLOR		D3DXCOLOR(1,1,1,1)												// D3DXCOLORの初期値
#define TXT_MAX				(256)		// 文字列の最大数(汎用) PositionVec4
//========================================
// 情報構造体
//========================================

//頂点情報【 2D 】
typedef struct
{
	D3DXVECTOR3 pos;	//頂点座標
	float rhw;			//座標変換係数（1.0fで固定）
	D3DCOLOR col;		//頂点カラー
	D3DXVECTOR2 tex;	//テクスチャ座標
} VERTEX_2D;

// メイン処理の情報構造体
typedef struct
{
	HWND				hWnd;		// ウインドウハンドル(識別子)
	D3DXVECTOR3			windowPos;	// ウインドウの位置
}Main;

//========================================
// プロトタイプ宣言
//========================================
void WindowMode(bool bScreen);		// ウインドウのモードを切り替える
HWND *GetWindowHandle(void);
D3DXVECTOR3 GetWindowPos(void);
int GetFps(void);
#endif