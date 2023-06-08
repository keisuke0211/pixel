//========================================
//
// エフェクト【 2D 】
//
//========================================
// *** effect2D.h ***
//========================================
#ifndef _EFFECT2D_H_
#define _EFFECT2D_H_

#include "../../main.h"
#include "../object2D.h"

//****************************************
// クラス
//****************************************
class CEffect2D : public CObject2D
{
public:

	// ***** 定義 *****
	static const int MAX_TEXTURE = 50;	// テクスチャの最大数


	CEffect2D(int nPriority = TYPE_EFFECT);
	~CEffect2D();

	// *****  関数 *****

	static HRESULT Load(char *pPath);			// テクスチャの生成 
	static void Unload(void);					// テクスチャの破棄

	/* メイン */
	HRESULT Init(void);		// 初期化
	void Uninit(void);		// 終了
	void Update(void);		// 更新
	void Draw(void);		// 描画

	// 生成
	static CEffect2D *Create(void);

	/* 設定 */
	void SetLife(int nLife) { m_nLife = m_nLifeMax = nLife; }	// 寿命
	void SetEffColor(D3DXCOLOR col) { m_color = col; }			// 色

private:
	// ***** 変数 *****
	int m_nLife;		// 寿命
	int m_nLifeMax;		// 寿命最大値
	D3DXCOLOR m_color;	// 色

	// ***** 静的変数 *****
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];		// 共有テクスチャ
	static int m_nTexture;									// テクスチャの総数
};
#endif 