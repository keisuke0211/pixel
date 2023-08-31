//========================================
// 
// �^�C�g��
// 
//========================================
// *** title.cpp ***
//========================================
#include "title.h"
#include "game.h"
#include "../object/UI/stage_menu.h"
#include "../object\model\model.h"
#include "../system/input.h"
#include "../object\UI\text2D.h"
#include "fade.h"
#include "../object/model/block.h"

#include "../system/words/text.h"
#include "../system/words/font.h"
#include "../system/words/words.h"

// ��`
const char* CTitle::TEXT_FILE_PATH = "data\\GAMEDATA\\TEXT\\TITLE_DATA.txt";

// �ÓI�ϐ�
bool CTitle::m_bStart = false;
bool CTitle::m_bClear = false;
bool CTitle::m_bExit = false;

//========================================
// �R���X�g���N�^
//========================================
CTitle::CTitle()
{
	m_nTextTime = 0;
	m_nStandTime = 0;

	m_nSelectMenu = 0;
	m_nSelectStage = 0;
	m_bStageText = false;
	m_bStageInput = false;
	Title = TITLE_OUTSET;

	for (int nCnt = 0; nCnt < WORDS_MAX; nCnt++)
	{
		m_Words[nCnt] = NULL;
		m_bMove[nCnt] = false;
	}

	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		m_Menu[nCnt] = NULL;
	}

	for (int nCnt = 0; nCnt < STAGE_MAX; nCnt++)
	{
		m_Stage[nCnt] = NULL;
	}

	for (int nCntText = 0; nCntText < CGame::Stage_MAX; nCntText++)
	{
		*m_aText[nCntText].aStageText = NULL;
		*m_aText[nCntText].aStageWords[0] = NULL;
		*m_aText[nCntText].aStageWords[1] = NULL;
	}
}

//========================================
// �f�X�g���N�^
//========================================
CTitle::~CTitle()
{

}

