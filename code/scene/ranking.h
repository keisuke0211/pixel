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
class CWords;

//****************************************
// クラス
//****************************************
class CRanking : public CScene
{
public:

	// ***** 関数 *****
	CRanking();
	~CRanking();

	// -- メイン ------------------------------------------
	/* 初期化		*/HRESULT Init(void);
	/* 終了			*/void Uninit(void);
	/* 更新			*/void Update(void);
	/* 描画			*/void Draw(void);
	/* 生成			*/static CRanking *Create(void);

private:

	// ***** 変数 *****
};

#endif