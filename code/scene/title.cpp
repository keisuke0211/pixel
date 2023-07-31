//========================================
// 
// �^�C�g��
// 
//========================================
// *** title.cpp ***
//========================================
#include "title.h"
#include "../object\model\model.h"
#include "../system/input.h"
#include "../object\UI\text2D.h"
#include "fade.h"
#include "../object/model/block.h"

#include "../system/words/text.h"
#include "../system/words/font.h"
#include "../system/words/words.h"

//========================================
// �}�N����`
//========================================
#define STAND_MAX	(20)
#define TEXT_TIME	(150)

//========================================
// �R���X�g���N�^
//========================================
CTitle::CTitle()
{
	m_nTextTime = 0;
	m_nStandTime = 0;

	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_bMove[nCnt] = false;
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
	CModel::InitModel();	// ���f��
	CBlock::Load();			// �u���b�N

	/*CText::Create(CText::BOX_NORMAL,
		D3DXVECTOR3(540.0f, 100.0f, 0.0f),
		D3DXVECTOR2(220.0f, 100.0f),
		"�s�N�p�Y",
		CFont::FONT_FZGONTA,
		40.0f,
		20, 10, -1, false);*/

	m_Words[0] = CWords::Create("�u", D3DXVECTOR3(440.0f, -60.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_FZGONTA);
	m_Words[1] = CWords::Create("��", D3DXVECTOR3(560.0f, -60.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_FZGONTA);
	m_Words[2] = CWords::Create("�p", D3DXVECTOR3(680.0f, -60.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_FZGONTA);
	m_Words[3] = CWords::Create("�Y", D3DXVECTOR3(800.0f, -60.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_FZGONTA);

	m_bMove[0] = true;

	CText::Create(CText::BOX_NORMAL,
		D3DXVECTOR3(640.0f, 600.0f, 0.0f),
		D3DXVECTOR2(1080.0f, 100.0f),
		" ",
		CFont::FONT_DOTGOTHIC,
		20.0f,
		1, 1, -1);

	CText::Create(CText::BOX_NORMAL,
		D3DXVECTOR3(640.0f, 600.0f, 0.0f),
		D3DXVECTOR2(1080.0f, 100.0f),
		"ENTER�������Ďn�߂Ă�!",
		CFont::FONT_DOTGOTHIC,
		20.0f,
		5, 10, -1);

	m_nTextTime = TEXT_TIME;
	m_nStandTime = STAND_MAX;

	return S_OK;
}

//========================================
// �I��
//========================================
void CTitle::Uninit(void)
{
	CObject::ReleaseAll(CObject::TYPE_TEXT2D);
	CObject::ReleaseAll(CObject::TYPE_FONT);
}

//========================================
// �X�V
//========================================
void CTitle::Update(void)
{
	// �^�C�g���A�j���[�V����
	for (int nCnt = 0; nCnt < 4; nCnt++)
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


	// ���͍Ñ��e�L�X�g
	if (--m_nTextTime <= 0)
	{
		m_nStandTime--;
		if (m_nStandTime == STAND_MAX)
		{
			CObject::Release(CObject::PRIO_TEXT, CObject::TYPE_FONT, 2);
		}
		if (m_nStandTime <= 0)
		{
			CText::Create(CText::BOX_NORMAL,
				D3DXVECTOR3(640.0f, 600.0f, 0.0f),
				D3DXVECTOR2(1080.0f, 100.0f),
				"ENTER�������Ďn�߂Ă�!",
				CFont::FONT_DOTGOTHIC,
				20.0f,
				5, 10, -1);

			m_nTextTime = TEXT_TIME;
			m_nStandTime = STAND_MAX;
		}
	}

	// --- �擾 ---------------------------------
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// �W���C�p�b�g

	if (pInputKeyboard->GetTrigger(DIK_RETURN) || pInputJoypad->GetJoypadTrigger(CInputJoypad::JOYKEY_A))
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			CManager::GetFade()->SetFade(MODE_GAME);
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