//========================================
// 
// �Q�[��
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
#include "../object/BG/blackout.h"
#include "../object\UI\text2D.h"
#include "../system/input.h"
#include "../system/words/text.h"
#include "../system/words/font.h"
#include "../system/camera.h"
#include "../scene/pause.h"
#include "fade.h"

// �ÓI�ϐ�
CPlayer *CGame::m_pPlayer = NULL;
CTime *CGame::m_pTime = NULL;
CScore *CGame::m_pScore = NULL;
bool CGame::m_bTime = false;
int CGame::m_nStage = STAGE_EASY;
int CGame::m_nSelectStage = STAGE_EASY;
int CGame::m_nScore = 0;
CGame::StageInfo CGame::m_aStageInfo = { NULL,NULL };

const char* CGame::STAGE_INFO_FILE = "data\\GAMEDATA\\STAGE_DATA.txt";
const char* CGame::SIDE_STAGE_FILE = "data\\GAMEDATA\\OBJECT\\SIDE_DATA .txt";
const char* CGame::FLOOR_STAGE_FILE = "data\\GAMEDATA\\OBJECT\\FLOOR_DATA.txt";

//========================================
// �R���X�g���N�^
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
	m_nClearTotal = 0;
	m_nTotal = 0;
	m_nAddTime = 0;
	m_bAddScore = false;

	for (int nRst = 0; nRst < RST_ADD_SCORE; nRst++)
	{
		m_RstText[nRst] = NULL;
	}
}

//========================================
// �f�X�g���N�^
//========================================
CGame::~CGame()
{

}

//========================================
// ������
//========================================
HRESULT CGame::Init(void)
{
	CBlock::Reset();

	m_rot = INIT_D3DXVECTOR3;
	m_nStartTime = 0;
	m_nEndTime = 0;
	m_bEnd = false;
	m_bTime = false;

	m_nRstStgType = 0;
	m_nTextCreate = 0;
	m_nTimeTotal = 0;
	m_nClearTotal = 0;
	m_nEveGame = 0;
	m_nTotal = 0;
	m_nAddTime = ADDTIME_MAX;

	CTitle::SetStart(false);
	CTitle::SetClear(false);

	// �w�i(����)�̐���
	LoodSide();

	// �w�i(�V��)�̐���
	LoodCeiling();

	// ���̐���
	LoodFloor();

	// �u���b�N�̐���
	LoodBlock();

	CPlayer *pPlayer = CPlayer::Create(m_aStageInfo.PlayerPos[m_nStage],m_aStageInfo.PlayerRot[m_nStage]);
	pPlayer->SetMotion("data\\GAMEDATA\\MODEL\\Player\\PLAYER_DATA.txt");

	// �G�̐���
	LoodEnemy();

	// �L���[�u�̐�����
	CCube::SetUseCube();

	// �^�C������
	m_pTime = CTime::Create(m_aStageInfo.nTime[m_nStage]);

	// �X�R�A����
	m_pScore = CScore::Create();
	CScore::SetScore(m_nScore);

	CCamera *pCamera = CManager::GetCamera();					// �J����
	pCamera->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	pCamera->SetHeigth(0.4f);
	pCamera->SetDistance(1400.0f);

	FormFont pFont = {INIT_D3DXCOLOR,20.0f,15,40,30};

	FormShadow pShadow = {D3DXCOLOR(0.0f,0.0f,0.0f,1.0f),true,D3DXVECTOR3(2.0f,2.0f,0.0f),D3DXVECTOR2(1.0f,1.0f)};

	char aString[TXT_MAX];

	// �ǂݍ���
	sprintf(aString, "STAGE %d",m_nStage + 1);

	int nStrlen = strlen(aString);

	CText::Create(CText::BOX_NORMAL_RECT,
		D3DXVECTOR3(640.0f, 350.0f, 0.0f),D3DXVECTOR2(440.0f, 100.0f),
		aString,CFont::FONT_BESTTEN,&pFont, false,&pShadow);

	m_nStartTime = (nStrlen * 15) + 10 + 10;
	m_nMoveRot = ((D3DX_PI * 2) / m_nStartTime);

	return S_OK;
}

