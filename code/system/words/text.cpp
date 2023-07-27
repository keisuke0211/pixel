//========================================
// 
// �e�L�X�g�\��
// 
//========================================
// *** text.cpp ***
//========================================
#include "text.h"
#include "../../object/object.h"
#include "../../system/texture.h"
#include "../../manager.h"
#include "../../system/renderer.h"

//========================================
// �R���X�g���N�^
//========================================
CText::CText(int nPriority) : CObject2D(nPriority)
{
	m_Info.col = INIT_D3DXCOLOR;

	m_Info.fTextSize = 0.0f;
	m_Info.nTextLength = 0;
	m_Info.nAppearTime = 0;
	m_Info.nAddCount = 0;
	m_Info.nAddLetter = 0;
	m_Info.nLetterPopCount = 0;
	m_Info.nLetterPopCountX = 0;
	m_Info.nNiCount = 0;

	m_Info.nStandTime = 0;
	m_Info.bStand = false;

	m_Info.nDisapTime = 0;
	m_Info.nDisapTimeMax = 0;
	m_Info.bRelease = false;
}

//========================================
// �f�X�g���N�^
//========================================
CText::~CText()
{

}

//================================================================================
//--------------------------------------------------------------------------------
//********************************** ���C������ **********************************
//--------------------------------------------------------------------------------
//================================================================================

//========================================
// ������
//========================================
HRESULT CText::Init()
{
	SetType(TYPE_FONT);
	CObject2D::Init();

	m_Info.sText = "";

	return S_OK;
}

//========================================
// �I��
//========================================
void CText::Uninit()
{
	// �����̍폜
	for (int wordsCount = 0; wordsCount < m_Info.nTextLength; wordsCount++)
	{
		if (m_Info.words[wordsCount] != NULL)
		{
			m_Info.words[wordsCount]->Uninit();
		}
	}
	delete[] m_Info.words;

	CObject2D::Uninit();
}

//========================================
// �X�V
//========================================
void CText::Update()
{

	// �e�L�X�g����
	if (!m_Info.bStand)
	{
		LetterForm();
	}

	// �ҋ@����
	StandTime();

	// �폜����
	DisapTime();
}

//========================================
// �`��
//========================================
void CText::Draw()
{
	CObject2D::Draw();
}

//========================================
// ����
//========================================
CText *CText::Create(Box type, D3DXVECTOR3 pos, D3DXVECTOR2 size, const char *Text, float TextSize, int AppearTime, int StandTime, int EraseTime, bool bTextBok)
{
	CText * pText = new CText;

	if (pText != NULL)
	{
		pText->Init();

		// -- ���b�Z�[�W�{�b�N�X ----------------

		// �e�N�X�`���ݒ�
		switch (type)
		{
		case CText::BOX_NORMAL:
			pText->BindTexture(CTexture::TYPE_TEXBOX);
			break;
		case CText::BOX_MAX:
			pText->BindTexture(-1);
			break;
		default:
			break;
		}
		pText->SetPos(pos);
		pText->SetSize(size.x, size.y);

		if (!bTextBok)
		{
			pText->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		}

		// -- �e�L�X�g -----------------------
		pText->SetTextSize(TextSize);
		pText->SetStandTime(StandTime);
		pText->EraseTime(EraseTime);
		pText->TextLetter(Text, AppearTime);
	}

	return pText;
}

//================================================================================
//--------------------------------------------------------------------------------
//********************************** ���̑����� **********************************
//--------------------------------------------------------------------------------
//================================================================================

