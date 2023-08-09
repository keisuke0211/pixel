//========================================
// 
// ランキング
// 
//========================================
// *** ranking.h ***
//========================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "../main.h"
#include "../manager.h"

//****************************************
// 前方宣言
//****************************************
class CText;

//****************************************
// クラス
//****************************************
class CRanking : public CScene
{
	static const char* FILE_PATH;		// 読み込むファイルパス
	static const int RANK_NUM = 8;		// 順位数

public:

	// ***** 関数 *****
	CRanking();
	~CRanking();

	// -- メイン ------------------------------------------
	/* 初期化		*/HRESULT Init(void);
	/* 終了			*/void Uninit(void);
	/* 更新			*/void Update(void);
	/* 描画			*/void Draw(void);
	/* 読み込み		*/void Load(void);
	/* 書き出し		*/void Save(void);
	/* 生成			*/static CRanking *Create(void);

	// -- 設定 ------------------------------------------
	/* スコア	*/void SetScore(int nScore);

	// -- 取得 ------------------------------------------
	/* 順位の表示形式の取得	*/char *GetRankText(int nRank) { return m_aRank[nRank].aRankText; }

private:

	// ***** 構造体 *****

	// ランキング情報
	struct Info
	{
		int nScore;		// スコア
	};

	struct Rank
	{
		char aRankText[TXT_MAX];	// テキスト
	};

	// ***** 関数 *****
	/* ソート降順 */void SortDesc(void);

	// ***** 変数 *****
	Info m_Info[RANK_NUM];		// ランキング情報
	CText *m_Text[RANK_NUM];	// テキスト

	// 順位の表示形式
	Rank m_aRank[RANK_NUM] =
	{
		"1ST",
		"2ND",
		"3RD",
		"4TH",
		"5TH",
		"6TH",
		"7TH",
		"8TH",
	};
};

#endif