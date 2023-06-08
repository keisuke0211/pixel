//========================================
// 
// 爆発処理
// 
//========================================
// *** explosion.h ***
//========================================
#ifndef _EXPLOSION_H_	//このマクロ定義がされてなかったら
#define _EXPLOSION_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "../main.h"
#include "object2D.h"

//==================================================
// 定義
//==================================================
class CExplosion : public CObject2D
{
public:

	// ***** 定義 *****
	static const int MAX_TEXTURE = 50;	// テクスチャの最大数

	// ***** 構造体 *****
	typedef struct
	{
		D3DXVECTOR3 pos;//位置
		D3DXCOLOR col;//色
		int nCounterAnim;//アニメーションカウンター
		int nPatternAnim;//アニメーションパターンNo.
		int nLife;
	}Info;

	// ***** 関数 *****
	CExplosion(int nPriority = TYPE_EFFECT);		// デフォルトコンストラクタ
	~CExplosion();		// デストラクタ

	/* メイン */
	static HRESULT Load(char *pPath);			// テクスチャの生成 
	static void Unload(void);					// テクスチャの破棄

	// 生成
	static CExplosion *Create(D3DXVECTOR3 pos);


	HRESULT Init(void);				// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画

	/* 取得 */
	Info GetInfo() { return m_Info; }	// プレイヤー情報

private:
	// ***** 変数 *****
	Info m_Info;	// 情報

	// ***** 静的変数 *****
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	// 共有テクスチャ
	static int m_nTexture;								// テクスチャの数
};

#endif // !_TEXTURE_H_