//========================================
// ��������
//========================================
void CText::LetterForm(void)
{
	float fTxtSize = m_Info.fTextSize;

	if (++m_Info.nAddCount >= m_Info.nAppearTime)
	{// �\�����鎞�Ԃ���������A

		if (m_Info.nAddLetter <= m_Info.nTextLength)
		{// �e�L�X�g�T�C�Y��������Ă���A

			m_Info.sText += m_Info.sALLText[m_Info.nAddLetter];
			string Text = m_Info.sText;
			D3DXVECTOR3 pos = GetPos();

			pos.x = pos.x - (GetWidth() / 2);

			if (Text != "" && m_Info.nAddLetter < m_Info.nTextLength)
			{// �󔒂���Ȃ�������A && �e�L�X�g�T�C�Y��������Ă���A

				if (CheckLeadByte(m_Info.sALLText[m_Info.nAddLetter]))
				{// 1�o�C�g�������V�t�gJIS��������A

					m_Info.nAddLetter++;
					m_Info.sText += m_Info.sALLText[m_Info.nAddLetter];
					m_Info.nAddLetter++;

					m_Info.words[m_Info.nLetterPopCount] = CWords::Create(m_Info.sText.c_str(),
						D3DXVECTOR3((pos.x + 10.0f) + ((fTxtSize * 2) * (m_Info.nLetterPopCountX + 1)), pos.y + m_Info.nNiCount*40.0f, pos.z),
						D3DXVECTOR3(fTxtSize, fTxtSize, 0.0f),
						CFont::FONT_DOTGOTHIC);

					m_Info.nLetterPopCount++;
					m_Info.nLetterPopCountX++;
				}
				else
				{
					if (m_Info.sText != "\n")
					{// �I�[�����Ȃ�A

						m_Info.nAddLetter++;
						m_Info.words[m_Info.nLetterPopCount] = CWords::Create(m_Info.sText.c_str(),
							D3DXVECTOR3((pos.x + 10.0f) + ((fTxtSize * 2) * (m_Info.nLetterPopCountX + 1)), pos.y + m_Info.nNiCount*40.0f, pos.z),
							D3DXVECTOR3(fTxtSize, fTxtSize, 0.0f),
							CFont::FONT_DOTGOTHIC);

						m_Info.nLetterPopCount++;
						m_Info.nLetterPopCountX++;
					}
					else
					{
						m_Info.nLetterPopCountX = 0;
						m_Info.nAddLetter++;
						m_Info.nNiCount++;
					}
				}
			}
			else
			{
				m_Info.bStand = true;
			}
		}

		m_Info.sText = "";
		m_Info.nAddCount = 0;
	}
}

//========================================
// �ҋ@
//========================================
void CText::StandTime(void)
{
	if (m_Info.bStand && m_Info.nStandTime >= 1)
	{
		if (--m_Info.nStandTime <= 0)
		{
			if (m_Info.nDisapTimeMax >= 1)
			{
				m_Info.bRelease = true;
			}
		}
	}
}

//========================================
// �폜
//========================================
void CText::DisapTime(void)
{
	if (m_Info.bRelease)
	{
		if (--m_Info.nDisapTime <= 0)
		{
			Uninit();
			return;
		}

		// �F�̐���
		m_Info.col.a *= ((float)m_Info.nDisapTime / m_Info.nDisapTimeMax);

		// �����F�̐���
		for (int wordsCount = 0; wordsCount < m_Info.nTextLength; wordsCount++)
		{
			if (m_Info.words[wordsCount] != NULL)
			{
				m_Info.words[wordsCount]->SetColar(m_Info.col);
			}
		}
		CObject2D::SetColar(m_Info.col);
	}
	CObject2D::Update();
}

//================================================================================
//--------------------------------------------------------------------------------
//*********************************** �ݒ菈�� ***********************************
//--------------------------------------------------------------------------------
//================================================================================

//========================================
// �����T�C�Y
//========================================
void CText::SetTextSize(float TextSize)
{
	if (TextSize <= 1.0f)
	{
		TextSize = 1.0f;
	}
	m_Info.fTextSize = TextSize;
}

//========================================
// �ҋ@����
//========================================
void CText::SetStandTime(int StandTime)
{
	if (StandTime <= 0)
	{
		StandTime = 0;
	}
	m_Info.nStandTime = StandTime;
}

//========================================
// �����܂ł̎���
//========================================
void CText::EraseTime(int Time)
{
	if (Time <= 0)
	{
		Time = 0;
	}
	m_Info.nDisapTime = Time;
	m_Info.nDisapTimeMax = m_Info.nDisapTime;
}

//========================================
// �\������܂ł̎���
//========================================
void CText::TextLetter(const char * Text, int AppearTime)
{
	m_Info.sALLText = Text;
	m_Info.nTextLength = m_Info.sALLText.size();
	m_Info.nAddCount = AppearTime;
	m_Info.nAppearTime = m_Info.nAddCount;
	m_Info.nAddLetter = 0;
	m_Info.words = new CWords*[m_Info.nTextLength];

	for (int wordsCount = 0; wordsCount < m_Info.nTextLength; wordsCount++)
	{
		m_Info.words[wordsCount] = NULL;
	}

}

//========================================
// �폜�t���O
//========================================
void CText::Disap(bool bDisap)
{
	m_Info.bRelease = bDisap;
	EraseTime(60);
}

//=============================================
// 1�o�C�g�������V�t�gJIS���ǂ������肷��֐�
//=============================================
bool CText::CheckLeadByte(int nLetter)
{
	return (((nLetter & 0xffu) ^ 0x20u) - 0xa1) < 94u / 2;
}