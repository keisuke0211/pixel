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
	m_nTime = 0;	// �^�C��
	m_nCounter = 0;	// �J�E���^�[
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

		if (!bPause || bCameraExit)
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
	}
}

//========================================
// �`�揈��
//========================================
void CTime::Draw(void)
{
	// �`�揈��
	CText2D::Draw();
}

//========================================
// �ݒ�
//========================================
void CTime::SetTime(int nTime)
{
	// �^�C�����
	m_nTime = nTime;

	// �^�C���𕶎���ɐݒ�
	char aString[TXT_MAX];
	sprintf(aString, "TIME :%d", m_nTime);
	SetString(aString);

	/*FormFont pFont = {
		INIT_D3DXCOLOR,
		11.0f,
		1,
		10,
		-1
	};

	FormShadow pShadow = {
		D3DXCOLOR(0.0f,0.0f,0.0f,1.0f),
		true,
		D3DXVECTOR3(1.0f,1.0f,0.0f),
		D3DXVECTOR2(1.0f,1.0f)
	};

	CText::Create(CText::BOX_NORMAL,
		D3DXVECTOR3(SCREEN_WIDTH - 760.0f, 32.0f, 0.0f),
		D3DXVECTOR2(55.0f, 10.0f),
		aString,
		CFont::FONT_BESTTEN,
		&pFont,false,&pShadow);*/
}