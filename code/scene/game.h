//========================================
// 
// ゲーム
// 
//========================================
// *** game.h ***
//========================================
#ifndef _GAME_H_
#define _GAME_H_

#include "../main.h"
#include "../manager.h"

//****************************************
// クラス
//****************************************
class CGame : public CScene
{
public:

	// ***** 関数 *****
	CGame();
	virtual~CGame();

	// -- メイン ------------------------------------------
	/* 初期化	*/HRESULT Init(void);
	/* 終了		*/void Uninit(void);
	/* 更新		*/void Update(void);
	/* 描画		*/void Draw(void);
	/* エネミー	*/void SetEnemy(void);

	// -- 読み込み ----------
	/* エネミー	*/static void LoodEnemy(void);
	/* ブロック */static void LoodBlock(void);

private:

	// ***** 変数 *****

};

#endif