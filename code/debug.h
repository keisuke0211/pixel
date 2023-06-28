//========================================
// 
// デバック処理
// 
//========================================
// *** debug.h ***
//========================================
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "main.h"

class CDebug
{
public:

	// ***** 関数 *****
	/* 初期化	*/static void Init(void);
	/* 終了		*/static void Uninit(void);
	/* 更新		*/static void Update(void);
	/* 描画		*/static void Draw(void);
	/* デバック表示 */static void DebugPrint(const char *text, ...);
	/*  */static void ReleasePrint(const char *text, ...);
};

#endif