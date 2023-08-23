//========================================
// 
// ゲーム
// 
//========================================
// *** game.cpp ***
//========================================
#include "title.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "../system/csv_file.h"
#include "../object\UI\score.h"
#include "../object\UI\time.h"
#include "../object\model\block.h"
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
CPlayer *CGame::m_pPlayer = NULL;
CTime *CGame::m_pTime = NULL;
CScore *CGame::m_pScore = NULL;

//========================================
// コンストラクタ
//========================================
CGame::CGame()
{
	m_rot = INIT_D3DXVECTOR3;
	m_nStartTime = 0;
	m_nEndTime = 0;
	m_bEnd = false;
}

//========================================
// デストラクタ
//========================================
CGame::~CGame()
{

}

//========================================
// 初期化
//========================================
HRESULT CGame::Init(void)
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

	CPlayer *pPlayer = CPlayer::Create();
	pPlayer->SetMotion("data\\GAMEDATA\\MODEL\\Player\\PLAYER_DATA.txt");

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
		m_pTime->SetTime(GAME_TIME*2);
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

	CText::Create(CText::BOX_NORMAL,
		D3DXVECTOR3(640.0f, 300.0f, 0.0f),
		D3DXVECTOR2(440.0f, 100.0f),
		"平原ステージ！\n６０秒以内で攻略せよ！",
		CFont::FONT_DOTGOTHIC,
		20.0f,
		15, 10, 30, false);
	m_nStartTime = (15 * 18) + 10 + 25;
	m_nMoveRot = ((D3DX_PI * 2) / m_nStartTime);

	return S_OK;
}

//========================================
// 終了
//========================================
void CGame::Uninit(void)
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
}

//========================================
// 更新
//========================================
void CGame::Update(void)
{
	// -- 取得 -------------------------------------------
	CCamera *pCamera = CManager::GetCamera();					// カメラ
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// キーボード
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// ジョイパット

	// ポーズ
	if (pInputKeyboard->GetTrigger(DIK_P) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_START))
	{
		CPause::SetPause(true);
	}

	// 開始フラグ
	{
		bool bStart = CTitle::IsStart();
		if (!bStart)
		{
			pCamera->SetRot(m_rot);
			m_rot.y += m_nMoveRot;

			if (--m_nStartTime <= 0)
			{
				pCamera->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				pCamera->SetHeigth(0.4f);
				pCamera->SetDistance(500.0f);
				CTitle::SetStart(true);
			}
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
						"GAME CLEAR",
						CFont::FONT_DOTGOTHIC,
						20.0f,
						12, 10, 30, false);

					m_nEndTime = (12 * 10) + 10 + 25;
					m_bEnd = true;
				}
				else
				{
					if (--m_nEndTime <= 0)
					{
						CResult::SetVerdict(CResult::VERDICT_GAMECLEAR);
						CManager::GetFade()->SetFade(MODE_RANKING);

						CRanking::SetScore11(m_pScore->GetScore());
					}
				}
			}
		}

		// 時間切れ
		if (m_pTime->GetTime() <= 0)
		{
			if (!m_bEnd)
			{
				CText::Create(CText::BOX_NORMAL,
					D3DXVECTOR3(640.0f, 300.0f, 0.0f),
					D3DXVECTOR2(440.0f, 100.0f),
					"TIME UP",
					CFont::FONT_DOTGOTHIC,
					20.0f,
					12, 10, 30, false);

				m_nEndTime = (12 * 7) + 10 + 25;
				m_bEnd = true;
			}
			else
			{
				if (--m_nEndTime <= 0)
				{
					CResult::SetVerdict(CResult::VERDICT_GAMEOVER);
					CManager::GetFade()->SetFade(MODE_RANKING);
				}
			}
		}
	}
}

//========================================
// 描画
//========================================
void CGame::Draw(void)
{

}

//========================================
// 生成
//========================================
CGame *CGame::Create(void)
{
	CGame *pGame = new CGame;

	pGame->Init();

	return pGame;
}

//========================================
// ブロックの読み込み
//========================================
void CGame::LoodBlock(void)
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
		CBlock *pObj = CBlock::Create(nType, pos,nState);
	}

	// メモリ開放
	delete pFile;
	pFile = NULL;
}

//========================================
// エネミーの読み込み
//========================================
void CGame::LoodEnemy(void)
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