//========================================
// 
// �X�e�[�W�I��
// 
//========================================
// *** stage_menu.cpp ***
//========================================
#include "stage_menu.h"
#include "../../manager.h"
#include "../../system/renderer.h"
#include "../../system/texture.h"
#include "../../system/words/text.h"
#include "../../system/words/font.h"

//========================================
// �}�N����`
//========================================
#define POS_RANGE_WIDE	(3.5f)	// ����̊g�� (���݂̈ʒu > �ڕW�ʒu - RANGE_WIDE && ���݈ʒu < �ڕW�ʒu + RANGE_WIDE)
#define SIZE_RANGE_WIDE	(3.5f)	// ����̊g��(�T�C�Y�p)

//========================================
// �R���X�g���N�^
//========================================
CStage::CStage(int nPriority) : CObject2D(nPriority)
{
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.TargetPos = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nType = 0;
	m_Info.size = INIT_D3DXVECTOR2;
	m_Info.TargetSize = INIT_D3DXVECTOR2;
	m_Info.bMove = false;
}

//========================================
// �f�X�g���N�^
//========================================
CStage::~CStage()
{

}

//========================================
// ����
//========================================
CStage *CStage::Create(int nType, int nPlace)
{
	CStage *pStage = new CStage;

	pStage->m_Info.nType = nType;
	pStage->m_Info.nPlace = nPlace;
	pStage->m_Info.pos = pStage->m_Place[nPlace];

	if (nPlace == PLACE_CENTER)
	{
		pStage->m_Info.size = D3DXVECTOR2(300.0f, 300.0f);
		pStage->m_Info.TargetSize = D3DXVECTOR2(300.0f, 300.0f);
	}
	else
	{
		pStage->m_Info.size = D3DXVECTOR2(150.0f, 150.0f);
		pStage->m_Info.TargetSize = D3DXVECTOR2(150.0f, 150.0f);
	}

	pStage->Init();

	return pStage;
}

//========================================
// ������
//========================================
HRESULT CStage::Init(void)
{
	CObject2D::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_BG);

	// �ݒ�
	SetPos(m_Info.pos);
	SetSize(m_Info.size.x, m_Info.size.y);
	SetColar(INIT_D3DXCOLOR);


	switch (m_Info.nType)
	{
	case CGame::Stage_EASY:
		BindTexture(CTexture::TEX_STAGE_EASY);
		break;
	case CGame::Stage_NORMAL:
		BindTexture(CTexture::TEX_STAGE_NORMAL);
		break;
	case CGame::Stage_DIFFICULT:
		BindTexture(CTexture::TEX_STAGE_DIFFICULT);
		break;
	default:
		BindTexture(CTexture::TEX_SEA01);
		break;
	}

	return S_OK;
}

//========================================
// �I��
//========================================
void CStage::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================
// �X�V
//========================================
void CStage::Update(void)
{
	bool bPos = false;
	bool bSize = false;
	bool bTextPos = false;
	bool bTextSize = false;

	if (m_Info.bMove)
	{
		// �ʒu�̐���
		if (m_Info.nPlace == PLACE_LEFT_EDGE || m_Info.nPlace == PLACE_VACANT)
		{
			m_Info.pos = m_Info.TargetPos;
		}
		else
		{
			m_Info.pos.x += (m_Info.TargetPos.x - m_Info.pos.x) * 0.12f;
			m_Info.pos.y += (m_Info.TargetPos.y - m_Info.pos.y) * 0.12f;
		}

		// �T�C�Y�̐���
		m_Info.size.x += (m_Info.TargetSize.x - m_Info.size.x) * 0.12f;
		m_Info.size.y += (m_Info.TargetSize.y - m_Info.size.y) * 0.12f;

		// �ʒu�E�T�C�Y�̍Đݒ�
		SetPos(m_Info.pos);
		SetSize(m_Info.size.x, m_Info.size.y);

		// �͈͂ɓ�������ړ�����߂�
		if (m_Info.pos.x > m_Info.TargetPos.x - POS_RANGE_WIDE && m_Info.pos.x < m_Info.TargetPos.x + POS_RANGE_WIDE)
		{
			m_Info.pos = m_Info.TargetPos;
			bPos = true;
		}

		if ((m_Info.size.x > m_Info.TargetSize.x - SIZE_RANGE_WIDE && m_Info.size.x < m_Info.TargetSize.x + SIZE_RANGE_WIDE) &&
			(m_Info.size.y > m_Info.TargetSize.y - SIZE_RANGE_WIDE && m_Info.size.y < m_Info.TargetSize.y + SIZE_RANGE_WIDE))
		{
			m_Info.size = m_Info.TargetSize;
			bSize = true;
		}

		if (bPos && bSize)
		{
			m_Info.bMove = false;
		}
	}

	CObject2D::Update();
}

//========================================
// �`��
//========================================
void CStage::Draw(void)
{
	CObject2D::Draw();
}

//========================================
// �ʒu�ݒ�
//========================================
void CStage::SetStageInfo(int nType, int nPlace)
{
	if (!m_Info.bMove)
	{
		// �ʒu
		m_Info.nPlace += nPlace;
		IntLoopControl(&m_Info.nPlace, PLACE_MAX, 0);

		m_Info.TargetPos = m_Place[m_Info.nPlace];
		m_Info.bMove = true;

		// �摜
		m_Info.nType += nType;
		IntLoopControl(&m_Info.nType, CGame::Stage_MAX, 0);

		if (m_Info.nPlace == PLACE_CENTER)
		{
			m_Info.TargetSize = D3DXVECTOR2(300.0f, 300.0f);
		}
		else
		{
			m_Info.TargetSize = D3DXVECTOR2(150.0f, 150.0f);
		}

		switch (m_Info.nType)
		{
		case CGame::Stage_EASY:
			BindTexture(CTexture::TEX_STAGE_EASY);
			break;
		case CGame::Stage_NORMAL:
			BindTexture(CTexture::TEX_STAGE_NORMAL);
			break;
		case CGame::Stage_DIFFICULT:
			BindTexture(CTexture::TEX_STAGE_DIFFICULT);
			break;
		}
	}
}