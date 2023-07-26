//========================================
// 
// �e�L�X�g�\��
// 
//========================================
// *** text.cpp ***
//========================================
#include "text.h"
#include "../../system/texture.h"
#include "../../manager.h"
#include "../../system/renderer.h"

//========================================
// �R���X�g���N�^
//========================================
CText::CText(int nPriority) : CObject2D(nPriority)
{
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nDesapTimar = 0;
	m_Info.nDesapTimarMax = 0;
	m_Info.nTextSize = 0;
	m_Info.nAddTime = 0;
	m_Info.nAddCount = 0;
	m_Info.nAddLetter = 0;
	m_Info.nLetterPopCount = 0;
	m_Info.nLetterPopCountX = 0;
	m_Info.nNiCount = 0;
	m_Info.bRelease = false;
}

//========================================
// �f�X�g���N�^
//========================================
CText::~CText()
{

}

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
	for (int wordsCount = 0; wordsCount < m_Info.nTextSize; wordsCount++)
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
	if (++m_Info.nAddCount >= m_Info.nAddTime)
	{// �\�����鎞�Ԃ���������A

		if (m_Info.nAddLetter <= m_Info.nTextSize)
		{// �e�L�X�g�T�C�Y��������Ă���A

			m_Info.sText += m_Info.sALLText[m_Info.nAddLetter];
			string Text = m_Info.sText;

			if (Text != "")
			{// �󔒂���Ȃ�������A

				D3DXVECTOR3 pos = GetPos();

				if (CheckLeadByte(m_Info.sALLText[m_Info.nAddLetter]) &&
					m_Info.nAddLetter < m_Info.nTextSize)
				{// �V�t�gJS ���� �e�L�X�g�T�C�Y��������Ă���A

					m_Info.nAddLetter++;
					m_Info.sText += m_Info.sALLText[m_Info.nAddLetter];
					m_Info.nAddLetter++;

					m_Info.words[m_Info.nLetterPopCount] = CWords::Create(m_Info.sText.c_str(),
						D3DXVECTOR3(50.0f + ( 40 * (m_Info.nLetterPopCountX + 1)), pos.y + m_Info.nNiCount*50.0f, pos.z),
						D3DXVECTOR3(20.0f, 20.0f, 0.0f),
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
							D3DXVECTOR3(50.0f + (40 * (m_Info.nLetterPopCountX + 1)), pos.y + m_Info.nNiCount*50.0f, pos.z),
							D3DXVECTOR3(20.0f, 20.0f, 0.0f),
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
		}
		m_Info.sText = "";
		m_Info.nAddCount = 0;
	}

	// �폜�t���O���^�̎�
	if (m_Info.bRelease)
	{
		if (--m_Info.nDesapTimar <= 0)
		{
			Uninit();
			return;
		}

		//// �F�̐���
		//m_Info.col.a *= ((float)m_Info.nDesapTimar / m_Info.nDesapTimarMax);
		//CObject2D::SetColar(m_Info.col);
	}

	CObject2D::Update();
}

//========================================
// �`��
//========================================
void CText::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2D::Draw();

	// �V�K�[�x�l <= Z�o�b�t�@�[�x�l (�����ݒ�)
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ���e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//========================================
// ����
//========================================
CText *CText::Create(Box type, int EraseTime, int DispText, const char *Text)
{
	CText * pText = new CText;

	if (pText != NULL)
	{
		pText->Init();

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
		pText->SetPos(D3DXVECTOR3(640.0f, 500.0f, 0.0f));
		pText->SetSize(1280.0f, 100.0f);

		pText->EraseTime(EraseTime);
		pText->TextLetter(Text, DispText);
	}

	return pText;
}
//================================================================================
//--------------------------------------------------------------------------------
//*********************************** �ݒ菈�� ***********************************
//--------------------------------------------------------------------------------
//================================================================================

//========================================
// �����܂ł̎���
//========================================
void CText::EraseTime(int Time)
{
	m_Info.nDesapTimar = Time;
	m_Info.nDesapTimarMax = m_Info.nDesapTimar;
	m_Info.bRelease = true;
}

//========================================
// �\������܂ł̎���
//========================================
void CText::TextLetter(const char * Text, int SpeedText)
{
	m_Info.sALLText = Text;
	m_Info.nTextSize = m_Info.sALLText.size();
	m_Info.nAddCount = SpeedText;
	m_Info.nAddTime = m_Info.nAddCount;
	m_Info.nAddLetter = 0;
	m_Info.words = new CWords*[m_Info.nTextSize];

	for (int wordsCount = 0; wordsCount < m_Info.nTextSize; wordsCount++)
	{
		m_Info.words[wordsCount] = NULL;
	}

}

//=============================================
// 1�o�C�g�������V�t�gJIS���ǂ������肷��֐�
//=============================================
bool CText::CheckLeadByte(int nLetter)
{
	return (((nLetter & 0xffu) ^ 0x20u) - 0xa1) < 94u / 2;
}