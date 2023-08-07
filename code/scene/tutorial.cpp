//========================================
// 
// チュートリアル
// 
//========================================
// *** tutorial.h ***
//========================================
#include "tutorial.h"
#include "title.h"
#include "../manager.h"
#include "../system/csv_file.h"
#include "../object\UI\score.h"
#include "../object\UI\time.h"
#include "../object\model\block.h"
#include "../object/model/bullet.h"
#include "../object/model/bullet_cube.h"
#include "../object\model\player.h"
#include "../object\model\enemy.h"
#include "../object\BG\bg_side.h"
#include "../object\BG\bg_ceiling.h"
#include "../object\UI\text2D.h"
#include "../system/input.h"
#include "../system/words/text.h"
#include "../system/words/font.h"
#include "../system/camera.h"
#include "../scene/pause.h"
#include "fade.h"

// 静的変数
CTutorial::TEXT_INFO *CTutorial::m_TextInfo = NULL;	// テキスト情報

// サウンドのデータファイルの相対パス
const char* CTutorial::FILE_PATH = "data\\GAMEDATA\\TEXT\\TUTORIAL_DATA.csv";

CPlayer *CTutorial::m_pPlayer = NULL;
CTime *CTutorial::m_pTime = NULL;
CScore *CTutorial::m_pScore = NULL;

//========================================
// コンストラクタ
//========================================
CTutorial::CTutorial()
{
	m_Text = NULL;
	m_nStartTime = 0;

	m_nTextMax = 0;
	m_nNumText = 0;
	m_nTextType = 0;

	Action = ACTION_MOVE;
	m_nEndTime = 0;
	m_bEnd = false;

}

//========================================
// デストラクタ
//========================================
CTutorial::~CTutorial()
{

}

//========================================
// 初期化
//========================================
HRESULT CTutorial::Init(void)
{
	CTitle::SetStart(false);
	CTitle::SetExit(false);
	CTitle::SetClear(false);

	// 背景(側面)の生成
	CBgSide *pBgsky = CBgSide::Create();

	// 背景(天井)の生成
	CBgCeiling *pBgCeiling = CBgCeiling::Create();

	// ブロックの生成
	LoodBlock();

	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetMotion("data\\GAMEDATA\\MODEL\\Player\\PLAYER_DATA.txt");

	// 敵の生成
	LoodEnemy();

	{
		// タイム生成
		m_pTime = CTime::Create();

		// サイズ設定
		m_pTime->SetSize(20.0f, 20.0f);

		// 位置設定
		m_pTime->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 260.0f, 32.0f, 0.0f));

		// タイム設定
		m_pTime->SetTime(MAX_TIME);
	}

	{
		// スコア生成
		m_pScore = CScore::Create();

		// サイズ設定
		m_pScore->SetSize(20.0f, 20.0f);

		// 位置設定
		m_pScore->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 260.0f, 52.0f, 0.0f));

		// スコア設定
		CScore::SetScore();
	}

	// 読み込み
	TextLoad();

	// テキスト生成
	TexCreate(m_nNumText);

	return S_OK;
}

//========================================
// 終了
//========================================
void CTutorial::Uninit(void)
{
	CObject::ReleaseAll(CObject::TYPE_BG);
	CObject::ReleaseAll(CObject::TYPE_BLOCK);
	CObject::ReleaseAll(CObject::TYPE_CUBE);
	CObject::ReleaseAll(CObject::TYPE_PLAYER);
	CObject::ReleaseAll(CObject::TYPE_ENEMY);
	CObject::ReleaseAll(CObject::TYPE_EFFECT);
	CObject::ReleaseAll(CObject::TYPE_PARTICLE);
	CObject::ReleaseAll(CObject::TYPE_TIME);
	CObject::ReleaseAll(CObject::TYPE_SCORE);
	CObject::ReleaseAll(CObject::TYPE_TEXT2D);
	CObject::ReleaseAll(CObject::TYPE_FONT);

	// メモリ開放
	delete m_TextInfo;
	m_TextInfo = NULL;
}

