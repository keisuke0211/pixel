//========================================
// 
// �����L���O
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

// ��`
const char* CRanking::FILE_PATH = "data\\SAVEDATA\\RANKING_DATA.csv";
const char* CRanking::TEXT_FILE_PATH = "data\\GAMEDATA\\TEXT\\WORDS_DATA.txt";
int CRanking::m_nGameScore = 1100;
bool CRanking::m_bSetScore = true;

//========================================
// �R���X�g���N�^
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
	m_Info.nCntChar = 0;

	m_Info.nCntString = 0;
	m_Info.nCntLetter = 0;
	m_pString = NULL;
	nStringMax = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CRanking::~CRanking()
{

}

//========================================
// ������
//========================================
HRESULT CRanking::Init(void)
{
	int nUpdateRank = -1;	// �X�R�A���X�V��������

	// �ǂݍ���
	Load();
	WordsLoad();

	// �\�[�g
	SortDesc(&nUpdateRank);

	// �e�L�X�g����
	for (int nRank = 0; nRank < RANK_NUM; nRank++)
	{
		char aString[TXT_MAX];
		sprintf(aString, " %s %-5s %6d", GetRankText(nRank), m_Ranking[nRank].aName,m_Ranking[nRank].nScore);

		m_Text[nRank] = CText::Create(CText::BOX_NORMAL,
			D3DXVECTOR3(640.0f, 200 + ( 30 * nRank), 0.0f),
			D3DXVECTOR2(1080.0f, 100.0f),
			aString,
			CFont::FONT_BESTTEN,
			20.0f,
			5, 1, -1,false);
	}


	if (m_bSetScore)
	{
		SetNameEntry(SetScore(m_nGameScore));
	}

	return S_OK;
}

//========================================
// �I��
//========================================
void CRanking::Uninit(void)
{
	// �����o������
	Save();

	delete[] m_pString;
	m_pString = NULL;

	CObject::ReleaseAll(CObject::TYPE_TEXT2D);
	CObject::ReleaseAll(CObject::TYPE_FONT);
}

//========================================
// �X�V
//========================================
void CRanking::Update(void)
{
	// -- �擾 -------------------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g

	// ���
	State();

	// ���O����
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
// �`��
//========================================
void CRanking::Draw(void)
{

}

//========================================
// ����
//========================================
CRanking *CRanking::Create(void)
{
	CRanking *pRanking = new CRanking;

	pRanking->Init();

	return pRanking;
}

//========================================
// �ǂݍ���
//========================================
void CRanking::Load(void)
{
	CSVFILE *pFile = new CSVFILE;

	pFile->FileLood(FILE_PATH, true, true, ',');

	// �s���̎擾
	int nRowMax = pFile->GetRowSize();

	for (int nRow = 0; nRow < nRowMax; nRow++)
	{

		// �񐔂̎擾
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
				break;	// ���O
			case 1:	pFile->ToValue(m_Ranking[nRow].nScore, sData);		break;	// �X�R�A
			}
		}

		// �ő吔�ɒB������Ԃ�
		if (nRow == nRowMax - 1)	// (�� - ��̍ő吔 - �w�b�_�[�̗�)
		{
			return;
		}
	}

	delete pFile;
	pFile = NULL;
}

//========================================
// �����o��
//========================================
void CRanking::Save(void)
{
	CSVFILE *pFile = new CSVFILE;

	// �w�b�_�[�̐ݒ�
	pFile->SetHeader("���O,�X�R�A,", ',');

	// �f�[�^�̐ݒ�
	for (int nRow = 0; nRow < RANK_NUM; nRow++)
	{
		// �C���f�b�N�X�̐ݒ�
		pFile->SetIndex(GetRankText(nRow), ',');

		for (int nLine = 0; nLine < 2; nLine++)
		{
			string sData;	// ������̊i�[����ϐ�

			// ������ɕϊ�
			switch (nLine)
			{
			case 0:	sData = m_Ranking[nRow].aName; break;	// ���O
			case 1:	sData = pFile->CastCell(m_Ranking[nRow].nScore); break;	// �X�R�A
			}

			// �f�[�^�̒ǉ�
			pFile->SetCell(sData, nRow, nLine);
		}
	}

	// �����o��
	pFile->FileSave(FILE_PATH, ',');
}

