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
// 前方宣言
//****************************************
class CWords;
class CText;
class CStage;

//****************************************
// クラス
//****************************************
class CTitle : public CScene
{
	// ***** 定義 *****
	static const char* TEXT_FILE_PATH;	// 読み込むファイルパス
	static const int STAND_MAX = 20;	// テキストの待機時間
	static const int TEXT_TIME = 150;	// テキストの表示時間
	static const int WORDS_MAX = 4;		// 文字の最大数
	static const int STAGE_MAX = 6;		// ステージ画像の最大数

public:

	// ***** 列挙型 *****

	// タイトルモード
	enum TITLE
	{
		TITLE_OUTSET = 0,	// タイトル
		TITLE_MENU,			// メニュー
		TITLE_STAGE,		// ステージ選択
		TITLE_NEXT,			// 次の画面に移動 
		TITLE_MAX
	};

	// メニュー
	enum MENU
	{
		MENU_GAME = 0,	// ゲーム
		MENU_TUTORIAL,	// チュートリアル
		MENU_RANKING,	// ランキング
		MENU_END,		// 終了
		MENU_MAX
	};

	// ***** 関数 *****
	CTitle();
	~CTitle();

	// -- メイン ------------------------------------------
	/* 初期化		*/HRESULT Init(void);
	/* 終了			*/void Uninit(void);
	/* 更新			*/void Update(void);
	/* 描画			*/void Draw(void);
	/* 生成			*/static CTitle *Create(void);
	/* タイトル		*/void TitleAnime(void);
	/* メニュー生成 */void MenuCreate(void);
	/* メニュー		*/void Menu(void);
	/* ステージ生成	*/void StageCreate(void);
	/* ステージ選択	*/void SelectStage(void);
	/* テキスト削除 */void TextClear(int nWords,int nText, TITLE aTitle);

	// -- 設定 ------------------------------------------
	/* 開始		*/static void SetStart(bool bStart) { m_bStart = bStart; }
	/* 出口		*/static void SetExit(bool bExit) { m_bExit = bExit; }
	/* クリア	*/static void SetClear(bool bClear) { m_bClear = bClear; }

	// -- 取得 ------------------------------------------
	/* 開始			*/static bool IsStart() { return m_bStart; }
	/* 出口			*/static bool IsExit() { return m_bExit; }
	/* クリア		*/static bool IsClear() { return m_bClear; }

private:

	// ***** 構造体 *****

	// テキスト情報
	struct Text
	{
		char aStageText[TXT_MAX];
		char aStageWords[2][TXT_MAX];
	};

	// ***** 関数 *****
	/* テキスト読み込み	*/void TextLoad(void);

	// ***** 静的変数 *****
	static bool m_bStart;	// 開始フラグ
	static bool m_bExit;	// 出口　（出口を開くかのフラク）
	static bool m_bClear;	// クリアフラグ

	// ***** 変数 *****
	TITLE Title;				// 現在のモード
	CWords *m_Words[4];			// タイトル
	bool m_bMove[4];			// タイトル移動フラグ
	CText *m_Menu[MENU_MAX];	// メニューテキスト
	CText *m_StageText[3];		// ステージテキスト
	bool m_bStageText;			// ステージテキストの生成フラグ
	CStage *m_Stage[STAGE_MAX];	// ステージ
	int m_nTextTime;			// テキストの表示時間
	int m_nStandTime;			// 待機時間
	int m_nSelectMenu;			// 現在選択しているメニュー
	int m_nSelectStage;			// 現在選択しているステージ
	Text m_aText[3];			// テキスト情報
};

#endif