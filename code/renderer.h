//========================================
// 
// 描画処理
// 
//========================================
// *** renderer.h ***
//========================================
#include "main.h"

#ifndef _RENDERER_H_
#define _RENDERER_H_

//****************************************
// 前方宣言
//****************************************
class CMain;

//****************************************
// クラス
//****************************************
class CRenderer
{
public:

	// ***** 関数 *****

	CRenderer();
	~CRenderer();

	/* レンダラー */
	HRESULT Init(HWND hWnd, BOOL bWindow);	// 初期化
	void Uninit(void);						// 終了
	void Update(void);						// 更新
	void Draw(void);						// 描画
	void Load(void);						// 読み込み

	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	// デバイスの所得

private:

	/* 全体 */
	HRESULT InitAll(void);	// 初期化
	void UninitAll(void);	// 終了
	void UpdateAll(void);	// 更新
	void DrawAll(void);		// 描画
	void DrawFPS(void);		// FPS表示

	D3DPRESENT_PARAMETERS m_d3dpp = {};	// プレゼンテーションパラメータ
	LPDIRECT3D9 m_pD3D;					// Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice;		// Direct3Dデバイスへのポインタ

	static LPD3DXFONT m_pFont;			// フォントへのポインタ
};
#endif