//========================================
// 更新
//========================================
void CTutorial::Update(void)
{
	// -- 取得 -------------------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// ジョイパット

	// ポーズ
	if (pInputKeyboard->GetTrigger(DIK_P) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_START))
	{
		CPause::SetPause(true);
	}

	// 各テキストの処理
	TutorialTex();

	// 開始フラグ
	{
		bool bStart = CTitle::IsStart();
		if (!bStart && --m_nStartTime <= 0)
		{
			CTitle::SetStart(true);
		}
	}

	// エネミーの全滅
	{
		bool bExit = CTitle::IsExit();
		if (!bExit && CEnemy::GetEnemyAll() <= 0)
		{
			CTitle::SetExit(true);
		}
	}

	if (CFade::GetFade() == CFade::FADE_NONE)
	{
		// CLEAR
		{
			bool bClear = CTitle::IsClear();

			if (bClear)
			{
				if (!m_bEnd)
				{
					CText::Create(CText::BOX_NORMAL,
						D3DXVECTOR3(640.0f, 300.0f, 0.0f),
						D3DXVECTOR2(440.0f, 100.0f),
						"Game Clear",
						CFont::FONT_DOTGOTHIC,
						20.0f,
						15, 10, 30, false);

					m_nEndTime = (15 * 10) + 10 + 25;
					m_bEnd = true;
				}
				else
				{
					if (--m_nEndTime <= 0)
					{
						CManager::GetFade()->SetFade(MODE_TITLE);
					}
				}
			}
		}

		// 時間切れ
		if (m_pTime->GetTime() <= 0)
		{
			CManager::GetFade()->SetFade(MODE_TITLE);
		}
	}
}

//========================================
// 描画
//========================================
void CTutorial::Draw(void)
{

}

//========================================
// 生成
//========================================
CTutorial *CTutorial::Create(void)
{
	CTutorial *pTutorial = new CTutorial;

	pTutorial->Init();

	return pTutorial;
}