//========================================
// �I��
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
// �X�V
//========================================
void CGame::Update(void)
{
	// -- �擾 -------------------------------------------
	CCamera *pCamera = CManager::GetCamera();					// �J����
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g

	// �|�[�Y
	if (pInputKeyboard->GetTrigger(DIK_P) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_START))
	{
		CPause::SetPause(true);
	}

	// �J�n�t���O
	{
		bool bStart = CTitle::IsStart();
		if (!bStart)
		{
			/*pCamera->SetRot(m_rot);
			m_rot.y += m_nMoveRot;*/

			if (--m_nStartTime <= 0)
			{
				pCamera->SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				pCamera->SetHeigth(0.4f);
				pCamera->SetDistance(500.0f);
				CTitle::SetStart(true);
			}
		}
	}

	// �G�l�~�[�̑S��
	{
		bool bClear = CTitle::IsClear();
		if (!bClear && CEnemy::GetEnemyAll() <= 0)
		{
			CTitle::SetClear(true);
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
						// ���U���g���o
						Result();
					}
				}
			}
		}

		// ���Ԑ؂�
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
					CRanking::SetScore11(m_pScore->GetScore());
					CRanking::SetAllStage(false);
				}
			}
		}
	}
}

//========================================
// �`��
//========================================
void CGame::Draw(void)
{

}

//========================================
// ����
//========================================
CGame *CGame::Create(void)
{
	CGame *pGame = new CGame;

	pGame->Init();

	return pGame;
}

