//========================================
// 
// ゲーム
// 
//========================================
// *** game.cpp ***
//========================================
#include "title.h"
#include "game.h"
#include "ranking.h"
#include "../system/csv_file.h"
#include "../object\UI\score.h"
#include "../object\UI\time.h"
#include "../object\model\block.h"
#include "../object/model/bullet_cube.h"
#include "../object\model\player.h"
#include "../object\model\enemy.h"
#include "../object\BG\bg_side.h"
#include "../object\BG\bg_ceiling.h"
#include "../object/BG/mesh_floor.h"
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
bool CGame::m_bTime = false;
int CGame::m_nSelectStage = Stage_EASY;

const char* CGame::SIDE_STAGE_EASY_FILE = "data\\GAMEDATA\\OBJECT\\SIDE_STAGE_EASY_DATA .txt";
const char* CGame::SIDE_STAGE_NORMAL_FILE = "data\\GAMEDATA\\OBJECT\\SIDE_STAGE_NORMAL_DATA.txt";
const char* CGame::SIDE_STAGE_DIFFICULT_FILE = "data\\GAMEDATA\\OBJECT\\SIDE_STAGE_DIFFICULT_DATA.txt";
const char* CGame::FLOOR_STAGE_EASY_FILE = "data\\GAMEDATA\\OBJECT\\FLOOR_STAGE_EASY_DATA.txt";
const char* CGame::FLOOR_STAGE_NORMAL_FILE = "data\\GAMEDATA\\OBJECT\\FLOOR_STAGE_NORMAL_DATA.txt";
const char* CGame::FLOOR_STAGE_DIFFICULT_FILE = "data\\GAMEDATA\\OBJECT\\FLOOR_STAGE_DIFFICULT_DATA.txt";
const char* CGame::BLOCK_FILE1 = "data\\GAMEDATA\\BLOCK\\STAGE_DATA1.csv";
const char* CGame::ENEMY_FILE1 = "data\\GAMEDATA\\ENEMY\\STAGE_ENEMY1.csv";


