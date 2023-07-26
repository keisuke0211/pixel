//========================================
// 
// テキスト表示
// 
//========================================
// *** text.h ***
//========================================
#ifndef _TEXT_H_
#define _TEXT_H_

#include "../../object/object2D.h"
#include "words.h"

//****************************************
// クラス
//****************************************
class CText : public CObject2D
{
public:

	// ***** 列挙型 *****

	// テキストボックスの種類
	enum Box
	{
		BOX_NORMAL = 0,	// シンプル
		BOX_MAX
	};

	// ***** 関数 *****
	CText(int nPriority = PRIO_TEXT);
	~CText();

	// -- メイン ------------------------------------------
	/* 初期化	*/HRESULT Init(void)override;
	/* 終了		*/void Uninit(void)override;
	/* 更新		*/void Update(void)override;
	/* 描画		*/void Draw(void)override;

	//--------------------------------------------------
	// テキスト生成
	// 引数1  : Box type			/ テキストボックスの画像
	// 引数2  : int EraseTime		/ 消えるまでの時間
	// 引数3  : int DispText		/ １文字目が表示されるまでの時間
	// 引数4  : const char *Text	/ テキスト
	//--------------------------------------------------
	static CText *CText::Create(Box type, int EraseTime, int DispText, const char *Text);

private:

	// ***** 構造体 *****

	// テキスト情報
	struct Info
	{
		D3DXCOLOR col;
		int nDesapTimar;		// 消える時間
		int nDesapTimarMax;		// 消える最大時間
		int nTextSize;			// 文字のサイズ
		int nAddTime;			// 1つの文字が加算されるまでの時間
		int nAddCount;			// 文字が加算されるまでのカウント
		int nAddLetter;			// 何文字目入れるか指定
		int nLetterPopCount;	// 文字を出した最大数
		int nLetterPopCountX;	// 横に文字を出した数
		int nNiCount;			// 改行の数
		bool bRelease;			// 消すフラグ
		string sText;			// 表示するテキスト
		string sALLText;		// テキストの全体
		CWords** words;			// 
	};

	// ***** 関数 *****

	// -- 設定 ------------------------------------------
	/* 文字の消す時間	*/void EraseTime(int time);
	/* 文字の出現時間	*/void TextLetter(const char *Text, int DispText);
	bool CheckLeadByte(int nLetter);
	// ***** 変数 *****
	Info m_Info;

};

#endif