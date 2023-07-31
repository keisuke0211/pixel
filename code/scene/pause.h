//========================================
// 
// ポーズ
// 
//========================================
// *** pause.h ***
//========================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "../main.h"
#include "../manager.h"

//****************************************
// 前方宣言
//****************************************
class CWords;

//****************************************
// クラス
//****************************************
class CPause : public CScene
{
public:

	// ***** 関数 *****
	CPause();
	~CPause();

	// -- メイン ------------------------------------------
	/* 初期化		*/HRESULT Init(void);
	/* 終了			*/void Uninit(void);
	/* 更新			*/void Update(void);
	/* 描画			*/void Draw(void);
	/* 生成			*/static CPause *Create(void);

	// -- 設定 --------------------------------------------
	/* ポーズ */static void SetPause(bool bPause) { m_bPause = bPause; }

	// -- 取得 --------------------------------------------
	/* ポーズ	*/static bool IsPause(void) { return m_bPause; }

private:

	// ***** 変数 *****
	static bool m_bPause;
};

#endif