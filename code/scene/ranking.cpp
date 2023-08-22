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

//========================================
// �R���X�g���N�^
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

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetTrigger(CJoypad::JOYKEY_A))
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
			case 0:	pFile->ToValue(*m_Info[nRow].aName, sData); break;	// ���O
			case 1:	pFile->ToValue(m_Info[nRow].nScore, sData);		break;	// �X�R�A
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
			case 0:	sData = *m_Info[nRow].aName; break;	// ���O
			case 1:	sData = pFile->CastCell(m_Info[nRow].nScore); break;	// �X�R�A
			}

			// �f�[�^�̒ǉ�
			pFile->SetCell(sData, nRow, nLine);
		}
	}

	// �����o��
	pFile->FileSave(FILE_PATH, ',');
}

//========================================
// �X�R�A�ݒ�
//========================================
int CRanking::SetScore(int nScore)
{
	int nUpdateRank = -1;	// �X�R�A���X�V��������

	// �X�R�A���~���Ƀ\�[�g����
	SortDesc(&nUpdateRank);

	if (nScore > m_Info[RANK_NUM - 1].nScore)
	{// �ł��������l���}������l���傫��������
	 // �ł��������l�ɑ}������l��������
		m_Info[RANK_NUM - 1].nScore = nScore;

		// �X�R�A���X�V�������ʂ�������
		nUpdateRank = RANK_NUM - 1;
	}

	// �X�R�A���~���Ƀ\�[�g����
	SortDesc(&nUpdateRank);

	// �X�R�A���X�V�������ʂ�Ԃ�
	return nUpdateRank;
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
			if (m_Info[nCnt2].nScore > m_Info[nCnt1].nScore)
			{// �v�f2���v�f1�̒l�������Ă������A
			 // �l�����ւ���
				nTemp = m_Info[nCnt1].nScore;
				m_Info[nCnt1].nScore = m_Info[nCnt2].nScore;
				m_Info[nCnt2].nScore = nTemp;

				// ���O�����ւ���
				sprintf(aNameTemp, "%s", *m_Info[nCnt1].aName);
				sprintf(*m_Info[nCnt1].aName, "%s", *m_Info[nCnt2].aName);
				sprintf(*m_Info[nCnt2].aName, "%s", aNameTemp);

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