//========================================
// ���U���g���o
//========================================
void CGame::Result(void)
{
	FormFont pFont = { INIT_D3DXCOLOR, 18.0f, 3, 5, 0};
	FormShadow pShadow = { D3DXCOLOR(0.0f,0.0f,0.0f,1.0f), true, D3DXVECTOR3(2.0f,2.0f,0.0f), D3DXVECTOR2(2.0f,2.0f)};

	char aString[TXT_MAX];
	int nLength = 0;
	D3DXVECTOR3 pos = INIT_D3DXVECTOR3;

	switch (m_nRstStgType)
	{
	case RST_TEXT:
	{
		CBlackout::Create();
		sprintf(aString, "STAGE CLEAR RESULT BONUS");
		pos = D3DXVECTOR3(23.0f, 100.0f, 0.0f);

		int nUseCube = CCube::GetUse();
		int nPerfCube = m_aStageInfo.nCube[m_nStage];

		if (nUseCube <= nPerfCube)
		{
			m_nEveGame = EVE_PERFECT;
		}
		else if (nUseCube <= nPerfCube + 10)
		{
			m_nEveGame = EVE_GREAT;
		}
		else
		{
			m_nEveGame = EVE_USUALLY;
		}
	}
	break;
	case RST_TIME:
	{
		sprintf(aString, "TIME BONUS");
		pos = D3DXVECTOR3(100.0f, 170.0f, 0.0f);
	}
		break;
	case RST_TIME_CALC:
	{
		int nTime = m_pTime->GetTime();
		m_nTimeTotal = TIME_SCORE * nTime;

		sprintf(aString, "%d * %d = %d",TIME_SCORE,nTime,m_nTimeTotal);
		pos = D3DXVECTOR3(100.0f, 240.0f, 0.0f);
	}
		break;
	case RST_CLEAR:
	{
		if (m_nEveGame == EVE_PERFECT)
		{
			sprintf(aString, "PERFECT BONUS");
		}
		else if (m_nEveGame == EVE_GREAT)
		{
			sprintf(aString, "GREAT BONUS");
		}
		else
		{
			sprintf(aString, "CLEAR BONUS");
		}

		pos = D3DXVECTOR3(100.0f, 310.0f, 0.0f);
	}
		break;
	case RST_CLEAR_CALC:
	{
		int nClear = m_aStageInfo.nClearBonus[m_nStage];

		int nUseCube = CCube::GetUse();
		int nPerfCube = m_aStageInfo.nCube[m_nStage];
		int nEve;

		// �{��
		if (m_nEveGame == EVE_PERFECT)
		{
			nEve = 5;
		}
		else if (m_nEveGame == EVE_GREAT)
		{
			nEve = 3;
		}
		else
		{
			nEve = 1;
		}

		m_nClearTotal = nClear * nEve;

		sprintf(aString, "%d", m_nClearTotal);
		pos = D3DXVECTOR3(100.0f, 380.0f, 0.0f);
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
		m_nTotal = m_nTimeTotal + m_nClearTotal;

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
				if (m_nStage < STAGE_MAX)
				{
					char aString[TXT_MAX];
					sprintf(aString, "NEXT��STAGE%d", m_nStage + 2);

					int nStrlen = strlen(aString);

					CText::Create(CText::BOX_NORMAL_RECT,
						D3DXVECTOR3(1000.0f, 650.0f, 0.0f), D3DXVECTOR2(440.0f, 100.0f),
						aString, CFont::FONT_BESTTEN, &pFont, false, &pShadow);

					m_nStandTime = (nStrlen * 15) + 10 + 10;
				}
				else if (m_nStage == STAGE_MAX)
				{
					char aString[TXT_MAX];
					sprintf(aString, "NEXT��RANKING");

					int nStrlen = strlen(aString);

					CText::Create(CText::BOX_NORMAL_RECT,
						D3DXVECTOR3(1000.0f, 650.0f, 0.0f), D3DXVECTOR2(440.0f, 100.0f),
						aString, CFont::FONT_BESTTEN, &pFont, false, &pShadow);

					m_nStandTime = 120;
				}

				m_nRstStgType++;
			}
			else
			{
				int AddScore;
				AddScore = (m_nTotal / m_nAddTime);
				m_nTotal -= AddScore;
				m_nAddTime--;

				if (m_nTotal <= 0)
				{
					m_nTotal = 0;
					AddScore = AddScore - m_nTotal;
				}

				CScore::SetScore(AddScore);

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
		if (++m_nStage < STAGE_MAX)
		{
			m_nScore = m_pScore->GetScore();
			CManager::GetFade()->SetFade(MODE_GAME);
		}
		else if (m_nStage >= STAGE_MAX)
		{
			CManager::GetFade()->SetFade(MODE_RANKING);
			m_nScore = m_pScore->GetScore();
			CRanking::SetScore11(m_nScore);
			CRanking::SetAllStage(false);
		}
	}
		break;
	}

	// �e�L�X�g�̐���
	if (m_nRstStgType < RST_ADD_SCORE)
	{
		if (--m_nTextCreate <= 0)
		{
			if (m_nRstStgType == RST_TEXT || m_nRstStgType == RST_CLEAR)
			{
				switch (m_nEveGame)
				{
				case EVE_PERFECT:
					pFont = { D3DXCOLOR(1.0f,0.96f,0,1)	, 20.0f, 1, 5, 0 };
					break;
				case EVE_GREAT:
					pFont = { D3DXCOLOR(0.5f,0.5f,0.5f,1), 20.0f, 1, 5, 0 };
					break;
				case EVE_USUALLY:
					pFont = { D3DXCOLOR(0.0f,0.84f,1,1), 20.0f, 1, 5, 0 };
					break;
				default:
					pFont = { INIT_D3DXCOLOR, 20.0f, 1, 5, 0 };
					break;
				}

				pShadow = { INIT_D3DXCOLOR, true, D3DXVECTOR3(1.0f,1.0f,0.0f), D3DXVECTOR2(1.0f,1.0f) };
			}

			m_nTextCreate = 0;
			nLength = strlen(aString);

			m_RstText[m_nRstStgType] = CText::Create(CText::BOX_NORMAL_RECT, pos, D3DXVECTOR2(0.0f, 0.0f),
				aString, CFont::FONT_BESTTEN, &pFont, false, &pShadow);

			if (m_nRstStgType == RST_TEXT)
			{
				m_nTextCreate = (nLength * 1) + 5;
			}
			else
			{
				m_nTextCreate = (nLength * 3) + 5;
			}
			m_nRstStgType++;
		}
	}	
}

