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
const char* CRanking::FILE_PATH = "data\\GAMEDATA\\TEXTURE\\TEXTURE_DATA.txt";

//========================================
// �R���X�g���N�^
//========================================
CRanking::CRanking()
{
	for (int nRank = 0; nRank < RANK_NUM; nRank++)
	{
		m_Info[nRank].nScore = 100 + (100 * nRank);
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
	// �\�[�g
	SortDesc();

	// �e�L�X�g����
	for (int nRank = 0; nRank < RANK_NUM; nRank++)
	{
		char aString[TXT_MAX];
		sprintf(aString, " %s %6d", GetRankText(nRank), m_Info[nRank].nScore);

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

}

//========================================
// �����o��
//========================================
void CRanking::Save(void)
{

}

//========================================
// �X�R�A�ݒ�
//========================================
void CRanking::SetScore(int nScore)
{
	int nUpdateRank = -1;	// �X�R�A���X�V��������

	// �X�R�A���~���Ƀ\�[�g����
	SortDesc();

	if (nScore > m_Info[RANK_NUM - 1].nScore)
	{// �ł��������l���}������l���傫��������
	 // �ł��������l�ɑ}������l��������
		m_Info[RANK_NUM - 1].nScore = nScore;

		// �X�R�A���X�V�������ʂ�������
		nUpdateRank = RANK_NUM - 1;
	}

	// �X�R�A���~���Ƀ\�[�g����
	SortDesc();
}

//========================================
// �\�[�g�~��
//========================================
void CRanking::SortDesc(void)
{
	int		nTemp;			// �ꎞ�I�ɒl���i�[


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

				//// ���O�����ւ���
				//sprintf(aNameTemp, "%s", m_Info[nCnt1].aName);
				//sprintf(m_Info[nCnt1].aName, "%s", m_Info[nCnt2].aName);
				//sprintf(m_Info[nCnt2].aName, "%s", aNameTemp);

				//if (bUpdateRank == false)
				//{// ���ʍX�V�t���O���U�̎��A
				// // ���ʍX�V�t���O��^�ɂ���
				//	bUpdateRank = true;

				//	// �X�R�A���X�V�������ʂ�������
				//	*nUpdateRank = nCnt1;
				//}
			}
		}
	}
}