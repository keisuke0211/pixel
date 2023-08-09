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
// 前方宣言
//****************************************
class CFont;

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
	/* 初期化	*/HRESULT Init(void);
	/* 終了		*/void Uninit(void);
	/* 更新		*/void Update(void);
	/* 描画		*/void Draw(void);

	//--------------------------------------------------
	// テキスト生成
	// 引数1  : Box type            / メッセージボックスの画像
	// 引数2  : D3DXVECTOR3 pos     / メッセージボックスの位置
	// 引数3  : D3DXVECTOR2 size    / メッセージボックスのサイズ
	// 引数4  : CFont::FONT Type　　/ フォント種類
	// 引数5  : const char *Text　　/ テキスト
	// 引数6  : float TextSize　　　/ サイズ (初期値 20)
	// 引数7  : int AppearTime　　　/ １文字目が表示されるまでの時間 (初期値 1)
	// 引数8  : int StandTime　　　 / 待機時間 (初期値 10)
	// 引数9  : int EraseTime　　　 / 消えるまでの時間 (初期値 1) ※ 0 は消えない
	// 引数10  : bool bTextBok　　　 / メッセージボックスの表示・非表示 (初期値 true)
	//--------------------------------------------------
	static CText *CText::Create(Box type, D3DXVECTOR3 pos, D3DXVECTOR2 size, const char *Text, CFont::FONT FontType, float TextSize = 20, int AppearTime = 1, int StandTime = 10, int EraseTime = 1, bool bTextBok = true);

	/* 削除 */void Disap(bool bDisap);

	// -- 設定 ------------------------------------------
	/* ポーズ中の生成	*/void SetTetPause(bool bPause);
	/* ボックスの色		*/void SetBoxColor(D3DXCOLOR col);
	/* テキストの色		*/void SetTextColor(D3DXCOLOR col);

private:

	// ***** 構造体 *****

	// テキスト情報
	struct Info
	{
		D3DXCOLOR col;
		float fTextSize;		// 文字のサイズ
		int nTextLength;		// 文字の長さ
		int nAppearTime;		// 1つの文字が加算されるまでの時間
		int nAddCount;			// 文字が加算されるまでのカウント
		int nAddLetter;			// 何文字目入れるか指定
		int nLetterPopCount;	// 文字を出した最大数
		int nLetterPopCountX;	// 横に文字を出した数
		int nNiCount;			// 改行の数

		int nStandTime;			// 待機時間
		bool bStand;			// 待機フラグ

		int nDisapTime;			// 消える時間
		int nDisapTimeMax;		// 消える最大時間
		bool bRelease;			// 消すフラグ

		bool bTextBok;			// テキストボックスの表示フラグ
		bool bPause;			// ポーズ中でも動くか（false：動かない）
		string sText;			// 表示するテキスト
		string sALLText;		// テキストの全体
		CWords** words;			// 文字
		CFont::FONT FontType;	// フォント種類
	};

	// ***** 関数 *****
	/* 文字生成	*/void LetterForm(void);
	/* 待機		*/void StandTime(void);
	/* 削除		*/void DisapTime(void);
	/* 文字判定	*/bool CheckLeadByte(int nLetter);

	// -- 設定 ------------------------------------------
	/* テキスト サイズ	*/void SetTextSize(float TextSize);
	/* 待機時間			*/void SetStandTime(int StandTime);
	/* 文字の消す時間	*/void EraseTime(int time);
	/* 文字の出現時間	*/void TextLetter(const char *Text, int DispText);

	// ***** 変数 *****
	Info m_Info;

};

#endif