//========================================
// ������
//========================================
HRESULT CTitle::Init(void)
{
	m_bStart = false;
	m_bClear = false;
	m_bExit = false;
	m_bStageInput = false;

	CModel::InitModel();	// ���f��
	CBlock::Load();			// �u���b�N

	// �e�L�X�g�ǂݍ���
	TextLoad();

	m_Words[0] = CWords::Create("�u", D3DXVECTOR3(440.0f, -60.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_BESTTEN,INIT_D3DXCOLOR);
	m_Words[1] = CWords::Create("��", D3DXVECTOR3(560.0f, -60.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_BESTTEN,INIT_D3DXCOLOR);
	m_Words[2] = CWords::Create("�p", D3DXVECTOR3(680.0f, -60.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_BESTTEN,INIT_D3DXCOLOR);
	m_Words[3] = CWords::Create("�Y", D3DXVECTOR3(800.0f, -60.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_BESTTEN,INIT_D3DXCOLOR);

	m_bMove[0] = true;

	FormFont pFont = {
		INIT_D3DXCOLOR,
		20.0f,
		1,
		1,
		-1
	};
	m_Menu[0] = CText::Create(CText::BOX_NORMAL_RECT,
		D3DXVECTOR3(640.0f, 600.0f, 0.0f),
		D3DXVECTOR2(1080.0f, 100.0f),
		" ",
		CFont::FONT_BESTTEN,
		&pFont);

	pFont = {
		INIT_D3DXCOLOR,
		20.0f,
		5,
		10,
		-1
	};

	m_Menu[1] = CText::Create(CText::BOX_NORMAL_RECT,
		D3DXVECTOR3(640.0f, 600.0f, 0.0f),
		D3DXVECTOR2(1080.0f, 100.0f),
		"ENTER�������Ďn�߂Ă�!",
		CFont::FONT_BESTTEN,
		&pFont,false);

	m_nTextTime = TEXT_TIME;
	m_nStandTime = STAND_MAX;

	return S_OK;
}

//========================================
// �I��
//========================================
void CTitle::Uninit(void)
{
	CObject::ReleaseAll(CObject::TYPE_BG);
	CObject::ReleaseAll(CObject::TYPE_TEXT2D);
	CObject::ReleaseAll(CObject::TYPE_FONT);
}

//========================================
// �X�V
//========================================
void CTitle::Update(void)
{
	// �^�C�g���A�j���[�V����
	if (Title == TITLE_OUTSET)
	{
		TitleAnime();
	}
	else if (Title == TITLE_MENU)
	{
		Menu();
	}
	else if (Title == TITLE_STAGE)
	{
		SelectStage();
	}

	// --- �擾 ---------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_A))
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			switch (Title)
			{
			case TITLE_OUTSET:
			{
				TextClear(WORDS_MAX, 2, TITLE_MENU);

				// ���j���[����
				MenuCreate();
			}
				break;
			case TITLE_MENU:
			{
				switch (m_nSelectMenu)
				{
				case MENU_GAME:
					TextClear(1, MENU_MAX, TITLE_STAGE);
					StageCreate();
					break;
				case MENU_TUTORIAL:
					TextClear(1, MENU_MAX, TITLE_NEXT);
					CManager::GetFade()->SetFade(MODE_TUTORIAL);
					break;
				case MENU_RANKING:
					TextClear(1, MENU_MAX, TITLE_NEXT);
					CManager::GetFade()->SetFade(MODE_RANKING);
					break;
				case MENU_END:
					//�Q�[���̏I��
					PostQuitMessage(0);
					break;
				}
			}
				break;
			case TITLE_STAGE:
			{
				CManager::GetFade()->SetFade(MODE_GAME);
				CGame::SetStage(m_nSelectStage);
			}
				break;
			}
		}
		else if (CFade::GetFade() == CFade::FADE_IN)
		{

		}
	}
}

//========================================
// �`��
//========================================
void CTitle::Draw(void)
{

}

//========================================
// ����
//========================================
CTitle *CTitle::Create(void)
{
	CTitle *pTitle = new CTitle;

	pTitle->Init();

	return pTitle;
}

//========================================
// �^�C�g���A�j���[�V����
//========================================
void CTitle::TitleAnime(void)
{
	for (int nCnt = 0; nCnt < WORDS_MAX; nCnt++)
	{
		if (m_Words[nCnt] != NULL)
		{
			D3DXVECTOR3 pos = m_Words[nCnt]->GetPos();

			if (pos.y <= 110.0f && m_bMove[nCnt])
			{
				D3DXVECTOR3 move;

				move.y = 3.0f;

				m_Words[nCnt]->SetMove(D3DXVECTOR3(0.0f, move.y, 0.0f));

				if (pos.y >= 100.0f)
				{
					move.y = 0.0f;

					m_Words[nCnt]->SetMove(D3DXVECTOR3(0.0f, move.y, 0.0f));
				}
				else if (pos.y >= 20 && nCnt != 3 && !m_bMove[nCnt + 1])
				{
					m_bMove[nCnt + 1] = true;
				}
			}
		}
	}

	// ���͍Ñ��e�L�X�g
	if (--m_nTextTime <= 0)
	{
		if (m_nStandTime == STAND_MAX)
		{
			if (m_Menu[1] != NULL)
			{
				m_Menu[1]->Uninit();

				m_Menu[1] = NULL;
			}
		}
		m_nStandTime--;
		if (m_nStandTime <= 0)
		{
			FormFont pFont = {
				INIT_D3DXCOLOR,
				20.0f,
				5,
				10,
				-1
			};

			m_Menu[1] = CText::Create(CText::BOX_NORMAL_RECT,
				D3DXVECTOR3(640.0f, 600.0f, 0.0f),
				D3DXVECTOR2(1080.0f, 100.0f),
				"ENTER�������Ďn�߂Ă�!",
				CFont::FONT_BESTTEN,
				&pFont, false);

			m_nTextTime = TEXT_TIME;
			m_nStandTime = STAND_MAX;
		}
	}
}

//========================================
// ���j���[����
//========================================
void CTitle::MenuCreate(void)
{
	FormFont pFont = {
		INIT_D3DXCOLOR,
		20.0f,
		5,
		10,
		-1
	};

	{
		m_Menu[0] = CText::Create(CText::BOX_NORMAL_RECT,
			D3DXVECTOR3(640.0f, 150.0f, 0.0f),
			D3DXVECTOR2(360.0f, 100.0f),
			"�Q�[��",
			CFont::FONT_BESTTEN,
			&pFont);
	}

	{
		m_Menu[1] = CText::Create(CText::BOX_NORMAL_RECT,
			D3DXVECTOR3(640.0f, 300.0f, 0.0f),
			D3DXVECTOR2(360.0f, 100.0f),
			"�`���[�g���A��",
			CFont::FONT_BESTTEN,
			&pFont);
	}
	{
		m_Menu[2] = CText::Create(CText::BOX_NORMAL_RECT,
			D3DXVECTOR3(640.0f, 450.0f, 0.0f),
			D3DXVECTOR2(360.0f, 100.0f),
			"�����L���O",
			CFont::FONT_BESTTEN,
			&pFont);
	}
	{
		m_Menu[3] = CText::Create(CText::BOX_NORMAL_RECT,
			D3DXVECTOR3(640.0f, 600.0f, 0.0f),
			D3DXVECTOR2(360.0f, 100.0f),
			"�Q�[������߂�",
			CFont::FONT_BESTTEN,
			&pFont);
	}
}

//========================================
// ���j���[
//========================================
void CTitle::Menu(void)
{
	// �F
	for (int nCnt = 0; nCnt < MENU_MAX; nCnt++)
	{
		if (m_Menu[nCnt] != NULL)
		{
			if (nCnt == m_nSelectMenu)
			{
				m_Menu[nCnt]->SetBoxColor(D3DXCOLOR(0.0f,1.0f,0.0f,1.0f));
			}
			else
			{
				m_Menu[nCnt]->SetBoxColor(INIT_D3DXCOLOR);
			}
		}
	}


	// --- �擾 ---------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g

	// -- ���j���[�I�� ---------------------------
	if (pInputKeyboard->GetTrigger(DIK_W) || pInputKeyboard->GetTrigger(DIK_UP) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_UP) || pInputJoypad->GetStick(0).aAngleTrigger[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_UP])
	{
		m_nSelectMenu--;
	}
	else if (pInputKeyboard->GetTrigger(DIK_S) || pInputKeyboard->GetTrigger(DIK_DOWN) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_DOWN) || pInputJoypad->GetStick(0).aAngleTrigger[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_DOWN])
	{
		m_nSelectMenu++;
	}

	// ���[�v����
	IntLoopControl(&m_nSelectMenu, MENU_MAX, 0);
}

