//========================================
//
// 時間
//
//========================================
// *** time.h ***
//========================================
#ifndef _TIME_H_
#define _TIME_H_

#include "../object.h"
#include "text2D.h"

//****************************************
// クラス
//****************************************
class CTime : public CText2D
{
public:

	CTime(int nPriority = PRIO_UI);
	~CTime();

	// *****  関数 *****

	/* メイン */
	/* 初期化		*/HRESULT Init(void);
	/* 終了			*/void Uninit(void);
	/* 更新			*/void Update(void);
	/* 描画			*/void Draw(void);
	/* タイム設定	*/void SetTime(int nTime = 0);
	/* タイム所得	*/int GetTime(void) { return m_nTime; }

	// 生成
	static CTime *Create(void);

private:
	// ***** 変数 *****
	int m_nTime;		// タイム
	int m_nCounter;		// カウンター
};
#endif 