//========================================
// ��ԏ���
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
// �X�R�A�ݒ�
//========================================
int CRanking::SetScore(int nScore)
{
	int nUpdateRank = -1;	// �X�R�A���X�V��������

	// �X�R�A���~���Ƀ\�[�g����
	SortDesc(&nUpdateRank);

	if (nScore > m_Ranking[RANK_NUM - 1].nScore)
	{// �ł��������l���}������l���傫��������
	 // �ł��������l�ɑ}������l��������
		m_Ranking[RANK_NUM - 1].nScore = nScore;

		// �X�R�A���X�V�������ʂ�������
		nUpdateRank = RANK_NUM - 1;
	}

	// �X�R�A���~���Ƀ\�[�g����
	SortDesc(&nUpdateRank);

	// �X�R�A���X�V�������ʂ�Ԃ�
	return nUpdateRank;
}

//========================================
// �X�R�A�ݒ�
//========================================
void CRanking::SetScore11(int nScore)
{
	m_nGameScore = nScore;
	m_bSetScore = true;
}

//========================================
// ���O���͐ݒ�
//========================================
void CRanking::SetNameEntry(int nUpdateRank)
{
	m_Info.nUpdateRank = nUpdateRank;

	if (m_Info.nUpdateRank != -1)
	{// �X�V���ʂ�-1(�X�V����)�łȂ����A
		m_Info.bNameEntry = true;
		m_Info.nCntName = 0;
		m_Info.nCntBlink = 0;

		// �X�V�������ʂ̖��O��������
		strinit(m_Ranking[nUpdateRank].aName, TXT_MAX);

		char aString[TXT_MAX];
		sprintf(aString, " %s %-5s %6d", GetRankText(m_Info.nUpdateRank), m_Ranking[m_Info.nUpdateRank].aName, m_Ranking[m_Info.nUpdateRank].nScore);

		m_Text[m_Info.nUpdateRank]->Uninit();

		m_Text[m_Info.nUpdateRank] = CText::Create(CText::BOX_NORMAL,
			D3DXVECTOR3(640.0f, 200 + (30 * m_Info.nUpdateRank), 0.0f),
			D3DXVECTOR2(1080.0f, 100.0f),
			aString,
			CFont::FONT_BESTTEN,
			20.0f,
			1, 1, -1, false);
	}
	else
	{// �X�V������-1(�X�V����)�̎��A
		m_Info.bNameEntry = false;
	}
}

//========================================
// ���O����
//========================================
void CRanking::NameEntry(void)
{
	if (!m_Info.bNameEntry)
	{
		return;
	}
	if (!m_Info.bNameInput)
	{
		// ����
		NameInput();
	}
	
	if (m_Info.bNameInput)
	{
		int nString = m_Info.nCntString;
		int nLetter = m_Info.nCntLetter;
		int nConv = m_Info.nCntConv;
		int nRank = m_Info.nUpdateRank;

		if (m_Text[nRank]->SetWords(m_pString[nString].pConv[nConv].pLetter[nLetter].aConv, NAME_START_DEX + m_Info.nCntName))
		{
			m_Text[nRank]->SetTextColor(BLINK_COLOR);
			m_Info.bNameInput = false;
		}
	}
}

