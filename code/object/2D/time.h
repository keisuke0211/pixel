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
// マクロ定義
//****************************************
#define	MAX_TIME	(2)

//****************************************
// 前方宣言
//****************************************
class CText2D;

//****************************************
// クラス
//****************************************
class CTime : public CText2D
{
public:

	CTime(int nPriority = PRIO_TEXT);
	~CTime();

	// *****  関数 *****

	/* メイン */
	HRESULT Init(void);		// 初期化
	void Uninit(void);		// 終了
	void Update(void);		// 更新
	void Draw(void);		// 描画
	static void SetTime(int nTime = 0);	// 設定

	// 生成
	static CTime *Create(void);

private:
	// ***** 変数 *****
	static int m_nTime;
};
#endif 