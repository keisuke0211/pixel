//========================================
// 
// マルチ背景処理
// 
//========================================
// *** bg_Multi.h ***
//========================================
#ifndef _BG_MULTI_H_
#define _BG_MULTI_H_

#include "../main.h"
#include "object.h"
//****************************************
// 前方宣言
//****************************************
class CBg;

//****************************************
// クラス
//****************************************
class CBgMulti : public CObject
{
public:

	// ***** 関数 *****
	CBgMulti(int nPriority = TYPE_BG);
	virtual~CBgMulti();

	// 生成
	static CBgMulti *Create(D3DXVECTOR3 move, int nType);

	/* メイン */
	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画

private:

	// ***** 定義 *****
	static const int BG_MAX = 3;	// 背景の最大数

	// ***** 変数 *****
	CBg *m_apBg[BG_MAX];		// 背景のポインタ配列
	D3DXVECTOR3 m_move;
	int m_nType;

	// ***** 静的変数 *****
	static int m_nNumBg;			// 背景の数

};
#endif