//========================================
//
// �X�R�A����
//
//========================================
// *** score2D.cpp ***
//========================================
#include "score.h"
#include "../../system/words/text.h"
#include "../../system/words/words.h"
#include "../../system/words/font.h"

// �ÓI�����o�ϐ���`
int CScore::m_nScore = 0;	// �X�R�A
bool CScore::m_bUpdateText = false;	// �X�V�t���O

//========================================
// �R���X�g���N�^
//========================================
CScore::CScore(int nPriority) : CText2D(nPriority)
{
	m_Score = NULL;
	m_bUpdateText = false;
	m_Digit = 0;
}

//========================================
// �f�X�g���N�^
//========================================
CScore::~CScore(void) 
{

}

//========================================
// ��������
//========================================
CScore *CScore::Create(void)
{
	CScore *pScore = NULL;

	// �X�R�A�̐���
	pScore = new CScore;

	// ����������
	pScore->Init();

	return pScore;
}

//========================================
// ����������
//========================================
HRESULT CScore::Init(void)
{
	// ����������
	CText2D::Init();

	{// �X�R�A�𕶎���ɐݒ�
		char aString[TXT_MAX];
		sprintf(aString, "SCORE�F%06d", m_nScore);

		FormFont pFont = {
			INIT_D3DXCOLOR,
			11.0f,
			1,
			10,
			-1
		};

		FormShadow pShadow = {
			D3DXCOLOR(0.0f,0.0f,0.0f,1.0f),
			true,
			D3DXVECTOR3(2.0f,2.0f,0.0f),
			D3DXVECTOR2(1.0f,1.0f)
		};

		m_Score = CText::Create(CText::BOX_NORMAL,
			D3DXVECTOR3(SCREEN_WIDTH - 290.0f, 42.0f, 0.0f),
			D3DXVECTOR2(0.0f, 0.0f),
			aString,
			CFont::FONT_BESTTEN,
			&pFont, false, &pShadow);
	}

	// ��ސݒ�
	SetType(TYPE_SCORE);

	return S_OK;
}

//========================================
// �I������
//========================================
void CScore::Uninit(void)
{
	// �I������
	CText2D::Uninit();
}

//========================================
// �X�V����
//========================================
void CScore::Update(void)
{
	if (m_bUpdateText)
	{
		int nNumSet = 0;
		char aString[TXT_MAX];
		sprintf(aString, "%06d", m_nScore);

		// �������擾
		m_Digit = strlen(aString);

		for (int nTime = 0; nTime < m_Digit; nTime++)
		{
			if (m_Score->SetWords(&aString[nTime], SCORE_START_DEX + nTime, INIT_D3DXCOLOR))
			{
				nNumSet++;
			}
		}

		if (nNumSet == m_Digit)
		{
			m_bUpdateText = false;
		}
	}
}

//========================================
// �`�揈��
//========================================
void CScore::Draw(void)
{
	// �`�揈��
	CText2D::Draw();
}

//========================================
// �ݒ�
//========================================
void CScore::SetScore(int nScore)
{
	m_nScore += nScore;

	if (!m_bUpdateText)
	{
		m_bUpdateText = true;
	}
}