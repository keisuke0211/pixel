//========================================
// 
// ブロック処理
// 
//========================================
//  *** block2D.h ***
//========================================
#ifndef _BLOCK2D_H_	// このマクロ定義がされていなかった時
#define _BLOCK2D_H_	// 二重インクルード防止のマクロを定義する

#include "../object2D.h"
#include "../../main.h"

//****************************************
// クラス定義
//****************************************
class CBlock2D :public CObject2D
{
public:

	// ***** 構造体 *****

	// プレイヤー情報
	typedef struct
	{
		D3DXVECTOR3 pos;	// 位置
		float fWidth;		// 幅
		float fHeight;		// 高さ
	} Info;

	// ***** 関数 *****
	CBlock2D(int nPriority = TYPE_BLOCK);	// コンストラクタ
	virtual ~CBlock2D();					// デストラクタ
	static HRESULT Load(char *pPath);		// テクスチャ読み込み
	static void Unload(void);				// テクスチャ破棄
	HRESULT Init(void);						// 初期化
	void Uninit(void);						// 終了
	void Update(void);						// 更新
	void Draw(void);						// 描画

	// 生成
	static CBlock2D *Create(D3DXVECTOR3 pos);

	/* 取得 */
	Info GetInfo() { return m_Info; }	// プレイヤー情報

private:

	// ***** 変数 *****
	Info m_Info;	// プレイヤー情報

	// ***** 静的変数 *****
	static LPDIRECT3DTEXTURE9 m_pTexture;	// 共有テクスチャ
};

#endif