//========================================
// コンストラクタ
//========================================
CGame::CGame()
{
	m_rot = INIT_D3DXVECTOR3;
	m_nStartTime = 0;
	m_nEndTime = 0;
	m_bEnd = false;

	m_nRstStgType = 0;
	m_nTextCreate = 0;
	m_nTimeTotal = 0;
	m_nCubeTotal = 0;
	m_nTotal = 0;
	m_bAddScore = false;

	for (int nRst = 0; nRst < RST_ADD_SCORE; nRst++)
	{
		m_RstText[nRst] = NULL;
	}
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
	m_rot = INIT_D3DXVECTOR3;
	m_nStartTime = 0;
	m_nEndTime = 0;
	m_bEnd = false;
	m_bTime = false;

	m_nRstStgType = 0;
	m_nTextCreate = 0;
	m_nTimeTotal = 0;
	m_nCubeTotal = 0;
	m_nTotal = 0;

	CTitle::SetStart(false);
	CTitle::SetExit(false);
	CTitle::SetClear(false);

	// 背景(側面)の生成
	LoodSide();

	// 背景(天井)の生成
	LoodCeiling();

	// 床の生成
	LoodFloor();

	// ブロックの生成
	LoodBlock();

	CPlayer *pPlayer = CPlayer::Create();
	pPlayer->SetMotion("data\\GAMEDATA\\MODEL\\Player\\PLAYER_DATA.txt");

	// 敵の生成
	LoodEnemy();

	// キューブの制限数
	CCube::SetLimit(MAX_CUBE);

	// タイム生成
	m_pTime = CTime::Create(GAME_TIME);

	// スコア生成
	m_pScore = CScore::Create();
	CScore::SetScore();

	CCamera *pCamera = CManager::GetCamera();					// カメラ

	pCamera->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pCamera->SetHeigth(0.02f);
	pCamera->SetDistance(300.0f);

	FormFont pFont = {
		D3DXCOLOR(0.0f,0.63f,0.2f,1.0f),
		20.0f,
		15,
		10,
		30
	};

	CText::Create(CText::BOX_NORMAL_RECT,
		D3DXVECTOR3(640.0f, 300.0f, 0.0f),
		D3DXVECTOR2(440.0f, 100.0f),
		"90秒以内に攻略せよ！",
		CFont::FONT_BESTTEN,
		&pFont, false);

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
					FormFont pFont = {
						INIT_D3DXCOLOR,
						20.0f,
						12,
						120,
						30
					};

					FormShadow pShadow = {
						D3DXCOLOR(0.0f,0.0f,0.0f,1.0f),
						true,
						D3DXVECTOR3(2.0f,2.0f,0.0f),
						D3DXVECTOR2(1.0f,1.0f)
					};

					CText::Create(CText::BOX_NORMAL_RECT,
						D3DXVECTOR3(640.0f, 300.0f, 0.0f),
						D3DXVECTOR2(440.0f, 100.0f),
						"GAME CLEAR",
						CFont::FONT_BESTTEN,
						&pFont, false,&pShadow);

					m_nEndTime = (12 * 10) + 120 + 25;
					m_bEnd = true;
					m_bTime = true;
				}
				else
				{
					if (--m_nEndTime <= 0)
					{
						// リザルト演出
						Result();
					}
				}
			}
		}

		// 時間切れ
		if (m_pTime->GetTime() <= 0)
		{
			if (!m_bEnd)
			{
				FormFont pFont = {
					INIT_D3DXCOLOR,
					20.0f,
					12,
					10,
					30
				};

				CText::Create(CText::BOX_NORMAL_RECT,
					D3DXVECTOR3(640.0f, 300.0f, 0.0f),
					D3DXVECTOR2(440.0f, 100.0f),
					"TIME UP",
					CFont::FONT_BESTTEN,
					&pFont, false);

				m_nEndTime = (12 * 7) + 10 + 25;
				m_bEnd = true;
			}
			else
			{
				if (--m_nEndTime <= 0)
				{
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
// リザルト演出
//========================================
void CGame::Result(void)
{
	FormFont pFont = { INIT_D3DXCOLOR, 20.0f, 5, 5, 0};
	FormShadow pShadow = { D3DXCOLOR(0.0f,0.0f,0.0f,1.0f), true, D3DXVECTOR3(2.0f,2.0f,0.0f), D3DXVECTOR2(1.0f,1.0f)};

	char aString[TXT_MAX];
	int nLength = 0;
	D3DXVECTOR3 pos = INIT_D3DXVECTOR3;

	switch (m_nRstStgType)
	{
	case RST_TIME:
	{
		sprintf(aString, "TIME BONUS");
		pos = D3DXVECTOR3(100.0f, 100.0f, 0.0f);
	}
		break;
	case RST_TIME_CALC:
	{
		int nTime = m_pTime->GetTime();
		m_nTimeTotal = TIME_SCORE * nTime;

		sprintf(aString, "%d * %d = %d",TIME_SCORE,nTime,m_nTimeTotal);
		pos = D3DXVECTOR3(100.0f, 150.0f, 0.0f);
	}
		break;
	case RST_CUBE:
	{
		sprintf(aString, "CUBE BONUS");
		pos = D3DXVECTOR3(100.0f, 250.0f, 0.0f);
	}
		break;
	case RST_CUBE_CALC:
	{
		int nCube = CCube::GetRest();
		m_nCubeTotal = CUBE_SCORE * nCube;

		sprintf(aString, "%d * %d = %d", CUBE_SCORE, nCube, m_nCubeTotal);
		pos = D3DXVECTOR3(100.0f, 300.0f, 0.0f);
	}
		break;
	case RST_BONUS:
	{
		sprintf(aString, "TOTAL BONUS");
		pos = D3DXVECTOR3(100.0f, 500.0f, 0.0f);
	}
		break;
	case RST_BONUS_CALC:
	{
		m_nTotal = m_nTimeTotal + m_nCubeTotal;

		sprintf(aString, "%d",m_nTotal);
		pos = D3DXVECTOR3(100.0f, 550.0f, 0.0f);
	}
		break;
	case RST_ADD_SCORE:
	{
		if (m_bAddScore)
		{
			if (m_nTotal <= 0)
			{
				m_nStandTime = 120;
				m_nRstStgType++;
			}
			else
			{
				m_nTotal -= 10;
				CScore::SetScore(10);

				char aTotal[TXT_MAX];

				sprintf(aTotal, "%d", m_nTotal);
				m_RstText[RST_BONUS_CALC]->ChgText(aTotal, INIT_D3DXCOLOR);
			}
		}
		else
		{
			if (--m_nTextCreate <= 0)
			{
				m_nTextCreate = 0;
				m_bAddScore = true;
			}
		}
	}
		break;
	case RST_STAND:
	{
		if (m_nStandTime-- <= 0)
		{
			m_nRstStgType++;
		}
	}
		break;
	case RST_END:
	{
		CManager::GetFade()->SetFade(MODE_RANKING);
		CRanking::SetScore11(m_pScore->GetScore());
	}
		break;
	}

	// テキストの生成
	if (m_nRstStgType < RST_ADD_SCORE)
	{
		if (--m_nTextCreate <= 0)
		{
			m_nTextCreate = 0;
			nLength = strlen(aString);

			m_RstText[m_nRstStgType] = CText::Create(CText::BOX_NORMAL_RECT, pos, D3DXVECTOR2(0.0f, 0.0f),
				aString, CFont::FONT_BESTTEN, &pFont, false, &pShadow);

			m_nTextCreate = (nLength * 5) + 5;
			m_nRstStgType++;
		}
	}	

	
}


//================================================================================
//--------------------------------------------------------------------------------
// 設定
//--------------------------------------------------------------------------------
//================================================================================

//========================================
// ステージ選択
//========================================
void CGame::SetStage(int nStage)
{
	m_nSelectStage = nStage;
}

//================================================================================
//--------------------------------------------------------------------------------
// 読み込み
//--------------------------------------------------------------------------------
//================================================================================

//========================================
// 天井
//========================================
void CGame::LoodCeiling(void)
{
	CBgCeiling *pBgCeiling = CBgCeiling::Create(m_nSelectStage);
}

//========================================
// 側面
//========================================
void CGame::LoodSide(void)
{
	// 変数宣言
	char aDataSearch[128] = {};		// 文字列比較用の変数
	char g_aEqual[128] = {};		// ＝読み込み用変数

	// ファイルポインタの宣言
	FILE * pFile;

	//ファイルを開く
	switch (m_nSelectStage)
	{
	case CGame::Stage_EASY:
		pFile = fopen(SIDE_STAGE_EASY_FILE, "r");
		break;
	case CGame::Stage_NORMAL:
		pFile = fopen(SIDE_STAGE_NORMAL_FILE, "r");
		break;
	case CGame::Stage_DIFFICULT:
		pFile = fopen(SIDE_STAGE_DIFFICULT_FILE, "r");
		break;
	default:
		pFile = fopen(SIDE_STAGE_EASY_FILE, "r");
		break;
	}

	// ファイルが開けたら
	if (pFile != NULL)
	{//ファイルが開いた場合

	 // END_SCRIPTが見つかるまで読み込みを繰り返す
		while (1)
		{
			fscanf(pFile, "%s", aDataSearch);	// 検索

			if (!strcmp(aDataSearch, "END_SCRIPT"))
			{// 読み込みを終了
				fclose(pFile);
				break;
			}
			else if (aDataSearch[0] == '#')
			{// 折り返す
				continue;
			}
			else if (!strcmp(aDataSearch, "CREATE_SIDE"))
			{// 生成開始
				
				while (1)
				{
					fscanf(pFile, "%s", aDataSearch);

					if (!strcmp(aDataSearch, "END_CREATE_SIDE"))
					{// 生成終了
						break;
					}
					else if (!strcmp(aDataSearch, "SET_SIDE"))
					{// 生成情報の読み込み
						D3DXVECTOR3 pos = INIT_D3DXVECTOR3;	// 位置
						D3DXVECTOR3 rot = INIT_D3DXVECTOR3;	// 向き
						D3DXCOLOR	color = INIT_D3DXCOLOR;	// 色
						float fHeight = 0;					// 高さ
						float fRadius = 0;					// 半径
						int *nType = 0;						// 画像種類
						int nNumTex = 0;					// 画像数
						int nDivisionX = 1;					// 分割幅
						int nDivisionY = 1;					// 分割高さ
						float *fTexV = 0;					// テクスチャ座標の開始位置(X軸)

						int nCntTex = 0; // 画像カウント

						while (1)
						{
							fscanf(pFile, "%s", aDataSearch);

							if (!strcmp(aDataSearch, "END_SIDE"))
							{// 読み込みを終了

								CBgSide *pBgSide = CBgSide::Create(
								pos,rot,color,fHeight,fRadius,nType,nNumTex,
									nDivisionX,nDivisionY,fTexV);

								delete[] nType;
								nType = NULL;

								delete[] fTexV;
								fTexV = NULL;

								break;
							}
							else if (!strcmp(aDataSearch, "POS"))
							{// 位置
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &pos.x);
								fscanf(pFile, "%f", &pos.y);
								fscanf(pFile, "%f", &pos.z);
							}
							else if (!strcmp(aDataSearch, "ROT"))
							{// 向き
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &rot.x);
								fscanf(pFile, "%f", &rot.y);
								fscanf(pFile, "%f", &rot.z);
							}
							else if (!strcmp(aDataSearch, "COLOR"))
							{// 色
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &color.r);
								fscanf(pFile, "%f", &color.g);
								fscanf(pFile, "%f", &color.b);
								fscanf(pFile, "%f", &color.a);
							}
							else if (!strcmp(aDataSearch, "HEIGHT"))
							{// 高さ
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &fHeight);
							}
							else if (!strcmp(aDataSearch, "RADIUS"))
							{// 半径
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &fRadius);
							}
							else if (!strcmp(aDataSearch, "NUMTEX"))
							{// 画像数
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nNumTex);

								// メモリの解放
								nType = new int[nNumTex];
								fTexV = new float[nNumTex];
							}
							else if (!strcmp(aDataSearch, "SET_TEX"))
							{// 画像関連の設定

								while (1)
								{
									fscanf(pFile, "%s", aDataSearch);

									if (!strcmp(aDataSearch, "END_TEX"))
									{// 読み込みを終了
										nCntTex++;
										break;
									}
									else if (!strcmp(aDataSearch, "TYPE"))
									{// 半径
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%d", &nType[nCntTex]);
									}
									else if (!strcmp(aDataSearch, "TEX_V"))
									{// 画像数
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%f", &fTexV[nCntTex]);
									}
								}
							}
							else if (!strcmp(aDataSearch, "DIVISION_X"))
							{// 分割幅
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nDivisionX);
							}
							else if (!strcmp(aDataSearch, "DIVISION_Y"))
							{// 分割高さ
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nDivisionY);
							}
						}
					}
				}
			}
		}
	}
}

