//========================================
// 
// ランキング
// 
//========================================
// *** ranking.h ***
//========================================
#include "ranking.h"
#include "fade.h"
#include "../system/csv_file.h"
#include "../system/input.h"
#include "../system/words/text.h"
#include "../system/words/font.h"

// 定義
const char* CRanking::FILE_PATH = "data\\SAVEDATA\\RANKING_DATA.csv";

//========================================
// コンストラクタ
//========================================
CRanking::CRanking()
{
	for (int nRank = 0; nRank < RANK_NUM; nRank++)
	{
		m_Info[nRank].nScore = 100 + (100 * nRank);
		*m_Info[nRank].aName = NULL;
	}
}

//========================================
// デストラクタ
//========================================
CRanking::~CRanking()
{

}

//========================================
// 初期化
//========================================
HRESULT CRanking::Init(void)
{
	int nUpdateRank = -1;	// スコアを更新した順位

	// 読み込み
	Load();

	// ソート
	SortDesc(&nUpdateRank);

	// テキスト生成
	for (int nRank = 0; nRank < RANK_NUM; nRank++)
	{
		char aString[TXT_MAX];
		sprintf(aString, " %s %-5s %6d", GetRankText(nRank), *m_Info[nRank].aName,m_Info[nRank].nScore);

		m_Text[nRank] = CText::Create(CText::BOX_NORMAL,
			D3DXVECTOR3(640.0f, 200 + ( 30 * nRank), 0.0f),
			D3DXVECTOR2(1080.0f, 100.0f),
			aString,
			CFont::FONT_DOTGOTHIC,
			20.0f,
			1, 1, -1,false);
	}

	return S_OK;
}

//========================================
// 終了
//========================================
void CRanking::Uninit(void)
{
	// 書き出し処理
	Save();

	CObject::ReleaseAll(CObject::TYPE_TEXT2D);
	CObject::ReleaseAll(CObject::TYPE_FONT);
}

//========================================
// 更新
//========================================
void CRanking::Update(void)
{
	//++pUi->nCounterBlink %= (UI_RANKINGFRAME_00_BLINK_TIME * 2);	// 点滅カウンターを加算制御

	// -- 取得 -------------------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// ジョイパット

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_A))
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			CManager::GetFade()->SetFade(MODE_TITLE);
		}
	}
}

//========================================
// 描画
//========================================
void CRanking::Draw(void)
{

}

//========================================
// 生成
//========================================
CRanking *CRanking::Create(void)
{
	CRanking *pRanking = new CRanking;

	pRanking->Init();

	return pRanking;
}

//========================================
// 読み込み
//========================================
void CRanking::Load(void)
{
	CSVFILE *pFile = new CSVFILE;

	pFile->FileLood(FILE_PATH, true, true, ',');

	// 行数の取得
	int nRowMax = pFile->GetRowSize();

	for (int nRow = 0; nRow < nRowMax; nRow++)
	{

		// 列数の取得
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(*m_Info[nRow].aName, sData); break;	// 名前
			case 1:	pFile->ToValue(m_Info[nRow].nScore, sData);		break;	// スコア
			}
		}

		// 最大数に達したら返す
		if (nRow == nRowMax - 1)	// (列数 - 列の最大数 - ヘッダーの列数)
		{
			return;
		}
	}

	delete pFile;
	pFile = NULL;
}

//========================================
// 書き出し
//========================================
void CRanking::Save(void)
{
	CSVFILE *pFile = new CSVFILE;

	// ヘッダーの設定
	pFile->SetHeader("名前,スコア,", ',');

	// データの設定
	for (int nRow = 0; nRow < RANK_NUM; nRow++)
	{
		// インデックスの設定
		pFile->SetIndex(GetRankText(nRow), ',');

		for (int nLine = 0; nLine < 2; nLine++)
		{
			string sData;	// 文字列の格納する変数

			// 文字列に変換
			switch (nLine)
			{
			case 0:	sData = *m_Info[nRow].aName; break;	// 名前
			case 1:	sData = pFile->CastCell(m_Info[nRow].nScore); break;	// スコア
			}

			// データの追加
			pFile->SetCell(sData, nRow, nLine);
		}
	}

	// 書き出し
	pFile->FileSave(FILE_PATH, ',');
}

//========================================
// スコア設定
//========================================
int CRanking::SetScore(int nScore)
{
	int nUpdateRank = -1;	// スコアを更新した順位

	// スコアを降順にソートする
	SortDesc(&nUpdateRank);

	if (nScore > m_Info[RANK_NUM - 1].nScore)
	{// 最も小さい値より挿入する値が大きかった時
	 // 最も小さい値に挿入する値を代入する
		m_Info[RANK_NUM - 1].nScore = nScore;

		// スコアを更新した順位を代入する
		nUpdateRank = RANK_NUM - 1;
	}

	// スコアを降順にソートする
	SortDesc(&nUpdateRank);

	// スコアを更新した順位を返す
	return nUpdateRank;
}

//========================================
// ソート降順
//========================================
void CRanking::SortDesc(int *nUpdateRank)
{
	int	 nTemp;					// 一時的に値を格納
	char aNameTemp[TXT_MAX];	// 一時的に値を格納
	bool bUpdateRank = false;	// 順位更新フラグ

	for (int nCnt1 = 0; nCnt1 < RANK_NUM - 1; nCnt1++)
	{
		for (int nCnt2 = nCnt1 + 1; nCnt2 < RANK_NUM; nCnt2++)
		{
			if (m_Info[nCnt2].nScore > m_Info[nCnt1].nScore)
			{// 要素2が要素1の値を上回っていた時、
			 // 値を入れ替える
				nTemp = m_Info[nCnt1].nScore;
				m_Info[nCnt1].nScore = m_Info[nCnt2].nScore;
				m_Info[nCnt2].nScore = nTemp;

				// 名前を入れ替える
				sprintf(aNameTemp, "%s", *m_Info[nCnt1].aName);
				sprintf(*m_Info[nCnt1].aName, "%s", *m_Info[nCnt2].aName);
				sprintf(*m_Info[nCnt2].aName, "%s", aNameTemp);

				if (bUpdateRank == false)
				{// 順位更新フラグが偽の時、
				 // 順位更新フラグを真にする
					bUpdateRank = true;

					// スコアを更新した順位を代入する
					*nUpdateRank = nCnt1;
				}
			}
		}
	}
}