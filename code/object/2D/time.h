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
	HRESULT Init(void);				// 初期化
	void Uninit(void);				// 終了
	void Update(void);				// 更新
	void Draw(void);				// 描画
	void SetTime(int nTime = 0);	// 設定

	// 生成
	static CTime *Create(void);

private:
	// ***** 変数 *****
	int m_nTime;		// タイム
	int m_nCounter;		// カウンター
};
#endif 