//========================================
// 床
//========================================
void CGame::LoodFloor(void)
{
	// 変数宣言
	char aDataSearch[128] = {};		// 文字列比較用の変数
	char g_aEqual[128] = {};		// ＝読み込み用変数

	// ファイルポインタの宣言
	FILE * pFile;

	//ファイルを開く
	switch (m_nSelectStage)
	{
	case CGame::Stage_EASY:
		pFile = fopen(FLOOR_STAGE_EASY_FILE, "r");
		break;
	case CGame::Stage_NORMAL:
		pFile = fopen(FLOOR_STAGE_NORMAL_FILE, "r");
		break;
	case CGame::Stage_DIFFICULT:
		pFile = fopen(FLOOR_STAGE_DIFFICULT_FILE, "r");
		break;
	default:
		pFile = fopen(FLOOR_STAGE_EASY_FILE, "r");
		break;
	}

	// ファイルが開けたら
	if (pFile != NULL)
	{//ファイルが開いた場合

	 // END_SCRIPTが見つかるまで読み込みを繰り返す
		while (1)
		{
			fscanf(pFile, "%s", aDataSearch);	// 検索

			if (!strcmp(aDataSearch, "END_SCRIPT"))
			{// 読み込みを終了
				fclose(pFile);
				break;
			}
			else if (aDataSearch[0] == '#')
			{// 折り返す
				continue;
			}
			else if (!strcmp(aDataSearch, "CREATE_FLOOR"))
			{// 生成開始

				while (1)
				{
					fscanf(pFile, "%s", aDataSearch);

					if (!strcmp(aDataSearch, "END_CREATE_FLOOR"))
					{// 生成終了
						break;
					}
					else if (!strcmp(aDataSearch, "SET_FLOOR"))
					{// 生成情報の読み込み
						D3DXVECTOR3 pos = INIT_D3DXVECTOR3;	// 位置
						D3DXVECTOR3 rot = INIT_D3DXVECTOR3;	// 向き
						D3DXCOLOR	color = INIT_D3DXCOLOR;	// 色
						float fWidth = 0;					// 幅
						float fHeight = 0;					// 高さ
						int *nType = 0;						// 画像種類
						int nNumTex = 0;					// 画像数
						int nDivisionX = 1;					// 分割幅
						int nDivisionY = 1;					// 分割高さ
						bool bDivision = false;				// テクスチャの分割するか
						float *fTexX = 0;					// テクスチャ座標の開始位置(X軸)
						float *fTexY = 0;					// テクスチャ座標の開始位置(Y軸)


						int nCntTex = 0; // 画像カウント

						while (1)
						{
							fscanf(pFile, "%s", aDataSearch);

							if (!strcmp(aDataSearch, "END_FLOOR"))
							{// 読み込みを終了

								CFloor *pBgSide = CFloor::Create(
									pos, rot, color, fWidth,fHeight, nType, nNumTex, bDivision,
									nDivisionX, nDivisionY, fTexX, fTexY);

								break;
							}
							else if (!strcmp(aDataSearch, "POS"))
							{// 位置
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &pos.x);
								fscanf(pFile, "%f", &pos.y);
								fscanf(pFile, "%f", &pos.z);
							}
							else if (!strcmp(aDataSearch, "ROT"))
							{// 向き
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &rot.x);
								fscanf(pFile, "%f", &rot.y);
								fscanf(pFile, "%f", &rot.z);
							}
							else if (!strcmp(aDataSearch, "COLOR"))
							{// 色
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &color.r);
								fscanf(pFile, "%f", &color.g);
								fscanf(pFile, "%f", &color.b);
								fscanf(pFile, "%f", &color.a);
							}
							else if (!strcmp(aDataSearch, "WIDTH"))
							{// 幅
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &fWidth);
							}
							else if (!strcmp(aDataSearch, "HEIGHT"))
							{// 高さ
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &fHeight);
							}
							else if (!strcmp(aDataSearch, "NUMTEX"))
							{// 画像数
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nNumTex);

								// メモリの解放
								nType = new int[nNumTex];
								fTexX = new float[nNumTex];
								fTexY = new float[nNumTex];
							}
							else if (!strcmp(aDataSearch, "DIVISION"))
							{// テクスチャの分割するか
								int nData;

								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nData);

								if (nData <= 0)
								{
									bDivision = false;
								}
								else
								{
									bDivision = true;
								}
							}
							else if (!strcmp(aDataSearch, "SET_TEX"))
							{// 画像関連の設定

								while (1)
								{
									fscanf(pFile, "%s", aDataSearch);

									if (!strcmp(aDataSearch, "END_TEX"))
									{// 読み込みを終了
										nCntTex++;
										break;
									}
									else if (!strcmp(aDataSearch, "TYPE"))
									{// 半径
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%d", &nType[nCntTex]);
									}
									else if (!strcmp(aDataSearch, "TEX_X"))
									{// テクスチャの移動量(X軸)
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%f", &fTexX[nCntTex]);
									}
									else if (!strcmp(aDataSearch, "TEX_Y"))
									{// テクスチャの移動量(Y軸)
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%f", &fTexY[nCntTex]);
									}
								}
							}
							else if (!strcmp(aDataSearch, "DIVISION_X"))
							{// 分割幅
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nDivisionX);
							}
							else if (!strcmp(aDataSearch, "DIVISION_Y"))
							{// 分割高さ
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nDivisionY);
							}
						}
					}
				}
			}
		}
	}
}

