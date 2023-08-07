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
class CPlayer;			// プレイヤー

//****************************************
// クラス
//****************************************
class CGame : public CScene
{
	static const int GAME_TIME = 60;	// 制限時間
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

	// -- 読み込み ----------
	/* エネミー	*/static void LoodEnemy(void);
	/* ブロック */static void LoodBlock(void);	

	// -- 取得 ------------------------
	/* プレイヤー	*/static CPlayer *GetPlayer() { return m_pPlayer; }
	/* タイム		*/static CTime *GetTime() { return m_pTime; }
	/* スコア		*/static CScore *GetScore() { return m_pScore; };
	
private:

	// ***** 変数 *****
	/* プレイヤー	*/static CPlayer *m_pPlayer;
	/* タイム		*/static CTime *m_pTime;
	/* スコア		*/static CScore *m_pScore;

	D3DXVECTOR3 m_rot;		// 向き
	float m_nMoveRot;		// 向きの加速度
	int m_nStartTime;		// 開始時間
	int m_nEndTime;			// 終了時間

	bool m_bEnd;			// 終了フラグ
};

#endif