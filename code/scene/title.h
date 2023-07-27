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

//****************************************
// クラス
//****************************************
class CTitle : public CScene
{
public:

	// ***** 関数 *****
	CTitle();
	~CTitle();

	// -- メイン ------------------------------------------
	/* 初期化		*/HRESULT Init(void);
	/* 終了			*/void Uninit(void);
	/* 更新			*/void Update(void);
	/* 描画			*/void Draw(void);
	/* 生成			*/static CTitle *Create(void);

private:

	// ***** 変数 *****
	CWords *m_Words[4]; // ピクパズ
	bool m_bMove[4];
	int m_nTextTime;
	int m_nStandTime;
};

#endif