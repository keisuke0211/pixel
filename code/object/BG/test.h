//========================================
// 
// テスト
// 
//========================================
// *** test.h ***
//========================================
#ifndef _TEST_H_	//このマクロ定義がされてなかったら
#define _TEST_H_	//２重インクルード防止のマクロ定義

#include "../../main.h"
#include "../object2D.h"

//****************************************
//　クラス
//****************************************
class CTest : public CObject2D
{
public:

	// ***** 構造体 *****

	// 共通情報
	struct Info
	{
		D3DXVECTOR3 pos;			// 位置
		D3DXVECTOR3 rot;			// 向き
		D3DXVECTOR2 size;			// 大きさ
		D3DXCOLOR col;				// 色
		int nLife;					// 寿命
		int nLifeMax;				// 寿命の最大値
	};

	// ***** 関数 *****
	CTest(int nPriority = PRIO_UI);
	~CTest();

	// -- メイン ------------------------------------------
	/* 初期化		*/HRESULT Init(void);
	/* 終了			*/void Uninit(void);
	/* 更新			*/void Update(void);
	/* 描画			*/void Draw(void);
	/* 生成			*/static CTest *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	static void TextSetTexture(LPDIRECT3DTEXTURE9 pTexture);

private:

	static LPDIRECT3DTEXTURE9 m_pTexture; // テクスチャ

	// ***** 変数 *****
	Info m_Info;		// 情報
};

#endif