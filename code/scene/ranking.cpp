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
int CRanking::m_nGameScore = 2000;
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
// �I��
//========================================
void CRanking::Uninit(void)
{
	// �����o������
	Save();

	CObject::ReleaseAll(CObject::TYPE_TEXT2D);
	CObject::ReleaseAll(CObject::TYPE_FONT);
}

//========================================
// �X�V
//========================================
void CRanking::Update(void)
{
	//++pUi->nCounterBlink %= (UI_RANKINGFRAME_00_BLINK_TIME * 2);	// �_�ŃJ�E���^�[�����Z����

	// -- �擾 -------------------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g

	// ���
	//State();

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
			case 0:	sData = *m_Ranking[nRow].aName; break;	// ���O
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
		m_Info.nCntChar = NAME_START_CHAR;
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
			CFont::FONT_DOTGOTHIC,
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

	// -- �擾 -------------------------------------------
	CKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CJoypad *pInputJoypad = CManager::GetInputJoypad();			// �W���C�p�b�g

	if (!m_Info.bNameInput)
	{
		// -- �����ؑ� ---------------------------------------------
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

		// -- ����E�폜 ---------------------------------------------
		if (pInputKeyboard->GetTrigger(DIK_BACKSPACE) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_B))
		{// �폜
			if (m_Info.nCntName > 0)
			{
				m_Info.nCntName--;

				// ���݂̃J�E���g�ȍ~�̕������󔒂ɂ���
				m_Ranking[m_Info.nUpdateRank].aName[m_Info.nCntName + 1] = '\0';

				// �����J�E���g��ݒ�
				m_Info.nCntChar = m_Ranking[m_Info.nUpdateRank].aName[m_Info.nCntName];
			}
			m_Info.bNameInput = true;

		}
		else if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_A))
		{// ����
			if (++m_Info.nCntName >= NAME_NUM)
			{// ���O���͂̃J�E���g�����Z�������ʁA�����L���O���̕������ɒB�������A
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

		// ���݂̃J�E���g�̕����𔽉f����
		m_Ranking[nRank].aName[m_Info.nCntName] = aWords;

		if (m_Text[nRank]->SetWords(&aWords, NAME_START_DEX + m_Info.nCntName))
		{
			m_Info.bNameInput = false;
		}
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