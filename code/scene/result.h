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

	// 
	enum VERDICT
	{
		VERDICT_GAMECLEAR = 0,	// ゲームクリア
		VERDICT_GAMEOVER,		// ゲームオーバー
		VERDICT_MAX,
	};

	// ***** 関数 *****
	CResult();
	virtual~CResult();

	// -- メイン ------------------------------------------
	/* 初期化	*/HRESULT Init(void);
	/* 終了		*/void Uninit(void);
	/* 更新		*/void Update(void);
	/* 描画		*/void Draw(void);
	/* 生成		*/static CResult *Create(void);

	/* 判定		*/static void SetVerdict(VERDICT nVerdict) { verdict = nVerdict; }

private:

	// ***** 変数 *****
	static VERDICT verdict;	// 判定
};

#endif