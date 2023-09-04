//========================================
// 
// テクスチャ管理
// 
//========================================
// *** texture.h ***
//========================================
#ifndef _TEXTURE_H_	//このマクロ定義がされてなかったら
#define _TEXTURE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#include "../main.h"

//==================================================
// 定義
//==================================================
class CTexture
{
public:

	// ***** 定義 *****
	static const int MAX_TEXTURE = 64;	// テクスチャの最大数
	static const char* FILE_PATH;		// 読み込むファイルパス

	// ***** 列挙型 *****

	// 画像種類
	enum Tex
	{
		TEX_SKY00 = 0,		// 朝空00
		TEX_SKY01,			// 朝空01
		TEX_SKY02,			// 朝空02
		TEX_NIGHT_SKY00,	// 夜空00
		TEX_NIGHT_SKY01,	// 夜空01
		TEX_NIGHT_SKY02,	// 夜空02
		TEX_NIGHT_SKY03,	// 夜空03
		TEX_SEA01,			// 海01
		TEX_SEA02,			// 海02
		TEX_TITLE_BG,		// タイトル画面
		TEX_STAGE_EASY,		// ステージ・初級
		TEX_STAGE_NORMAL,	// ステージ・中級
		TEX_STAGE_DIFFICULT,// ステージ・上級
		TEX_TEXBOX,			// テキストボックス
		TEX_TEXBOX1,		// テキストボックス
		TEX_MAX
	};

	// ***** 関数 *****
	CTexture();		// デフォルトコンストラクタ
	~CTexture();	// デストラクタ

	HRESULT Load(void);			// 読み込み
	void Unload(void);			// 破棄

	/* 設定 */
	int Regist(const char* pFilename);	// テクスチャ番号

	/* 取得 */
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);	// テクスチャポインタ

private:
	// ***** 変数 *****
	LPDIRECT3DTEXTURE9 m_apTexture[MAX_TEXTURE];	// テクスチャポインタ
	static int m_NumAll;							// テクスチャ総数

	static char m_FileName[MAX_TEXTURE][TXT_MAX];	// ファイルパス
};

#endif // !_TEXTURE_H_
