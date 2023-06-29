//========================================
// 
// 背景処理
// 
//========================================
// *** bg.h ***
//========================================
#ifndef _BG_H_
#define _BG_H_

#include "../../main.h"
#include "../object2D.h"


//****************************************
// クラス
//****************************************
class CBg : public CObject2D
{
public:

	// ***** 定義 ****
	static const int BG_MAX = 3;	// 背景の最大数

	// ***** 関数 *****
	CBg(int nPriority = TYPE_BG);
	virtual~CBg();

	/* メイン */

	// 生成
	static CBg *Create(D3DXVECTOR3 move, int nType);

	HRESULT Init(void);	// 初期化
	void Uninit(void);	// 終了
	void Update(void);	// 更新
	void Draw(void);	// 描画

private:
	// ***** 変数 *****
	D3DXVECTOR3 m_texPos;								// テクスチャの位置		
	D3DXVECTOR3 m_texMove;								// テクスチャの加算値
	int m_Type;											// 画像種類

};
#endif