//========================================
// ���O����(����)
//========================================
void CRanking::NameInput(void)
{
	// -- �擾 -------------------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g

	// -- ������ؑ� ---------------------------------------------
	if (pInputKeyboard->GetRepeat(DIK_A) || pInputKeyboard->GetRepeat(DIK_LEFT) ||
		pInputJoypad->GetRepeat(CJoypad::JOYKEY_LEFT) || pInputJoypad->GetStick().aAngleRepeat[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_LEFT])
	{
		m_Info.nCntLetter--;
		m_Info.bNameInput = true;
	}
	else if (
		pInputKeyboard->GetRepeat(DIK_D) || pInputKeyboard->GetRepeat(DIK_RIGHT) ||
		pInputJoypad->GetRepeat(CJoypad::JOYKEY_RIGHT) || pInputJoypad->GetStick().aAngleRepeat[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_RIGHT])
	{
		m_Info.nCntLetter++;
		m_Info.bNameInput = true;
	}

	// -- �����ؑ� ---------------------------------------------
	if (pInputKeyboard->GetRepeat(DIK_S) || pInputKeyboard->GetRepeat(DIK_DOWN) ||
		pInputJoypad->GetRepeat(CJoypad::JOYKEY_DOWN) || pInputJoypad->GetStick().aAngleRepeat[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_DOWN])
	{
		m_Info.nCntLetter = 0;
		m_Info.nCntConv = 0;
		m_Info.nCntString++;
		m_Info.bNameInput = true;
	}
	else if (
		pInputKeyboard->GetRepeat(DIK_W) || pInputKeyboard->GetRepeat(DIK_UP) ||
		pInputJoypad->GetRepeat(CJoypad::JOYKEY_UP) || pInputJoypad->GetStick().aAngleRepeat[CJoypad::STICK_TYPE_LEFT][CJoypad::STICK_ANGLE_UP])
	{
		m_Info.nCntLetter = 0;
		m_Info.nCntConv = 0;
		m_Info.nCntString--;
		m_Info.bNameInput = true;
	}

	// -- �ϊ� ---------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_Q) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_X))
	{
		m_Info.nCntConv--;
		m_Info.bNameInput = true;
	}
	else if (pInputKeyboard->GetTrigger(DIK_E) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_Y))
	{
		m_Info.nCntConv++;
		m_Info.bNameInput = true;
	}

	// �J�E���g����
	{
		int nString = m_Info.nCntString;
		int nLetterMax = m_pString[nString].nLettreMax;
		int nConvMax = m_pString[nString].nConvMax;

		IntLoopControl(&m_Info.nCntString, nStringMax, 0);
		IntLoopControl(&m_Info.nCntLetter, nLetterMax, 0);
		IntLoopControl(&m_Info.nCntConv, nConvMax, 0);
	}

	// -- ����E�폜 ---------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_BACKSPACE) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_B))
	{// �폜
		if (m_Info.nCntName > 0)
		{
			int nRank = m_Info.nUpdateRank;
			char aWords = '\0';

			// ���݂̃J�E���g�̕����𔽉f����
			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				m_Ranking[nRank].aName[(m_Info.nCntChar - 1) - nCnt] = '\0';
			}

			if (m_Text[nRank]->SetWords(&aWords, NAME_START_DEX + m_Info.nCntName))
			{
				m_Info.bNameInput = false;
			}
			m_Info.nCntName--;

		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_A))
	{// ����

		int nString = m_Info.nCntString;
		int nLetter = m_Info.nCntLetter;
		int nConv = m_Info.nCntConv;
		int nRank = m_Info.nUpdateRank;

		// ���݂̃J�E���g�̕����𔽉f����
		strcat(m_Ranking[nRank].aName, m_pString[nString].pConv[0].pLetter[nLetter].aConv);

		m_Info.nCntChar += 2;

		if (++m_Info.nCntName >= NAME_NUM)
		{// ���O���͂̃J�E���g�����Z�������ʁA�����L���O���̕������ɒB�������A
			m_Info.bNameEntry = false;
			return;
		}
		m_Info.bNameInput = true;
	}
}