//========================================
// �X�e�[�W����
//========================================
void CTitle::StageCreate(void)
{
	// ����
	m_Stage[1] = CStage::Create(1, 0);	// ���[
	m_Stage[2] = CStage::Create(2, 1);	// ��
	m_Stage[0] = CStage::Create(0, 2);	// ����
	m_Stage[3] = CStage::Create(1, 3);	// �E
	m_Stage[4] = CStage::Create(2, 4);	// �E�[
	m_Stage[5] = CStage::Create(0, 5);	// ��

	{
		FormFont pFont = { INIT_D3DXCOLOR,25.0f,1,1,-1 };
		m_StageText[0] = CText::Create(CText::BOX_NORMAL_RECT, D3DXVECTOR3(550.0f, 560.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f),
			m_aText[0].aStageText, CFont::FONT_BESTTEN, &pFont, false);

		pFont = { INIT_D3DXCOLOR,20.0f,1,1,-1 };

		m_StageText[1] = CText::Create(CText::BOX_NORMAL_RECT, D3DXVECTOR3(990.0f, 485.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f),
			m_aText[1].aStageText, CFont::FONT_BESTTEN, &pFont, false);
		m_StageText[2] = CText::Create(CText::BOX_NORMAL_RECT, D3DXVECTOR3(145.0f, 485.0f, 0.0f), D3DXVECTOR2(0.0f, 0.0f),
			m_aText[2].aStageText, CFont::FONT_BESTTEN, &pFont, false);

		m_bStageText = true;// 145 990
	}
}

