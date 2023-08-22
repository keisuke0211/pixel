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
int CRanking::m_nGameScore = 2000;
bool CRanking::m_bSetScore = true;

//========================================
// コンストラクタ
//========================================
CRanking::CRanking()
{
	for (int nRank = 0; nRank < RANK_NUM; nRank++)
	{
		m_Ranking[nRank].nScore = 100 + (100 * nRank);
		*m_Ranking[nRank].aName = NULL;
	}

	m_Info.nCounterState = 0;
	m_Info.bNameEntry = false;
	m_Info.nCntName = 0;
	m_Info.nUpdateRank = -1;
	m_Info.nCntBlink = 0;
	m_Info.bNameInput = true;
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
		sprintf(aString, " %s %-5s %6d", GetRankText(nRank), m_Ranking[nRank].aName,m_Ranking[nRank].nScore);

		m_Text[nRank] = CText::Create(CText::BOX_NORMAL,
			D3DXVECTOR3(640.0f, 200 + ( 30 * nRank), 0.0f),
			D3DXVECTOR2(1080.0f, 100.0f),
			aString,
			CFont::FONT_DOTGOTHIC,
			20.0f,
			1, 1, -1,false);
	}


	if (m_bSetScore)
	{
		SetNameEntry(SetScore(m_nGameScore));
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

	// 状態
	//State();

	// 名前入力
	NameEntry();

	if ((pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_A)) && m_Info.bNameEntry == false)
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
			case 0:
				char *pNama;
				pFile->ToValue(pNama, sData);

				strcat(m_Ranking[nRow].aName,pNama);
				break;	// 名前
			case 1:	pFile->ToValue(m_Ranking[nRow].nScore, sData);		break;	// スコア
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
			case 0:	sData = *m_Ranking[nRow].aName; break;	// 名前
			case 1:	sData = pFile->CastCell(m_Ranking[nRow].nScore); break;	// スコア
			}

			// データの追加
			pFile->SetCell(sData, nRow, nLine);
		}
	}

	// 書き出し
	pFile->FileSave(FILE_PATH, ',');
}

//========================================
// 状態処理
//========================================
void CRanking::State(void)
{
	for (int nCntRanking = 0; nCntRanking < RANK_NUM; nCntRanking++)
	{
		if (m_Info.nUpdateRank == nCntRanking)
		{
			m_Text[nCntRanking]->SetTextColor(BLINK_COLOR);
		}
	}
}

//========================================
// スコア設定
//========================================
int CRanking::SetScore(int nScore)
{
	int nUpdateRank = -1;	// スコアを更新した順位

	// スコアを降順にソートする
	SortDesc(&nUpdateRank);

	if (nScore > m_Ranking[RANK_NUM - 1].nScore)
	{// 最も小さい値より挿入する値が大きかった時
	 // 最も小さい値に挿入する値を代入する
		m_Ranking[RANK_NUM - 1].nScore = nScore;

		// スコアを更新した順位を代入する
		nUpdateRank = RANK_NUM - 1;
	}

	// スコアを降順にソートする
	SortDesc(&nUpdateRank);

	// スコアを更新した順位を返す
	return nUpdateRank;
}

//========================================
// スコア設定
//========================================
void CRanking::SetScore11(int nScore)
{
	m_nGameScore = nScore;
	m_bSetScore = true;
}

//========================================
// 名前入力設定
//========================================
void CRanking::SetNameEntry(int nUpdateRank)
{
	m_Info.nUpdateRank = nUpdateRank;

	if (m_Info.nUpdateRank != -1)
	{// 更新順位が-1(更新無し)でない時、
		m_Info.bNameEntry = true;
		m_Info.nCntName = 0;
		m_Info.nCntChar = NAME_START_CHAR;
		m_Info.nCntBlink = 0;

		// 更新した順位の名前を初期化
		strinit(m_Ranking[nUpdateRank].aName, TXT_MAX);

		char aString[TXT_MAX];
		sprintf(aString, " %s %-5s %6d", GetRankText(m_Info.nUpdateRank), m_Ranking[m_Info.nUpdateRank].aName, m_Ranking[m_Info.nUpdateRank].nScore);

		m_Text[m_Info.nUpdateRank]->Uninit();

		m_Text[m_Info.nUpdateRank] = CText::Create(CText::BOX_NORMAL,
			D3DXVECTOR3(640.0f, 200 + (30 * m_Info.nUpdateRank), 0.0f),
			D3DXVECTOR2(1080.0f, 100.0f),
			aString,
			CFont::FONT_DOTGOTHIC,
			20.0f,
			1, 1, -1, false);
	}
	else
	{// 更新処理が-1(更新無し)の時、
		m_Info.bNameEntry = false;
	}
}

