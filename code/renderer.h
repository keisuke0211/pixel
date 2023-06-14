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

	/* 取得 */
	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }	// デバイス

private:

	// ***** 関数 *****
	void DrawFPS(void);		// FPS表示

	// ***** 変数 *****
	D3DPRESENT_PARAMETERS m_d3dpp = {};	// プレゼンテーションパラメータ
	LPDIRECT3D9 m_pD3D;					// Direct3Dオブジェクトへのポインタ
	LPDIRECT3DDEVICE9 m_pD3DDevice;		// Direct3Dデバイスへのポインタ

	static LPD3DXFONT m_pFont;			// フォントへのポインタ
};
#endif