//========================================
// �X�e�[�W�I��
//========================================
void CTitle::SelectStage(void)
{
	int nSelect = 0;

	// --- �擾 ---------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g

	// -- �X�e�[�W�I�� ---------------------------
	if (!m_bStageInput)
	{
		if (pInputKeyboard->GetTrigger(DIK_A) || pInputKeyboard->GetTrigger(DIK_LEFT) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_LEFT) || pInputJoypad->GetStick(0).aAngleTrigger[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_LEFT])
		{
			nSelect = 1;
			m_nSelectStage--;
			m_bStageInput = true;
		}
		else if (pInputKeyboard->GetTrigger(DIK_D) || pInputKeyboard->GetTrigger(DIK_RIGHT) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_RIGHT) || pInputJoypad->GetStick(0).aAngleTrigger[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_RIGHT])
		{
			nSelect = -1;
			m_nSelectStage++;
			m_bStageInput = true;
		}
	}

	int nCntMove = 0;
	for (int nCnt = 0; nCnt < STAGE_MAX; nCnt++)
	{
		bool bMove = m_Stage[nCnt]->IsMove();

		if (!bMove)
		{
			nCntMove++;
		}
	}

	if (nCntMove == STAGE_MAX && !m_bStageText)
	{
		for (int nCntText = 0; nCntText < 3; nCntText++)
		{
			int nText;

			switch (nCntText)
			{
			case 0:
				nText = m_nSelectStage;
				break;
			case 1:
				nText = m_nSelectStage + 1;
				IntLoopControl(&nText, CGame::Stage_MAX, 0);
				break;
			case 2:
				nText = m_nSelectStage - 1;
				IntLoopControl(&nText, CGame::Stage_MAX, 0);
				break;
			}

			for (int nCntWorde = 0; nCntWorde < 2; nCntWorde++)
			{
				m_StageText[nCntText]->ChgWords(m_aText[nText].aStageWords[nCntWorde], nCntWorde, INIT_D3DXCOLOR);
			}
		}
		m_bStageText = true;
		m_bStageInput = false;
	}

	if (m_bStageInput && nCntMove == STAGE_MAX)
	{
		IntLoopControl(&m_nSelectStage, CGame::Stage_MAX, 0);

		// �X�e�[�W�̈ʒu�ݒ�
		for (int nCnt = 0; nCnt < STAGE_MAX; nCnt++)
		{
			m_Stage[nCnt]->SetStageInfo(0,nSelect);
		}

		if (m_bStageText)
		{
			for (int nCntText = 0; nCntText < 3; nCntText++)
			{
				for (int nCntWorde = 0; nCntWorde < 2; nCntWorde++)
				{
					m_StageText[nCntText]->SetTextColor(D3DXCOLOR(0.0f,0.0f,0.0f,0.0f));
				}
			}
			m_bStageText = false;
		}
	}
}

//========================================
// �e�L�X�g�폜
//========================================
void CTitle::TextClear(int nWords, int nText, TITLE aTitle)
{
	for (int nCnt = 0; nCnt < nWords; nCnt++)
	{
		if (m_Words[nCnt] != NULL)
		{
			m_Words[nCnt]->Uninit();
			m_Words[nCnt] = NULL;
		}
	}
	for (int nCnt = 0; nCnt < nText; nCnt++)
	{
		if (m_Menu[nCnt] != NULL)
		{
			m_Menu[nCnt]->Uninit();
			m_Menu[nCnt] = NULL;
		}
	}

	Title = aTitle;
}

//========================================
// �e�L�X�g�ǂݍ���
//========================================
void CTitle::TextLoad(void)
{
	// �ϐ��錾
	char aDataSearch[128] = {};		// �������r�p�̕ϐ�

									// �t�@�C���|�C���^�̐錾
	FILE * pFile;

	//�t�@�C�����J��
	pFile = fopen(TEXT_FILE_PATH, "r");

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
			else if (!strcmp(aDataSearch, "SET_STAGE_TEXT"))
			{// �X�e�[�W�e�L�X�g
				int nCntWoards = 0;

				while (1)
				{
					fscanf(pFile, "%s", aDataSearch);	// ����

					if (!strcmp(aDataSearch, "END_STAGE_TEXT"))
					{// �ǂݍ��݂��I��
						break;
					}
					else if (!strcmp(aDataSearch, "WOARDS"))
					{// �X�e�[�W�e�L�X�g

						int nCountLetter = 0;	// ������
						char aString[TXT_MAX];	// ������i�[
						char *ptr;				// ���������̊i�[

						fscanf(pFile, "%s", &aString[0]);

						// �J���}����؂�ɕ�����𕪊�
						ptr = strtok(aString, ",");

						if (nCountLetter < 2)
						{
							strcat(m_aText[nCntWoards].aStageText, ptr);
							sprintf(m_aText[nCntWoards].aStageWords[nCountLetter], "%s", ptr);
							nCountLetter++;
						}

						while (ptr != NULL)
						{
							// strtok�֐��ɂ��ύX���ꂽNULL�̃|�C���^���擪
							ptr = strtok(NULL, ",");

							// ptr��NULL�̏ꍇ�G���[����������̂őΏ�
							if (ptr != NULL)
							{
								if (nCountLetter < 2)
								{
									strcat(m_aText[nCntWoards].aStageText, ptr);
									sprintf(m_aText[nCntWoards].aStageWords[nCountLetter], "%s", ptr);
									nCountLetter++;
								}
							}
						}

						nCntWoards++;
					}
				}
			}

		}
	}
}