//========================================
// ���Z�b�g
//========================================
void CGame::Reset(void)
{
	m_nStage = STAGE_EASY;
	m_bTime = false;
	m_nScore = 0;
	m_aStageInfo = { NULL,NULL };
}

//================================================================================
//--------------------------------------------------------------------------------
// �ݒ�
//--------------------------------------------------------------------------------
//================================================================================

//========================================
// �X�e�[�W�I��
//========================================
void CGame::SetStage(int nStage)
{
	m_nSelectStage = nStage;
}

//================================================================================
//--------------------------------------------------------------------------------
// �ǂݍ���
//--------------------------------------------------------------------------------
//================================================================================

//========================================
// �X�e�[�W���
//========================================
void CGame::LoodStage(void)
{
	char aDataSearch[TXT_MAX];	// �f�[�^�����p

	// �t�@�C���̓ǂݍ���
	FILE *pFile = fopen(STAGE_INFO_FILE, "r");

	if (pFile == NULL)
	{// ��ޖ��̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ�A
	 //�������I������
		return;
	}

	// END_SCRIPT��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", &aDataSearch[0]);

		if (!strcmp(aDataSearch, "END_SCRIPT"))
		{// �ǂݍ��݂��I��
			fclose(pFile);
			break;
		}
		else if (aDataSearch[0] == '#')
		{// �܂�Ԃ�
			continue;
		}
		else if (!strcmp(aDataSearch, "SET_INFO"))
		{// �����J�n

			int nCntStage = 0;
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch);

				if (!strcmp(aDataSearch, "END_INFO"))
				{// �����I��
					break;
				}
				else if (!strcmp(aDataSearch, "SET_STAGE"))
				{
					while (1)
					{
						fscanf(pFile, "%s", aDataSearch);

						if (!strcmp(aDataSearch, "END_STAGE"))
						{// �����I��
							nCntStage++;
							break;
						}
						else if (nCntStage > STAGE_MAX)
						{// �܂�Ԃ�
							continue;
						}
						else if (!strcmp(aDataSearch, "TIME"))
						{
							fscanf(pFile, "%s", &aDataSearch[0]);
							fscanf(pFile, "%d", &m_aStageInfo.nTime[nCntStage]);
						}
						else if (!strcmp(aDataSearch, "CUBE"))
						{
							fscanf(pFile, "%s", &aDataSearch[0]);
							fscanf(pFile, "%d", &m_aStageInfo.nCube[nCntStage]);
						}
						else if (!strcmp(aDataSearch, "CLEAR"))
						{
							fscanf(pFile, "%s", &aDataSearch[0]);
							fscanf(pFile, "%d", &m_aStageInfo.nClearBonus[nCntStage]);
						}
						else if (!strcmp(aDataSearch, "BLOCK"))
						{
							fscanf(pFile, "%s", &aDataSearch[0]);
							fscanf(pFile, "%s", &m_aStageInfo.aBlockFile[nCntStage][0]); // �t�@�C����
						}
						else if (!strcmp(aDataSearch, "PLAYER_POS"))
						{
							fscanf(pFile, "%s", &aDataSearch[0]);
							fscanf(pFile, "%f", &m_aStageInfo.PlayerPos[nCntStage].x);
							fscanf(pFile, "%f", &m_aStageInfo.PlayerPos[nCntStage].y);
							fscanf(pFile, "%f", &m_aStageInfo.PlayerPos[nCntStage].z);
						}
						else if (!strcmp(aDataSearch, "PLAYER_ROT"))
						{
							fscanf(pFile, "%s", &aDataSearch[0]);
							fscanf(pFile, "%f", &m_aStageInfo.PlayerRot[nCntStage]);
						}
					}
				}
				else if (!strcmp(aDataSearch, "ENEMY"))
				{
					fscanf(pFile, "%s", &aDataSearch[0]);
					fscanf(pFile, "%s", &m_aStageInfo.aEnemyFile[0]); // �t�@�C����
				}
			}
		}
	}
}

