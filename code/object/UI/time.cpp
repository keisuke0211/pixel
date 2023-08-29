//========================================
//
// �X�R�A����
//
//========================================
// *** score2D.cpp ***
//========================================
#include "time.h"
#include "../model/block.h"
#include "../../scene/game.h"
#include "../../scene/title.h"
#include "../../scene/pause.h"
#include "../../system/words/text.h"
#include "../../system/words/words.h"
#include "../../system/words/font.h"

//========================================
// �R���X�g���N�^
//========================================
CTime::CTime(int nPriority) : CText2D(nPriority)
{
	m_nTime = 0;			// �^�C��
	m_nCounter = 0;			// �J�E���^�[
	m_Digit = 0;			// ����
	m_bSetTime = false;		// �ݒ�t���O
	m_bUpdateTime = false;	// �X�V�t���O
	m_Time = NULL;
}

//========================================
// �f�X�g���N�^
//========================================
CTime::~CTime(void)
{

}

//========================================
// ��������
//========================================
CTime *CTime::Create(void)
{
	CTime *pTime = new CTime;

	 // ����������
	pTime->Init();

	return pTime;
}

//========================================
// ����������
//========================================
HRESULT CTime::Init(void)
{
	// ����������
	CText2D::Init();

	m_nTime = 0;	// �^�C��
	m_nCounter = 0;	// �J�E���^�[

	{// �X�R�A�𕶎���ɐݒ�
		char aString[TXT_MAX];
		sprintf(aString, "TIME:%d", m_nTime);
		SetString(aString);
	}

	// ��ސݒ�
	SetType(TYPE_TIME);

	return S_OK;
}

//========================================
// �I������
//========================================
void CTime::Uninit(void)
{
	// �I������
	CText2D::Uninit();
}

//========================================
// �X�V����
//========================================
void CTime::Update(void)
{
	bool bStart = CTitle::IsStart();
	
	if (bStart)
	{
		bool bPause = CPause::IsPause();
		bool bCameraExit = CBlock::IsExitCamera();

		if (!bPause && bCameraExit)
		{
			// �X�V����
			CText2D::Update();

			if (m_nTime > 0)
			{// �^�C����0�ȏ�̎��A

				// �J�E���^�[��0�ɂȂ������A
				m_nCounter = (m_nCounter + 1) % 60;
				if (m_nCounter == 0)
				{
					m_nTime--;			// �^�C�������Z
					SetTime(m_nTime);	// �^�C���ݒ�
				}
			}
		}

		if (m_bUpdateTime)
		{
			// �^�C���𕶎���ɐݒ�
			char aTime[TXT_MAX];
			int nNumSet = 0;

			sprintf(aTime, "%d", m_nTime);

			// �������擾
			m_Digit = strlen(aTime);

			for (int nTime = 0; nTime < m_Digit; nTime++)
			{
				if (m_Time->SetWords(&aTime[nTime], TIME_START_DEX + nTime, INIT_D3DXCOLOR))
				{
					nNumSet++;
				}
			}

			if (nNumSet == m_Digit)
			{
				m_bUpdateTime = false;
			}
		}
	}
}

//========================================
// �`�揈��
//========================================
void CTime::Draw(void)
{

}

//========================================
// �ݒ�
//========================================
void CTime::SetTime(int nTime)
{
	// ���Ԑݒ�
	if (!m_bSetTime)
	{
		// �^�C�����
		m_nTime = nTime;

		// �^�C���𕶎���ɐݒ�
		char aString[TXT_MAX];
		sprintf(aString, "TIME �F%d", m_nTime);

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

		m_Time = CText::Create(CText::BOX_NORMAL,
			D3DXVECTOR3(SCREEN_WIDTH - 290.0f, 21.0f, 0.0f),
			D3DXVECTOR2(0.0f, 0.0f),
			aString,
			CFont::FONT_BESTTEN,
			&pFont,false,&pShadow);

		m_bSetTime = true;
	}
	else
	{
		m_bUpdateTime = true;
	}
}