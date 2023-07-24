//========================================
// 
// タイトル
// 
//========================================
// *** title.h ***
//========================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "../main.h"
#include "../manager.h"

//****************************************
// クラス
//****************************************
class CTitle : public CScene
{
public:

	// ***** 関数 *****
	CTitle();
	virtual~CTitle();

	// -- メイン ------------------------------------------
	/* 初期化		*/HRESULT Init(void);
	/* 終了			*/void Uninit(void);
	/* 更新			*/void Update(void);
	/* 描画			*/void Draw(void);
private:

	// ***** 変数 *****

};

#endif