//========================================
// 
// �`���[�g���A��
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
#include "../object/BG/mesh_floor.h"
#include "../object\UI\text2D.h"
#include "../system/input.h"
#include "../system/words/text.h"
#include "../system/words/font.h"
#include "../system/camera.h"
#include "../scene/pause.h"
#include "fade.h"

// �ÓI�ϐ�
CTutorial::TEXT_INFO *CTutorial::m_TextInfo = NULL;	// �e�L�X�g���

// �T�E���h�̃f�[�^�t�@�C���̑��΃p�X
const char* CTutorial::FILE_PATH = "data\\GAMEDATA\\TEXT\\TUTORIAL_DATA.csv";

CPlayer *CTutorial::m_pPlayer = NULL;
CTime *CTutorial::m_pTime = NULL;
CScore *CTutorial::m_pScore = NULL;

const char* CTutorial::CEILING_FILE = "data\\GAMEDATA\\OBJECT\\CEILING_MULTI_DATA.txt";
const char* CTutorial::SIDE_FILE = "data\\GAMEDATA\\OBJECT\\SIDE_MULTI_DATA.txt";
const char* CTutorial::FLOOR_FILE = "data\\GAMEDATA\\OBJECT\\FLOOR_MULTI_DATA.txt";
const char* CTutorial::BLOCK_FILE1 = "data\\GAMEDATA\\BLOCK\\STAGE_DATA1.csv";
const char* CTutorial::ENEMY_FILE1 = "data\\GAMEDATA\\ENEMY\\STAGE_ENEMY1.csv";

//========================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//========================================
CTutorial::~CTutorial()
{

}

//========================================
// ������
//========================================
HRESULT CTutorial::Init(void)
{
	CTitle::SetStart(false);
	CTitle::SetExit(false);
	CTitle::SetClear(false);

	// �w�i(����)�̐���
	LoodSide();

	// �w�i(�V��)�̐���
	LoodCeiling();

	// ���̐���
	LoodFloor();

	// �u���b�N�̐���
	LoodBlock();

	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetMotion("data\\GAMEDATA\\MODEL\\Player\\PLAYER_DATA.txt");

	// �G�̐���
	LoodEnemy();

	{
		// �^�C������
		m_pTime = CTime::Create();

		// �T�C�Y�ݒ�
		m_pTime->SetSize(20.0f, 20.0f);

		// �ʒu�ݒ�
		m_pTime->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 260.0f, 32.0f, 0.0f));

		// �^�C���ݒ�
		m_pTime->SetTime(MAX_TIME);
	}

	{
		// �X�R�A����
		m_pScore = CScore::Create();

		// �T�C�Y�ݒ�
		m_pScore->SetSize(20.0f, 20.0f);

		// �ʒu�ݒ�
		m_pScore->SetPos(D3DXVECTOR3(SCREEN_WIDTH - 260.0f, 52.0f, 0.0f));

		// �X�R�A�ݒ�
		CScore::SetScore();
	}

	// �ǂݍ���
	TextLoad();

	// �e�L�X�g����
	TexCreate(m_nNumText);

	return S_OK;
}

//========================================
// �I��
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

	// �������J��
	delete m_TextInfo;
	m_TextInfo = NULL;
}

//========================================
// �X�V
//========================================
void CTutorial::Update(void)
{
	// -- �擾 -------------------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g

	// �|�[�Y
	if (pInputKeyboard->GetTrigger(DIK_P) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_START))
	{
		CPause::SetPause(true);
	}

	// �e�e�L�X�g�̏���
	TutorialTex();

	// �J�n�t���O
	{
		bool bStart = CTitle::IsStart();
		if (!bStart && --m_nStartTime <= 0)
		{
			CTitle::SetStart(true);
		}
	}

	// �G�l�~�[�̑S��
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
						15,
						10,
						30
					};

					CText::Create(CText::BOX_NORMAL,
						D3DXVECTOR3(640.0f, 300.0f, 0.0f),
						D3DXVECTOR2(440.0f, 100.0f),
						"Game Clear",
						CFont::FONT_BESTTEN,
						&pFont, false);

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

		// ���Ԑ؂�
		if (m_pTime->GetTime() <= 0)
		{
			CManager::GetFade()->SetFade(MODE_TITLE);
		}
	}
}

//========================================
// �`��
//========================================
void CTutorial::Draw(void)
{

}

//========================================
// ����
//========================================
CTutorial *CTutorial::Create(void)
{
	CTutorial *pTutorial = new CTutorial;

	pTutorial->Init();

	return pTutorial;
}

