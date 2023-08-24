//========================================
// 
// チュートリアル
// 
//========================================
// *** tutorial.h ***
//========================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "../main.h"
#include "../manager.h"

//****************************************
// 前方宣言
//****************************************
class CText;
class CPlayer;
class CEnemy;

//****************************************
// クラス
//****************************************
class CTutorial : public CScene
{
	// ***** 定義 *****
	static const char* FILE_PATH;		// 読み込むファイルパス
	static const int MAX_TIME = 99;		// 制限時間
	static const int NUM_TEXT = 10;		// テキスト数

	static const char* CEILING_FILE;	// 天井のファイルパス
	static const char* SIDE_FILE;		// 側面のファイルパス
	static const char* FLOOR_FILE;		// 床のファイルパス
	static const char* BLOCK_FILE1;		// ブロックのファイルパス
	static const char* ENEMY_FILE1;		// エネミーのファイルパス
public:

	// ***** 列挙型 *****

	// 行動
	enum ACTION
	{
		ACTION_MOVE = 0,	// 移動
		ACTION_CAMERA,		// 視点移動
		ACTION_SHOT,		// 発射
		ACTION_SET,			// 配置(壁)
		ACTION_SET1,		// 配置(任意)
		ACTION_ENEMY,		// 敵
		ACTION_CLEAR,		// 出口
		ACTION_FREE,		// 自由
		ACTION_MAX
	};

	// ***** 関数 *****
	CTutorial();
	~CTutorial();

	// -- メイン ------------------------------------------
	/* 初期化			*/HRESULT Init(void);
	/* 終了				*/void Uninit(void);
	/* 更新				*/void Update(void);
	/* 描画				*/void Draw(void);
	/* 生成				*/static CTutorial *Create(void);
	/* 読み込み			*/void TextLoad(void);

	// -- 読み込み ----------
	/* 背景　天井	*/static void LoodCeiling(void);
	/* 背景　側面	*/static void LoodSide(void);
	/* 床			*/static void LoodFloor(void);
	/* ブロック		*/static void LoodBlock(void);
	/* エネミー		*/static void LoodEnemy(void);

	// -- 取得 ------------------------
	/* プレイヤー	*/static CPlayer *GetPlayer() { return m_pPlayer; }
	/* タイム		*/static CTime *GetTime() { return m_pTime; }
	/* スコア		*/static CScore *GetScore() { return m_pScore; };

private:

	// ***** 構造体 *****

	// テキスト情報
	struct TEXT_INFO
	{
		D3DXVECTOR3 pos;			// 位置
		D3DXVECTOR2 size;			// サイズ
		int nType;					// 種類
		int nStartTime;				// 開始時間
		int nStandTime;				// 待機時間
		int nDisapTime;				// 消える時間
		char *ActionTex[TXT_MAX];	// 行動テキスト
		int nTextSize;				// テキストサイズ
		int nEndTime;				// 終了時間
		bool bCreate;				// 生成フラグ
		bool bEnd;					// 終了フラグ
		bool bAction;				// テキストに書かれた行動を行ったか

		bool bTextBok;				// テキストボックスの表示フラグ

	};

	// ***** 関数 *****
	/* テキスト情報初期化	*/void TextInit(int nIdx);
	/* テキスト生成			*/void TexCreate(int nIdx);
	/* チュートリアル		*/void TutorialTex(void);

	// ***** 静的変数 *****
	/* テキスト情報	*/static TEXT_INFO	*m_TextInfo;
	/* プレイヤー	*/static CPlayer *m_pPlayer;
	/* タイム		*/static CTime *m_pTime;
	/* スコア		*/static CScore *m_pScore;

	// ***** 変数 *****
	CText *m_Text;				// テキスト
	ACTION Action;				// 行動種類
	int m_nTextMax;				// テキスト情報の最大数
	int m_nNumText;				// 生成したテキスト数
	int m_nTextType;			// 現在の表示テキスト種類
	int m_nTextCreate;			// 次のテキストの生成するまでの時間

	int m_nStartTime;			// 開始時間
	int m_nEndTime;				// 終了時間
	bool m_bEnd;				// 終了フラグ

	int m_nTypeMax[ACTION_MAX];	// 種類ごとの最終位置

};

#endif