//========================================
// 名前入力
//========================================
void CRanking::NameEntry(void)
{
	if (!m_Info.bNameEntry)
	{
		return;
	}

	// -- 取得 -------------------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// ジョイパット

	if (!m_Info.bNameInput)
	{
		// -- 文字切替 ---------------------------------------------
		if (pInputKeyboard->GetRepeat(DIK_A) || pInputKeyboard->GetRepeat(DIK_LEFT) ||
			pInputJoypad->GetRepeat(CJoypad::JOYKEY_LEFT) || pInputJoypad->GetStick().aAngleRepeat[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_LEFT])
		{
			m_Info.nCntChar--;
			m_Info.bNameInput = true;
		}
		else if (
			pInputKeyboard->GetRepeat(DIK_D) || pInputKeyboard->GetRepeat(DIK_RIGHT) ||
			pInputJoypad->GetRepeat(CJoypad::JOYKEY_RIGHT) || pInputJoypad->GetStick().aAngleRepeat[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_RIGHT])
		{
			m_Info.nCntChar++;
			m_Info.bNameInput = true;
		}

		IntLoopControl(&m_Info.nCntChar, NAME_MAX_CHAR, NAME_MIN_CHAR);

		// -- 決定・削除 ---------------------------------------------
		if (pInputKeyboard->GetTrigger(DIK_BACKSPACE) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_B))
		{// 削除
			if (m_Info.nCntName > 0)
			{
				m_Info.nCntName--;

				// 現在のカウント以降の文字を空白にする
				m_Ranking[m_Info.nUpdateRank].aName[m_Info.nCntName + 1] = '\0';

				// 文字カウントを設定
				m_Info.nCntChar = m_Ranking[m_Info.nUpdateRank].aName[m_Info.nCntName];
			}
			m_Info.bNameInput = true;

		}
		else if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_A))
		{// 決定
			if (++m_Info.nCntName >= NAME_NUM)
			{// 名前入力のカウントを加算した結果、ランキング名の文字数に達した時、
				m_Info.bNameEntry = false;
				return;
			}
			m_Info.nCntChar = NAME_START_CHAR;
			m_Info.bNameInput = true;
		}
	}
	
	if (m_Info.bNameInput)
	{
		int nRank = m_Info.nUpdateRank;
		char aWords = m_Info.nCntChar;

		// 現在のカウントの文字を反映する
		m_Ranking[nRank].aName[m_Info.nCntName] = aWords;

		if (m_Text[nRank]->SetWords(&aWords, NAME_START_DEX + m_Info.nCntName))
		{
			m_Info.bNameInput = false;
		}
	}
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
			if (m_Ranking[nCnt2].nScore > m_Ranking[nCnt1].nScore)
			{// 要素2が要素1の値を上回っていた時、
			 // 値を入れ替える
				nTemp = m_Ranking[nCnt1].nScore;
				m_Ranking[nCnt1].nScore = m_Ranking[nCnt2].nScore;
				m_Ranking[nCnt2].nScore = nTemp;

				// 名前を入れ替える
				sprintf(aNameTemp, "%s", m_Ranking[nCnt1].aName);
				sprintf(m_Ranking[nCnt1].aName, "%s", m_Ranking[nCnt2].aName);
				sprintf(m_Ranking[nCnt2].aName, "%s", aNameTemp);

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

//========================================
// 空白埋め
//========================================
void CRanking::strinit(char *pData, int nNum)
{
	for (int nCnt = 0; nCnt < nNum; nCnt++)
	{
		pData[nCnt] = '\0';
	}
}