//========================================
// 
// フォント
// 
//========================================
// *** font.h ***
//========================================
#ifndef _FONT_H_
#define _FONT_H_

#include "../../main.h"

//****************************************
// クラス
//****************************************
class CFont
{

public:
	// ***** 列挙型 *****

	// フォント
	enum FONT // DotGothic
	{
		FONT_DOTGOTHIC = 0,
		FONT_MEIRIO,
		FONT_MAX,
	};

	// ***** 関数 *****
	CFont();
	virtual~CFont();

	// -- メイン ------------------------------------------
	/* フォント作成		*/void FontCreate(FONT nFont);
	/* テクスチャ作成	*/void TextureCreate(string nWords, FONT nFont);
	/* 全て破棄			*/void ReleaseAll(void);
	/* 指定の破棄		*/void Release(FONT nFont);

	// -- 取得 ------------------------------------------
	/* テクスチャ情報の取得 */LPDIRECT3DTEXTURE9 GetFont(string words, FONT nFont);
private:

	// ***** 静的変数 *****
	static int m_nMaxFont;				// フォント数
	static const char* s_FileName[];	// ファイルパス
	static const char* s_FontName[];	// ファイルパス

										// ***** 変数 *****
	HFONT  m_hFont[FONT_MAX];
	LOGFONT m_logFont[FONT_MAX];
	LPDIRECT3DTEXTURE9 m_texFont[FONT_MAX];	// テクスチャの情報
};

#endif