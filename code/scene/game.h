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
class CTime;	// タイム
class CScore;	// スコア
class CPlayer;	// プレイヤー
class CText;	// テキスト

//****************************************
// クラス
//****************************************
class CGame : public CScene
{
	static const int GAME_TIME = 90;				// 制限時間
	static const int ADDTIME_MAX = 120;				// ボーナスをスコアに加算する時間
	static const int MAX_CUBE = 30;					// ステージで配置出来るキューブの制限
	static const char* SIDE_STAGE_EASY_FILE;		// 側面のファイル(STAGE1)
	static const char* SIDE_STAGE_NORMAL_FILE;		// 側面のファイル(STAGE2)
	static const char* SIDE_STAGE_DIFFICULT_FILE;	// 側面のファイル(STAGE3)

	static const char* FLOOR_STAGE_EASY_FILE;		// 床のファイル(STAGE1)
	static const char* FLOOR_STAGE_NORMAL_FILE;		// 床のファイル(STAGE2)
	static const char* FLOOR_STAGE_DIFFICULT_FILE;	// 床のファイル(STAGE3)

	static const char* BLOCK_STAGE_EASY_FILE;		// ブロックのファイル(STAGE1)
	static const char* BLOCK_STAGE_NORMAL_FILE;		// ブロックのファイル(STAGE2)
	static const char* BLOCK_STAGE_DIFFICULT_FILE;	// ブロックのファイル(STAFE3)

	static const char* ENEMY_STAGE_EASY_FILE;		// エネミーのファイル(STAGE1)
	static const char* ENEMY_STAGE_NORMAL_FILE;		// エネミーのファイル(STAGE2)
	static const char* ENEMY_STAGE_DIFFICULT_FILE;	// エネミーのファイル(STAFE3)

	static const int TIME_SCORE = 100;	// １秒のスコアの加算値
	static const int CUBE_SCORE = 10;	// １個のスコアの加算値

public:

	// ***** 列挙型 *****

	// ステージ
	enum Stage
	{
		Stage_EASY = 0,		// 初級
		Stage_NORMAL,		// 中級
		Stage_DIFFICULT,	// 難しい
		Stage_MAX
	};

	// ***** 関数 *****
	CGame();
	virtual~CGame();

	// -- メイン ------------------------------------------
	/* 初期化	*/HRESULT Init(void);
	/* 終了		*/void Uninit(void);
	/* 更新		*/void Update(void);
	/* 描画		*/void Draw(void);
	/* 生成		*/static CGame *Create(void);
	
	// -- 読み込み ------------------------------------------
	/* 背景　天井	*/static void LoodCeiling(void);
	/* 背景　側面	*/static void LoodSide(void);
	/* 床			*/static void LoodFloor(void);
	/* ブロック		*/static void LoodBlock(void);
	/* エネミー		*/static void LoodEnemy(void);

	// -- 設定 ------------------------------------------
	/* ステージ選択	*/static void SetStage(int nStage);

	// -- 取得 ------------------------------------------
	/* プレイヤー	*/static CPlayer *GetPlayer() { return m_pPlayer; }
	/* タイム		*/static CTime *GetTime() { return m_pTime; }
	/* スコア		*/static CScore *GetScore() { return m_pScore; };
	/* 時間フラグ	*/static bool IsTime() { return m_bTime; }
	
private:

	// ***** 列挙型 *****

	// リザルト演出
	enum Rst
	{
		RST_TIME = 0,	// タイムボーナス(テキスト)
		RST_TIME_CALC,	// タイムボーナス(計算)
		RST_CUBE,		// キューブボーナス(テキスト)
		RST_CUBE_CALC,	// キューブボーナス(結果)
		RST_BONUS,		// ボーナスの合計(テキスト)
		RST_BONUS_CALC,	// ボーナスの合計(計算)
		RST_ADD_SCORE,	// スコア加算
		RST_STAND,		// 待機
		RST_END,		// ランキング画面に移動
		RST_MAX
	};

	// ***** 関数 *****
	/* リザルト	*/void  Result(void);

	// ***** 変数 *****
	/* プレイヤー	*/static CPlayer *m_pPlayer;
	/* タイム		*/static CTime *m_pTime;
	/* スコア		*/static CScore *m_pScore;

	D3DXVECTOR3 m_rot;					// 向き
	float m_nMoveRot;					// 向きの加速度
	int m_nStartTime;					// 開始時間
	int m_nEndTime;						// 終了時間
	int m_nRstStgType;					// リザルト演出の種類
	int m_nTextCreate;					// 次のテキストの生成するまでの時間

	bool m_bEnd;						// 終了フラグ

	int m_nTimeTotal;					// タイムボーナスの合計値
	int m_nCubeTotal;					// キューブボーナスの合計値
	int m_nTotal;						// 全ての合計値
	int m_nAddTime;						// スコアの加算時間
	int m_nStandTime;					// 待機時間(リザルト演出終了後)
	CText *m_RstText[RST_ADD_SCORE];	// テキスト表示
	bool m_bAddScore;					// スコアの加算フラグ
	static bool m_bTime;				// 時間フラグ

	static int m_nSelectStage;			// 現在選択しているステージ 
};

#endif