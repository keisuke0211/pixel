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
// 前方宣言
//****************************************
class CTime;			// タイム
class CScore;			// スコア

						//****************************************
						// クラス
						//****************************************
class CGame : public CScene
{
	static const int MAX_TIME = 99;	// 制限時間
public:

	// ***** 関数 *****
	CGame();
	virtual~CGame();

	// -- メイン ------------------------------------------
	/* 初期化	*/HRESULT Init(void);
	/* 終了		*/void Uninit(void);
	/* 更新		*/void Update(void);
	/* 描画		*/void Draw(void);
	/* 生成		*/static CGame *Create(void);
	/* エネミー	*/void SetEnemy(void);

	// -- 読み込み ----------
	/* エネミー	*/static void LoodEnemy(void);
	/* ブロック */static void LoodBlock(void);

	// -- 取得 ------------------------
	/* タイム		*/static CTime *GetTime() { return m_pTime; }
	/* スコア		*/static CScore *GetScore() { return m_pScore; };
private:

	// ***** 変数 *****
	/* タイム		*/static CTime *m_pTime;
	/* スコア		*/static CScore *m_pScore;

};

#endif