//========================================
// �ǂݍ���
//========================================
void CTutorial::TextLoad(void)
{
	CSVFILE *pFile = new CSVFILE;

	pFile->FileLood(FILE_PATH, true, true, ',');

	// �s���̎擾
	int nRowMax = pFile->GetRowSize();

	// �������m��
	m_TextInfo = new CTutorial::TEXT_INFO[nRowMax];
	m_nTextMax = nRowMax - 1;
	int nNumAll = 0;

	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		// ������
		TextInit(nRow);

		// �񐔂̎擾
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(m_TextInfo[nRow].nType, sData); break;		// ���
			case 1:	pFile->ToValue(m_TextInfo[nRow].pos.x, sData); break;		// �ʒu X
			case 2:	pFile->ToValue(m_TextInfo[nRow].pos.y, sData); break;		// �@�@ Y
			case 3:	pFile->ToValue(m_TextInfo[nRow].size.x, sData); break;		// �T�C�Y X
			case 4:	pFile->ToValue(m_TextInfo[nRow].size.y, sData); break;		// �@�@�@ Y
			case 5:	pFile->ToValue(m_TextInfo[nRow].nStartTime, sData); break;	// �\������
			case 6:	pFile->ToValue(m_TextInfo[nRow].nStandTime, sData); break;	// �ҋ@����
			case 7:	pFile->ToValue(m_TextInfo[nRow].nDisapTime, sData); break;	// �����鎞��
			case 8:	pFile->ToValue(m_TextInfo[nRow].bTextBok, sData); break;	// Box�\��
			case 9:	pFile->ToValue(m_TextInfo[nRow].nTextSize, sData); break;	// �e�L�X�g �T�C�Y
			case 10:pFile->ToValue(*m_TextInfo[nRow].ActionTex, sData); break;	// �e�L�X�g
			}
		}

		// �ő吔�ɒB������Ԃ�
		if (nRow == nRowMax - 1)	// (�� - ��̍ő吔 - �w�b�_�[�̗�)
		{
			return;
		}

		{
			nNumAll++;
			int nType = m_TextInfo[nRow].nType;
			m_nTypeMax[nType] = nNumAll;
		}
	}

	delete pFile;
	pFile = NULL;
}