//========================================
// 読み込み
//========================================
void CTutorial::TextLoad(void)
{
	CSVFILE *pFile = new CSVFILE;

	pFile->FileLood(FILE_PATH, true, true, ',');

	// 行数の取得
	int nRowMax = pFile->GetRowSize();

	// メモリ確保
	m_TextInfo = new CTutorial::TEXT_INFO[nRowMax];
	m_nTextMax = nRowMax;

	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		// 初期化
		TextInit(nRow);

		// 列数の取得
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(m_TextInfo[nRow].nType, sData); break;		// 種類
			case 1:	pFile->ToValue(m_TextInfo[nRow].pos.x, sData); break;		// 位置 X
			case 2:	pFile->ToValue(m_TextInfo[nRow].pos.y, sData); break;		// 　　 Y
			case 3:	pFile->ToValue(m_TextInfo[nRow].size.x, sData); break;		// サイズ X
			case 4:	pFile->ToValue(m_TextInfo[nRow].size.y, sData); break;		// 　　　 Y
			case 5:	pFile->ToValue(m_TextInfo[nRow].nStartTime, sData); break;	// 表示時間
			case 6:	pFile->ToValue(m_TextInfo[nRow].nStandTime, sData); break;	// 待機時間
			case 7:	pFile->ToValue(m_TextInfo[nRow].nDisapTime, sData); break;	// 消える時間
			case 8:	pFile->ToValue(m_TextInfo[nRow].bTextBok, sData); break;	// Box表示
			case 9:	pFile->ToValue(m_TextInfo[nRow].nTextSize, sData); break;	// テキスト サイズ
			case 10:pFile->ToValue(*m_TextInfo[nRow].ActionTex, sData); break;	// テキスト
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
// テキスト情報の初期化
//========================================
void CTutorial::TextInit(int nIdx)
{
	m_TextInfo[nIdx].pos = INIT_D3DXVECTOR3;
	m_TextInfo[nIdx].size = INIT_D3DXVECTOR2;
	m_TextInfo[nIdx].nType = 0;
	m_TextInfo[nIdx].nStartTime = 0;
	m_TextInfo[nIdx].nStandTime = 0;
	m_TextInfo[nIdx].nDisapTime = 0;
	*m_TextInfo[nIdx].ActionTex = NULL;
	m_TextInfo[nIdx].nTextSize = 0;
	m_TextInfo[nIdx].nEndTime = 0;
	m_TextInfo[nIdx].bCreate = false;
	m_TextInfo[nIdx].bEnd = false;
	m_TextInfo[nIdx].bAction = false;
	m_TextInfo[nIdx].bTextBok = false;
}

//========================================
// テキスト生成
//========================================
void CTutorial::TexCreate(int nIdx)
{
	if (nIdx >= m_nTextMax - 1)
	{
		return;
	}

	if (m_TextInfo[nIdx].nType == m_nTextType && !m_TextInfo[nIdx].bCreate)
	{
		CText::Create(CText::BOX_NORMAL,
			m_TextInfo[nIdx].pos,
			m_TextInfo[nIdx].size,
			*m_TextInfo[nIdx].ActionTex,
			CFont::FONT_DOTGOTHIC,
			m_TextInfo[nIdx].nTextSize,
			m_TextInfo[nIdx].nStartTime,
			m_TextInfo[nIdx].nStandTime,
			m_TextInfo[nIdx].nDisapTime,
			m_TextInfo[nIdx].bTextBok);

		if (m_TextInfo[nIdx].nDisapTime == -1)
		{
			m_TextInfo[nIdx].nDisapTime = 5;
		}

		int nStrlen = (strlen(*m_TextInfo[nIdx].ActionTex) / 2);

		m_nTextCreate = (nStrlen * m_TextInfo[nIdx].nStartTime) +
			m_TextInfo[nIdx].nStandTime + (m_TextInfo[nIdx].nDisapTime - 5);

		m_TextInfo[nIdx].bCreate = true;
		m_nNumText++;
	}
}

//========================================
// チュートリアル
//========================================
void CTutorial::TutorialTex(void)
{
	// -- 取得 -------------------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CMouse *pInputMouse = CManager::GetInputMouse();			// マウス
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// ジョイパット

	// テキストの生成
	if (--m_nTextCreate <= 0)
	{
		m_nTextCreate = 0;
		TexCreate(m_nNumText);
	}

	switch (m_nTextType)
	{
	case ACTION_MOVE:// 移動
	{
		D3DXVECTOR3 move = m_pPlayer->GetPlayerMove();
		
		if (move.x <= -1.0f || move.x >= 1.0f)
		{
			if (m_nTextCreate <= 0)
			{
				CObject::ReleaseAll(CObject::TYPE_FONT);
				m_nTextType++;
			}
		}
	}
		break;
	case ACTION_CAMERA:	// 視点移動
	{
		D3DXVECTOR3 move = CManager::GetCamera()->GetInfo().spin;

		if (move.y <= -0.01f || move.y >= 0.01f)
		{
			if (m_nTextCreate <= 0)
			{
				CObject::ReleaseAll(CObject::TYPE_FONT);
				m_nTextType++;
			}
		}
	}
		break;
	case ACTION_SHOT:	// 発射
	{
		int nNumAll = CBullet::GetNumAll();

		if (nNumAll >= 3)
		{
			CObject::ReleaseAll(CObject::TYPE_FONT);
			m_nTextType++;
		}
	}
	break;
	case ACTION_SET:	// 配置(壁)
	{
		int nNumAll = CCube::GetNumAll();

		if (nNumAll >= 3)
		{
			CObject::ReleaseAll(CObject::TYPE_FONT);
			m_nTextType++;
		}
	}
	break;
	case ACTION_SET1:	// 配置(任意)
	{
		bool bSet = CPlayer::IsCubeSet();

		if (bSet)
		{
			CObject::ReleaseAll(CObject::TYPE_FONT);
			m_nTextType++;
		}
	}
	break;
	case ACTION_ENEMY:	// 敵
	{

	}
	break;
	case ACTION_CLEAR:	// 出口
	{

	}
	break;
	}
}

//========================================
// ブロックの読み込み
//========================================
void CTutorial::LoodBlock(void)
{
	CSVFILE *pFile = new CSVFILE;

	// 読み込み
	pFile->FileLood("data\\GAMEDATA\\BLOCK\\STAGE_DATA1.csv", true, true, ',');

	// 行数の取得
	int nRowMax = pFile->GetRowSize();

	// 各データに代入
	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		// 配置情報の生成
		int nType;				// 種類
		int nState;				// 状態
		D3DXVECTOR3 pos;		// 位置

								// 列数の取得
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(nType, sData); break;	// 種類
			case 1:	pFile->ToValue(pos.x, sData); break;	// 位置 X
			case 2:	pFile->ToValue(pos.y, sData); break;	// 位置 Y
			case 3:	pFile->ToValue(pos.z, sData); break;	// 位置 Z
			case 4: pFile->ToValue(nState, sData); break;	// 状態
			}
		}

		// 最大数に達したら返す
		if (nRow == nRowMax - 1)	// (列数 - 列の最大数 - ヘッダーの列数)
		{
			return;
		}

		// 配置
		CBlock *pObj = CBlock::Create(nType, pos, nState);
	}

	// メモリ開放
	delete pFile;
	pFile = NULL;
}

//========================================
// エネミーの読み込み
//========================================
void CTutorial::LoodEnemy(void)
{
	CSVFILE *pFile = new CSVFILE;

	pFile->FileLood("data\\GAMEDATA\\ENEMY\\STAGE_ENEMY1.csv", true, true, ',');

	// 行数の取得
	int nRowMax = pFile->GetRowSize();

	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		int nType, nMove;
		D3DXVECTOR3 pos;

		// 列数の取得
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(nType, sData); break;	// 種類
			case 1:	pFile->ToValue(nMove, sData); break;	// 移動種類
			case 2:	pFile->ToValue(pos.x, sData); break;	// 位置 X
			case 3:	pFile->ToValue(pos.y, sData); break;	// 位置 Y
			case 4:	pFile->ToValue(pos.z, sData); break;	// 位置 Z
			}
		}

		// 最大数に達したら返す
		if (nRow == nRowMax - 1)	// (列数 - 列の最大数 - ヘッダーの列数)
		{
			return;
		}

		CEnemy *pObj = CEnemy::Create(nType, nMove, pos);
	}

	delete pFile;
	pFile = NULL;
}