//========================================
// �V��
//========================================
void CGame::LoodCeiling(void)
{
	CBgCeiling *pBgCeiling = CBgCeiling::Create(m_nSelectStage);
}

//========================================
// ����
//========================================
void CGame::LoodSide(void)
{
	// �ϐ��錾
	char aDataSearch[128] = {};		// �������r�p�̕ϐ�
	char g_aEqual[128] = {};		// ���ǂݍ��ݗp�ϐ�

	// �t�@�C���|�C���^�̐錾
	FILE * pFile;

	//�t�@�C�����J��
	pFile = fopen(SIDE_STAGE_FILE, "r");

	// �t�@�C�����J������
	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	 // END_SCRIPT��������܂œǂݍ��݂��J��Ԃ�
		while (1)
		{
			fscanf(pFile, "%s", aDataSearch);	// ����

			if (!strcmp(aDataSearch, "END_SCRIPT"))
			{// �ǂݍ��݂��I��
				fclose(pFile);
				break;
			}
			else if (aDataSearch[0] == '#')
			{// �܂�Ԃ�
				continue;
			}
			else if (!strcmp(aDataSearch, "CREATE_SIDE"))
			{// �����J�n
				
				while (1)
				{
					fscanf(pFile, "%s", aDataSearch);

					if (!strcmp(aDataSearch, "END_CREATE_SIDE"))
					{// �����I��
						break;
					}
					else if (!strcmp(aDataSearch, "SET_SIDE"))
					{// �������̓ǂݍ���
						D3DXVECTOR3 pos = INIT_D3DXVECTOR3;	// �ʒu
						D3DXVECTOR3 rot = INIT_D3DXVECTOR3;	// ����
						D3DXCOLOR	color = INIT_D3DXCOLOR;	// �F
						float fHeight = 0;					// ����
						float fRadius = 0;					// ���a
						int *nType = 0;						// �摜���
						int nNumTex = 0;					// �摜��
						int nDivisionX = 1;					// ������
						int nDivisionY = 1;					// ��������
						float *fTexV = 0;					// �e�N�X�`�����W�̊J�n�ʒu(X��)

						int nCntTex = 0; // �摜�J�E���g

						while (1)
						{
							fscanf(pFile, "%s", aDataSearch);

							if (!strcmp(aDataSearch, "END_SIDE"))
							{// �ǂݍ��݂��I��

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
							{// �ʒu
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &pos.x);
								fscanf(pFile, "%f", &pos.y);
								fscanf(pFile, "%f", &pos.z);
							}
							else if (!strcmp(aDataSearch, "ROT"))
							{// ����
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &rot.x);
								fscanf(pFile, "%f", &rot.y);
								fscanf(pFile, "%f", &rot.z);
							}
							else if (!strcmp(aDataSearch, "COLOR"))
							{// �F
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &color.r);
								fscanf(pFile, "%f", &color.g);
								fscanf(pFile, "%f", &color.b);
								fscanf(pFile, "%f", &color.a);
							}
							else if (!strcmp(aDataSearch, "HEIGHT"))
							{// ����
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &fHeight);
							}
							else if (!strcmp(aDataSearch, "RADIUS"))
							{// ���a
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &fRadius);
							}
							else if (!strcmp(aDataSearch, "NUMTEX"))
							{// �摜��
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nNumTex);

								// �������̉��
								nType = new int[nNumTex];
								fTexV = new float[nNumTex];
							}
							else if (!strcmp(aDataSearch, "SET_TEX"))
							{// �摜�֘A�̐ݒ�

								while (1)
								{
									fscanf(pFile, "%s", aDataSearch);

									if (!strcmp(aDataSearch, "END_TEX"))
									{// �ǂݍ��݂��I��
										nCntTex++;
										break;
									}
									else if (!strcmp(aDataSearch, "TYPE"))
									{// ���a
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%d", &nType[nCntTex]);
									}
									else if (!strcmp(aDataSearch, "TEX_V"))
									{// �摜��
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%f", &fTexV[nCntTex]);
									}
								}
							}
							else if (!strcmp(aDataSearch, "DIVISION_X"))
							{// ������
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nDivisionX);
							}
							else if (!strcmp(aDataSearch, "DIVISION_Y"))
							{// ��������
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
// ��
//========================================
void CGame::LoodFloor(void)
{
	// �ϐ��錾
	char aDataSearch[128] = {};		// �������r�p�̕ϐ�
	char g_aEqual[128] = {};		// ���ǂݍ��ݗp�ϐ�

	// �t�@�C���|�C���^�̐錾
	FILE * pFile;

	//�t�@�C�����J��
	pFile = fopen(FLOOR_STAGE_FILE, "r");

	// �t�@�C�����J������
	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

	 // END_SCRIPT��������܂œǂݍ��݂��J��Ԃ�
		while (1)
		{
			fscanf(pFile, "%s", aDataSearch);	// ����

			if (!strcmp(aDataSearch, "END_SCRIPT"))
			{// �ǂݍ��݂��I��
				fclose(pFile);
				break;
			}
			else if (aDataSearch[0] == '#')
			{// �܂�Ԃ�
				continue;
			}
			else if (!strcmp(aDataSearch, "CREATE_FLOOR"))
			{// �����J�n

				while (1)
				{
					fscanf(pFile, "%s", aDataSearch);

					if (!strcmp(aDataSearch, "END_CREATE_FLOOR"))
					{// �����I��
						break;
					}
					else if (!strcmp(aDataSearch, "SET_FLOOR"))
					{// �������̓ǂݍ���
						D3DXVECTOR3 pos = INIT_D3DXVECTOR3;	// �ʒu
						D3DXVECTOR3 rot = INIT_D3DXVECTOR3;	// ����
						D3DXCOLOR	color = INIT_D3DXCOLOR;	// �F
						float fWidth = 0;					// ��
						float fHeight = 0;					// ����
						int *nType = 0;						// �摜���
						int nNumTex = 0;					// �摜��
						int nDivisionX = 1;					// ������
						int nDivisionY = 1;					// ��������
						bool bDivision = false;				// �e�N�X�`���̕������邩
						float *fTexX = 0;					// �e�N�X�`�����W�̊J�n�ʒu(X��)
						float *fTexY = 0;					// �e�N�X�`�����W�̊J�n�ʒu(Y��)


						int nCntTex = 0; // �摜�J�E���g

						while (1)
						{
							fscanf(pFile, "%s", aDataSearch);

							if (!strcmp(aDataSearch, "END_FLOOR"))
							{// �ǂݍ��݂��I��

								CFloor *pBgSide = CFloor::Create(
									pos, rot, color, fWidth,fHeight, nType, nNumTex, bDivision,
									nDivisionX, nDivisionY, fTexX, fTexY);

								break;
							}
							else if (!strcmp(aDataSearch, "POS"))
							{// �ʒu
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &pos.x);
								fscanf(pFile, "%f", &pos.y);
								fscanf(pFile, "%f", &pos.z);
							}
							else if (!strcmp(aDataSearch, "ROT"))
							{// ����
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &rot.x);
								fscanf(pFile, "%f", &rot.y);
								fscanf(pFile, "%f", &rot.z);
							}
							else if (!strcmp(aDataSearch, "COLOR"))
							{// �F
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &color.r);
								fscanf(pFile, "%f", &color.g);
								fscanf(pFile, "%f", &color.b);
								fscanf(pFile, "%f", &color.a);
							}
							else if (!strcmp(aDataSearch, "WIDTH"))
							{// ��
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &fWidth);
							}
							else if (!strcmp(aDataSearch, "HEIGHT"))
							{// ����
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%f", &fHeight);
							}
							else if (!strcmp(aDataSearch, "NUMTEX"))
							{// �摜��
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nNumTex);

								// �������̉��
								nType = new int[nNumTex];
								fTexX = new float[nNumTex];
								fTexY = new float[nNumTex];
							}
							else if (!strcmp(aDataSearch, "DIVISION"))
							{// �e�N�X�`���̕������邩
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
							{// �摜�֘A�̐ݒ�

								while (1)
								{
									fscanf(pFile, "%s", aDataSearch);

									if (!strcmp(aDataSearch, "END_TEX"))
									{// �ǂݍ��݂��I��
										nCntTex++;
										break;
									}
									else if (!strcmp(aDataSearch, "TYPE"))
									{// ���a
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%d", &nType[nCntTex]);
									}
									else if (!strcmp(aDataSearch, "TEX_X"))
									{// �e�N�X�`���̈ړ���(X��)
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%f", &fTexX[nCntTex]);
									}
									else if (!strcmp(aDataSearch, "TEX_Y"))
									{// �e�N�X�`���̈ړ���(Y��)
										fscanf(pFile, "%s", &g_aEqual[0]);
										fscanf(pFile, "%f", &fTexY[nCntTex]);
									}
								}
							}
							else if (!strcmp(aDataSearch, "DIVISION_X"))
							{// ������
								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nDivisionX);
							}
							else if (!strcmp(aDataSearch, "DIVISION_Y"))
							{// ��������
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
// �u���b�N
//========================================
void CGame::LoodBlock(void)
{
	CSVFILE *pFile = new CSVFILE;

	// �ǂݍ���
	pFile->FileLood(m_aStageInfo.aBlockFile[m_nStage], true, true, ',');

	// �s���̎擾
	int nRowMax = pFile->GetRowSize();

	// �e�f�[�^�ɑ��
	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		// �z�u���̐���
		int nType;				// ���
		int nState;				// ���
		D3DXVECTOR3 pos;		// �ʒu

		// �񐔂̎擾
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(nType, sData); break;	// ���
			case 1:	pFile->ToValue(pos.x, sData); break;	// �ʒu X
			case 2:	pFile->ToValue(pos.y, sData); break;	// �ʒu Y
			case 3:	pFile->ToValue(pos.z, sData); break;	// �ʒu Z
			case 4: pFile->ToValue(nState, sData); break;	// ���
			}
		}

		// �ő吔�ɒB������Ԃ�
		if (nRow == nRowMax - 1)	// (�� - ��̍ő吔 - �w�b�_�[�̗�)
		{
			return;
		}

		// �z�u
		CBlock *pObj = CBlock::Create(nType, pos,nState);
	}

	// �������J��
	delete pFile;
	pFile = NULL;
}

