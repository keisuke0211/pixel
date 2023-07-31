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

	// -- 設定 ------------------------
	/* 出口		*/static void SetExit(bool bExit) { m_bExit = bExit; }
	/* クリア	*/static void SetClear(bool bClear) { m_bClear = bClear; }

	// -- 取得 ------------------------
	/* タイム		*/static CTime *GetTime() { return m_pTime; }
	/* スコア		*/static CScore *GetScore() { return m_pScore; };
	/* 開始			*/static bool IsStart() { return m_bStart; }
	/* 出口			*/static bool IsExit() { return m_bExit; }
	/* クリア		*/static bool IsClear() { return m_bClear; }

private:

	// ***** 変数 *****
	/* タイム		*/static CTime *m_pTime;
	/* スコア		*/static CScore *m_pScore;

	D3DXVECTOR3 posV;			// 視点の保存
	D3DXVECTOR3 posR;			// 注視点の保存

	int m_nStartTime;		// 開始時間
	int m_nEndTime;			// 終了時間

	bool m_bEnd;			// 終了フラグ
	static bool m_bStart;	// 開始フラグ
	static bool m_bExit;	// 出口　（出口を開くかのフラク）
	static bool m_bClear;	// クリアフラグ
};

#endif