//========================================
// �e�L�X�g���̏�����
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
// �e�L�X�g����
//========================================
void CTutorial::TexCreate(int nIdx)
{
	if (m_TextInfo[nIdx].nType == ACTION_CLEAR)
	{
		int nCntExit = CBlock::GetBlockExit();
		bool bExit = CBlock::IsExit();

		if (!bExit)
		{
			return;
		}
		else if (nCntExit >= 1)
		{
			return;
		}
	}

	if (m_TextInfo[nIdx].nType == m_nTextType && !m_TextInfo[nIdx].bCreate)
	{
		FormFont pFont = {
			INIT_D3DXCOLOR,
			m_TextInfo[nIdx].nTextSize,
			m_TextInfo[nIdx].nStartTime,
			m_TextInfo[nIdx].nStandTime,
			m_TextInfo[nIdx].nDisapTime
		};

		CText::Create(CText::BOX_NORMAL,
			m_TextInfo[nIdx].pos,
			m_TextInfo[nIdx].size,
			*m_TextInfo[nIdx].ActionTex,
			CFont::FONT_BESTTEN,
			&pFont,
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
// �`���[�g���A��
//========================================
void CTutorial::TutorialTex(void)
{
	// -- �擾 -------------------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g


	// �e�L�X�g�̐���
	if (--m_nTextCreate <= 0)
	{
		m_nTextCreate = 0;

		if (m_nNumText < m_nTextMax)
		{
			TexCreate(m_nNumText);
		}
	}

	switch (m_nTextType)
	{
	case ACTION_MOVE:// �ړ�
	{
		D3DXVECTOR3 move = m_pPlayer->GetPlayerMove();
		
		if (move.x <= -1.0f || move.x >= 1.0f)
		{
			if (m_nTextCreate <= 0 && m_nTypeMax[ACTION_MOVE] == m_nNumText)
			{
				CObject::ReleaseAll(CObject::TYPE_FONT);
				m_nTextType = ACTION_CAMERA;
			}
		}
	}
		break;
	case ACTION_CAMERA:	// ���_�ړ�
	{
		D3DXVECTOR3 move = CManager::GetCamera()->GetInfo().spin;

		if (move.y <= -0.01f || move.y >= 0.01f)
		{
			if (m_nTextCreate <= 0 && m_nTypeMax[ACTION_CAMERA] == m_nNumText)
			{
				CObject::ReleaseAll(CObject::TYPE_FONT);
				m_nTextType = ACTION_SHOT;
			}
		}
	}
		break;
	case ACTION_SHOT:	// ����
	{
		int nNumAll = CBullet::GetNumAll();

		if (nNumAll >= 3 && m_nTypeMax[ACTION_SHOT] == m_nNumText)
		{
			CObject::ReleaseAll(CObject::TYPE_FONT);
			m_nTextType = ACTION_SET;
		}
	}
	break;
	case ACTION_SET:	// �z�u(��)
	{
		int nNumAll = CCube::GetNumAll();

		if (nNumAll >= 2 && m_nTypeMax[ACTION_SET] == m_nNumText)
		{
			CObject::ReleaseAll(CObject::TYPE_FONT);
			m_nTextType = ACTION_SET1;
		}
	}
	break;
	case ACTION_SET1:	// �z�u(�C��)
	{
		bool bSet = CPlayer::IsCubeSet();

		if (bSet && m_nTypeMax[ACTION_SET1] == m_nNumText)
		{
			CObject::ReleaseAll(CObject::TYPE_FONT);
			m_nTextType = ACTION_ENEMY;
		}
	}
	break;
	case ACTION_ENEMY:	// �G
	{
		int nNumEnemy = CEnemy::GetEnemyAll();

		if (nNumEnemy == 0 && m_nTypeMax[ACTION_ENEMY] == m_nNumText)
		{
			CObject::ReleaseAll(CObject::TYPE_FONT);
			m_nTextType = ACTION_CLEAR;
		}
	}
	break;
	case ACTION_CLEAR:	// �o��
	{
		if (m_nTextCreate <= 0 && m_nTypeMax[ACTION_CLEAR] == m_nNumText)
		{
			CObject::ReleaseAll(CObject::TYPE_FONT);
			m_nTextType = ACTION_FREE;
		}
	}
	break;
	case ACTION_FREE:	// ���R
	{
		if (m_nTextCreate <= 0 && m_nTypeMax[ACTION_FREE] == m_nNumText)
		{
			CObject::ReleaseAll(CObject::TYPE_FONT);
			m_nTextType = ACTION_MAX;
		}
	}
	}
}

//========================================
// �V��
//========================================
void CTutorial::LoodCeiling(void)
{
	CBgCeiling *pBgCeiling = CBgCeiling::Create();
}

//========================================
// ����
//========================================
void CTutorial::LoodSide(void)
{
	// �ϐ��錾
	char aDataSearch[128] = {};		// �������r�p�̕ϐ�
	char g_aEqual[128] = {};		// ���ǂݍ��ݗp�ϐ�

									// �t�@�C���|�C���^�̐錾
	FILE * pFile;

	//�t�@�C�����J��
	pFile = fopen(SIDE_FILE, "r");

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
									pos, rot, color, fHeight, fRadius, nType, nNumTex,
									nDivisionX, nDivisionY, fTexV);

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
void CTutorial::LoodFloor(void)
{
	// �ϐ��錾
	char aDataSearch[128] = {};		// �������r�p�̕ϐ�
	char g_aEqual[128] = {};		// ���ǂݍ��ݗp�ϐ�

									// �t�@�C���|�C���^�̐錾
	FILE * pFile;

	//�t�@�C�����J��
	pFile = fopen(FLOOR_FILE, "r");

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
									pos, rot, color, fWidth, fHeight, nType, nNumTex, bDivision,
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
// �u���b�N�̓ǂݍ���
//========================================
void CTutorial::LoodBlock(void)
{
	CSVFILE *pFile = new CSVFILE;

	// �ǂݍ���
	pFile->FileLood("data\\GAMEDATA\\BLOCK\\STAGE_DATA1.csv", true, true, ',');

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
		CBlock *pObj = CBlock::Create(nType, pos, nState);
	}

	// �������J��
	delete pFile;
	pFile = NULL;
}

//========================================
// �G�l�~�[�̓ǂݍ���
//========================================
void CTutorial::LoodEnemy(void)
{
	CSVFILE *pFile = new CSVFILE;

	pFile->FileLood("data\\GAMEDATA\\ENEMY\\STAGE_ENEMY1.csv", true, true, ',');

	// �s���̎擾
	int nRowMax = pFile->GetRowSize();

	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		int nType, nMove;
		D3DXVECTOR3 pos;

		// �񐔂̎擾
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(nType, sData); break;	// ���
			case 1:	pFile->ToValue(nMove, sData); break;	// �ړ����
			case 2:	pFile->ToValue(pos.x, sData); break;	// �ʒu X
			case 3:	pFile->ToValue(pos.y, sData); break;	// �ʒu Y
			case 4:	pFile->ToValue(pos.z, sData); break;	// �ʒu Z
			}
		}

		// �ő吔�ɒB������Ԃ�
		if (nRow == nRowMax - 1)	// (�� - ��̍ő吔 - �w�b�_�[�̗�)
		{
			return;
		}

		CEnemy *pObj = CEnemy::Create(nType, nMove, pos);
	}

	delete pFile;
	pFile = NULL;
}