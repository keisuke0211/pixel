//========================================
//
// スコア
//
//========================================
// *** score.h ***
//========================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "../object.h"
#include "text2D.h"

//****************************************
// マクロ定義
//****************************************
#define	MAX_SCORE	(8)

//****************************************
// 前方宣言
//****************************************
class CText2D;

//****************************************
// クラス
//****************************************
class CScore : public CText2D
{
public:

	CScore(int nPriority = TYPE_SCORE);
	~CScore();

	// *****  関数 *****

	/* メイン */
	HRESULT Init(void);		// 初期化
	void Uninit(void);		// 終了
	void Update(void);		// 更新
	void Draw(void);		// 描画
	static void SetScore(int nScore = 0);	// 設定

	// 生成
	static CScore *Create(void);

private:
	// ***** 変数 *****
	static int m_nScore;
};
#endif 