//========================================
// �\�[�g�~��
//========================================
void CRanking::SortDesc(int *nUpdateRank)
{
	int	 nTemp;					// �ꎞ�I�ɒl���i�[
	char aNameTemp[TXT_MAX];	// �ꎞ�I�ɒl���i�[
	bool bUpdateRank = false;	// ���ʍX�V�t���O

	for (int nCnt1 = 0; nCnt1 < RANK_NUM - 1; nCnt1++)
	{
		for (int nCnt2 = nCnt1 + 1; nCnt2 < RANK_NUM; nCnt2++)
		{
			if (m_Ranking[nCnt2].nScore > m_Ranking[nCnt1].nScore)
			{// �v�f2���v�f1�̒l�������Ă������A
			 // �l�����ւ���
				nTemp = m_Ranking[nCnt1].nScore;
				m_Ranking[nCnt1].nScore = m_Ranking[nCnt2].nScore;
				m_Ranking[nCnt2].nScore = nTemp;

				// ���O�����ւ���
				sprintf(aNameTemp, "%s", m_Ranking[nCnt1].aName);
				sprintf(m_Ranking[nCnt1].aName, "%s", m_Ranking[nCnt2].aName);
				sprintf(m_Ranking[nCnt2].aName, "%s", aNameTemp);

				if (bUpdateRank == false)
				{// ���ʍX�V�t���O���U�̎��A
				 // ���ʍX�V�t���O��^�ɂ���
					bUpdateRank = true;

					// �X�R�A���X�V�������ʂ�������
					*nUpdateRank = nCnt1;
				}
			}
		}
	}
}

//========================================
// �󔒖���
//========================================
void CRanking::strinit(char *pData, int nNum)
{
	for (int nCnt = 0; nCnt < nNum; nCnt++)
	{
		pData[nCnt] = '\0';
	}
}

