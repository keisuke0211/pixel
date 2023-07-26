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
	// ***** 定義 *****
	static const char* FILE_PATH;		// 読み込むファイルパス

public:
	// ***** 列挙型 *****

	// フォント
	enum FONT // DotGothic
	{
		FONT_DOTGOTHIC = 0,
		FONT_MEIRIO,
		FONT_MAX,
	};

	// ***** 構造体 *****

	// フォントデータ

	//struct Info
	//{
	//	char FileName[TXT_MAX];	// ファイルパス
	//	char FontName[TXT_MAX];	// フォント名
	//	HFONT  hFont;
	//	LOGFONT logFont;
	//	LPDIRECT3DTEXTURE9 texFont;	// テクスチャの情報
	//};

	// ***** 関数 *****
	CFont();
	virtual~CFont();

	// -- メイン ------------------------------------------
	/* フォント作成		*/void FontCreate(FONT nFont);
	/* テクスチャ作成	*/void TextureCreate(string nWords, FONT nFont);
	/* 全て破棄			*/void ReleaseAll(void);
	/* 指定の破棄		*/void Release(FONT nFont);
	/* 読み込み			*/void Load(void);

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

	///* フォント情報	*/Info m_Font[FONT_MAX];

};

#endif