//========================================
// �G�l�~�[
//========================================
void CGame::LoodEnemy(void)
{
	CSVFILE *pFile = new CSVFILE;

	// �ǂݍ���
	pFile->FileLood(m_aStageInfo.aEnemyFile, true, true, ',');

	// �s���̎擾
	int nRowMax = pFile->GetRowSize();

	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		int nStage, nType, nMove, nTime;
		float fRotY;
		D3DXVECTOR3 pos;

		// �񐔂̎擾
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0: pFile->ToValue(nStage, sData); break;	// �X�e�[�W
			case 1:	pFile->ToValue(nType, sData); break;	// ���
			case 2:	pFile->ToValue(nMove, sData); break;	// �ړ����
			case 3:	pFile->ToValue(pos.x, sData); break;	// �ʒu X
			case 4:	pFile->ToValue(pos.y, sData); break;	// �ʒu Y
			case 5:	pFile->ToValue(pos.z, sData); break;	// �ʒu Z
			case 6: pFile->ToValue(fRotY, sData); break;	// ����Y
			case 7: pFile->ToValue(nTime, sData); break;	// �s���J�E���g
			}
		}

		// �ő吔�ɒB������Ԃ�
		if (nRow == nRowMax - 1)	// (�� - ��̍ő吔 - �w�b�_�[�̗�)
		{
			return;
		}

		if (nStage == m_nStage)
		{
			CEnemy *pObj = CEnemy::Create(nType, nMove, pos, D3DXVECTOR3(0.0f, fRotY, 0.0f), nTime);
		}
	}

	delete pFile;
	pFile = NULL;
}