//========================================
// �����ǂݍ���
//========================================
void CRanking::WordsLoad(void)
{
	// �ϐ��錾
	char aDataSearch[128] = {};		// �������r�p�̕ϐ�
	char g_aEqual[128] = {};		// ���ǂݍ��ݗp�ϐ�

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
			else if (!strcmp(aDataSearch, "NUM_ROW"))
			{// �s��
				fscanf(pFile, "%s", &g_aEqual[0]);
				fscanf(pFile, "%d", &nStringMax);

				// �������̉��
				m_pString = new String[nStringMax];
			}
			else if (!strcmp(aDataSearch, "SET_TEXT"))
			{// ������̓ǂݍ���

				int nCntString = 0;	// ��

				while (1)
				{
					fscanf(pFile, "%s", aDataSearch);	// ����

					if (!strcmp(aDataSearch, "END_TEXT"))
					{// �ǂݍ��݂��I��
						break;
					}
					else if (!strcmp(aDataSearch, "SET_ROW"))
					{// �����̓ǂݍ���
						while (1)
						{
							fscanf(pFile, "%s", aDataSearch);	// ����

							if (!strcmp(aDataSearch, "END_ROW"))
							{// �ǂݍ��݂��I��
								nCntString++;	// ����̉��Z
								break;
							}
							else if (!strcmp(aDataSearch, "NUM_CONV"))
							{// �ϊ����̓ǂݍ���

								int nConvMin = 1;
								int nConvMax = 0;

								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nConvMax);

								nConvMax = nConvMin + nConvMax;

								// �������̉��
								m_pString[nCntString].pConv = new Conv[nConvMax];

								m_pString[nCntString].nConvMax = nConvMax;
							}
							else if (!strcmp(aDataSearch, "NUM_WORDS"))
							{// �������̓ǂݍ���

								int nLettreMax = -1;

								fscanf(pFile, "%s", &g_aEqual[0]);
								fscanf(pFile, "%d", &nLettreMax);

								for (int nConv = 0; nConv < m_pString[nCntString].nConvMax; nConv++)
								{
									m_pString[nCntString].pConv[nConv].pLetter = new Letter[nLettreMax];
								}
								m_pString[nCntString].nLettreMax = nLettreMax;
							}
							else if (!strcmp(aDataSearch, "SET_WORDS"))
							{// �^�C�v�̓ǂݍ���
								int nCountLetter = 0;	// ������
								int nCountConv = 0;

								while (1)
								{
									fscanf(pFile, "%s", &aDataSearch[0]);	// ����

									if (!strcmp(aDataSearch, "END_WORDS"))
									{// �ǂݍ��݂��I��
										break;
									}
									else if (!strcmp(aDataSearch, "WOARDS")) 
									{// �����̓ǂݍ���
										char aString[TXT_MAX];	// ������i�[
										char *ptr;				// ���������̊i�[

										fscanf(pFile, "%s", &aString[0]);

										// �J���}����؂�ɕ�����𕪊�
										ptr = strtok(aString, ",");

										if (nCountLetter < m_pString[nCntString].nLettreMax)
										{
											sprintf(m_pString[nCntString].pConv[nCountConv].pLetter[nCountLetter].aConv, "%s", ptr);
											nCountLetter++;
										}

										while (ptr != NULL)
										{
											// strtok�֐��ɂ��ύX���ꂽNULL�̃|�C���^���擪
											ptr = strtok(NULL, ",");

											// ptr��NULL�̏ꍇ�G���[����������̂őΏ�
											if (ptr != NULL) 
											{
												if (nCountLetter < m_pString[nCntString].nLettreMax)
												{
													sprintf(m_pString[nCntString].pConv[nCountConv].pLetter[nCountLetter].aConv, "%s", ptr);
													nCountLetter++;
												}
											}
										}
										nCountConv++;
									}
									else if (!strcmp(aDataSearch, "CONV"))
									{// �����̓ǂݍ���
										nCountLetter = 0;	// ������
										char aString[TXT_MAX];	// ������i�[
										char *ptr;				// ���������̊i�[

										fscanf(pFile, "%s", &aString[0]);

										// �ő吔�����Ă���
										if (nCountConv >= m_pString[nCntString].nConvMax)
										{
											return;
										}

										// �J���}����؂�ɕ�����𕪊�
										ptr = strtok(aString, ",");

										if (nCountLetter < m_pString[nCntString].nLettreMax)
										{
											// �X�V�������ʂ̖��O��������
											sprintf(m_pString[nCntString].pConv[nCountConv].pLetter[nCountLetter].aConv, "%s", ptr);
											nCountLetter++;
										}

										while (ptr != NULL)
										{
											// strtok�֐��ɂ��ύX���ꂽNULL�̃|�C���^���擪
											ptr = strtok(NULL, ",");

											// ptr��NULL�̏ꍇ�G���[����������̂őΏ�
											if (ptr != NULL)
											{
												if (nCountLetter < m_pString[nCntString].nLettreMax)
												{
													sprintf(m_pString[nCntString].pConv[nCountConv].pLetter[nCountLetter].aConv, "%s", ptr);	
													nCountLetter++;
												}
											}
										}

										nCountConv++;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else
	{//�t�@�C�����J���Ȃ��ꍇ
		assert(false);

		// �������I������
		return;
	}

	//// �t�@�C�����J��
	//pFile = fopen("data\\GAMEDATA\\TEXT\\WORDS.txt", "w");

	//if (pFile != NULL)
	//{// �t�@�C�����J�����ꍇ
	//	for (int nLen = 0; nLen < m_Info.nStringMax; nLen++)
	//	{
	//		for (int nCnt = 0; nCnt < m_Info.aString[nLen].nLettreMax; nCnt++)
	//		{
	//			fprintf(pFile, "WORDS:%s\n", m_Info.aString[nLen].aLetter[nCnt].aLetter);
	//		}
	//	}
	//	// �t�@�C�������
	//	fclose(pFile);
	//}

	//for (int nLen = 0; nLen < m_Info.nStringMax; nLen++)
	//{
	//	for (int nCnt = 0; nCnt < m_Info.aString[nLen].nLettreMax; nCnt++)
	//	{
	//		CText::Create(CText::BOX_NORMAL,
	//			D3DXVECTOR3(640.0f + (60 * nLen), 200 + (30 * nCnt), 0.0f),
	//			D3DXVECTOR2(1080.0f, 100.0f),
	//			m_Info.aString[nLen].aLetter[nCnt].aLetter,
	//			CFont::FONT_DOTGOTHIC,
	//			20.0f,
	//			5, 1, -1, false);
	//	}
	//}
}