//========================================
// ブロック
//========================================
void CGame::LoodBlock(void)
{
	CSVFILE *pFile = new CSVFILE;

	// 読み込み
	switch (m_nSelectStage)
	{
	case CGame::Stage_EASY:
		pFile->FileLood(BLOCK_FILE1, true, true, ',');
		break;
	case CGame::Stage_NORMAL:
		pFile->FileLood(BLOCK_FILE1, true, true, ',');
		break;
	case CGame::Stage_DIFFICULT:
		pFile->FileLood(BLOCK_FILE1, true, true, ',');
		break;
	default:
		pFile->FileLood(BLOCK_FILE1, true, true, ',');
		break;
	}


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
// エネミー
//========================================
void CGame::LoodEnemy(void)
{
	CSVFILE *pFile = new CSVFILE;

	// 読み込み
	switch (m_nSelectStage)
	{
	case CGame::Stage_EASY:
		pFile->FileLood(ENEMY_FILE1, true, true, ',');
		break;
	case CGame::Stage_NORMAL:
		pFile->FileLood(ENEMY_FILE1, true, true, ',');
		break;
	case CGame::Stage_DIFFICULT:
		pFile->FileLood(ENEMY_FILE1, true, true, ',');
		break;
	default:
		pFile->FileLood(ENEMY_FILE1, true, true, ',');
		break;
	}

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