//========================================
// 
// リザルト
// 
//========================================
// *** result.h ***
//========================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "../main.h"
#include "../manager.h"

//****************************************
// クラス
//****************************************
class CResult : public CScene
{
public:

	// ***** 関数 *****
	CResult();
	virtual~CResult();

	// -- メイン ------------------------------------------
	/* 初期化	*/HRESULT Init(void);
	/* 終了		*/void Uninit(void);
	/* 更新		*/void Update(void);
	/* 描画		*/void Draw(void);
private:

	// ***** 変数 *****

};

#endif