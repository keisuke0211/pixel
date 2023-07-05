//========================================
// 
// �u���b�N����
// 
//========================================
// *** block.cpp ***
//========================================
#include "block.h"
#include "model.h"
#include "../../sound.h"
#include "../../csv_file.h"

//========================================
// �}�N����`
//========================================
#define RADIUS_TIME	(20)	// ���a�E���ڎ���
#define BULLET_ID	(2)		// �eID

// �ÓI�ϐ�
CBlock::SetInfo *CBlock::pSetInfo = NULL;

//========================================
// �R���X�g���N�^
//========================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority)
{
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.posOld = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.rotOld = INIT_D3DXVECTOR3;
	m_Info.size = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nType = 0;
	m_Info.nLife = 0;
	m_Info.nLifeMax = 0;
	m_Info.fRadius = 0.0f;
	m_Info.nCntRadius = 0;
	m_Info.fRadiusRate = 0.0f;
	m_Info.Width = 0.0f;
	m_Info.Height = 0.0f;
	m_Info.Depth = 0.0f;
	m_Info.bSet = false;
}

//========================================
// �f�X�g���N�^
//========================================
CBlock::~CBlock()
{

}

//========================================
// ����
//========================================
CBlock *CBlock::Create(int nType,D3DXVECTOR3 pos)
{
	CBlock *pBlock = NULL;

	if (pBlock != NULL)
	{
		return pBlock;
	}

	// �I�u�W�F�N�g2D�̐���
	pBlock = new CBlock;

	if (nType == MODEL_BULLET)
	{
		pBlock->m_Info.nCntRadius = RADIUS_TIME;
		pBlock->m_Info.fRadiusRate = 0.0f;
		pBlock->m_Info.bSet = false;
	}
	else
	{
		pBlock->m_Info.bSet = false;
	}

	pBlock->SetModel(nType);

	// ����������
	pBlock->Init();

	pBlock->m_Info.nType = nType;
	pBlock->m_Info.nLife = 300;
	pBlock->m_Info.nLifeMax = 300;
	pBlock->BlockSetPos(pos);

	return pBlock;
}

//========================================
// ������
//========================================
HRESULT CBlock::Init(void)
{
	CObjectX::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_BLOCK);

	m_Info.pos = D3DXVECTOR3(0.0f, 10.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.size = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nType = 0;
	m_Info.fRadius = 1.0f;

	// ����
	SetPos(m_Info.pos);
	//SetRot(m_Info.rot);
	SetScale(m_Info.size);
	SetColor(m_Info.col);

	return S_OK;
}

//========================================
// �I��
//========================================
void CBlock::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================
// �X�V
//========================================
void CBlock::Update(void)
{
	// �ߋ��̈ʒu�E�����̍X�V
	m_Info.posOld = m_Info.pos;
	m_Info.rotOld = m_Info.rot;

	// ���a����
	if (m_Info.bSet == false && m_Info.nType == MODEL_BULLET)
	{
		m_Info.fRadiusRate = (float)m_Info.nCntRadius / (float)RADIUS_TIME;
		m_Info.fRadius = 1 * (1.0f - m_Info.fRadiusRate);

		if (--m_Info.nCntRadius <= 0)
		{
			m_Info.bSet = true;
		}
	}

	// ����
	if (--m_Info.nLife <= 0 && m_Info.bSet == true)
	{
		Uninit();
		return;
	}
	else if (m_Info.nLife <= RADIUS_TIME && m_Info.bSet == true)
	{
		m_Info.fRadius -= m_Info.fRadius / m_Info.nLife;
		m_Info.col.a *= ((float)m_Info.nLife / RADIUS_TIME);

		SetColor(m_Info.col);
	}

	// �T�C�Y�̍X�V
	m_Info.size = D3DXVECTOR3(m_Info.fRadius, m_Info.fRadius, m_Info.fRadius);

	SetPos(m_Info.pos);
	//SetRot(m_Info.rot);
	SetScale(m_Info.size);

	CObjectX::Update();
}

//========================================
// �`��
//========================================
void CBlock::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// �ǂݍ���
//========================================
void CBlock::Load(void)
{
	CSVFILE *pFile = new CSVFILE;

	// �ǂݍ���
	pFile->FileLood("data\\GAMEDATA\\BLOCK\\BLOCK_DATA.csv", true, true, ',');

	// �s���̎擾
	int nRowMax = pFile->GetRowSize();

	// ���I�m��
	pSetInfo = new SetInfo;

	SetInfo* keep = pSetInfo;

	for (int nRow = 0; nRow < nRowMax; nRow++)
	{
		// �񐔂̎擾
		int nLineMax = pFile->GetLineSize(nRow);

		for (int nLine = 0; nLine < nLineMax; nLine++)
		{
			string sData = pFile->GetData(nRow, nLine);

			switch (nLine)
			{
			case 0:	pFile->ToValue(pSetInfo->nType, sData); break;	// ���
			case 1:	pFile->ToValue(pSetInfo->pos.x, sData); break;	// �ʒu X
			case 2:	pFile->ToValue(pSetInfo->pos.y, sData); break;	// �ʒu Y
			case 3:	pFile->ToValue(pSetInfo->pos.z, sData); break;	// �ʒu Z
			}
		}
		pSetInfo++;
	}

	// �擪�ʒu�ɖ߂�
	pSetInfo = keep;

	// �z�u
	SetBlock(nRowMax - 1);

	delete pFile;
	pFile = NULL;
}

//========================================
// �j��
//========================================
void CBlock::UnLoad(void)
{
	if (pSetInfo != NULL)
	{
		delete[] pSetInfo;
		pSetInfo = NULL;
	}
}

//========================================
// �z�u
//========================================
void CBlock::SetBlock(int nNumSet)
{
	for (int nCntSet = 0; nCntSet < nNumSet; nCntSet++, pSetInfo++)
	{
		CBlock::Create(pSetInfo->nType,
			D3DXVECTOR3(
				pSetInfo->pos.x,
				pSetInfo->pos.y,
				pSetInfo->pos.z)/*,
			pSetInfo->rot*/);
	}
}