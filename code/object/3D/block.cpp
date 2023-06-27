//========================================
// 
// �u���b�N����
// 
//========================================
// *** block.cpp ***
//========================================
#include "block.h"
#include "../model.h"
#include "../../sound.h"
#include "../../csv_file.h"

#define BULLET_ID	(2)	// �eID

// �ÓI�ϐ�
CBlock::SetInfo *CBlock::pSetInfo = NULL;

//========================================
// �R���X�g���N�^
//========================================
CBlock::CBlock(int nPriority) : CObjectX(nPriority)
{
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.size = INIT_D3DXVECTOR3;
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nType = 0;
	m_Info.nLife = 0;
	m_Info.nLifeMax = 0;
	m_Info.Width = 0.0f;
	m_Info.Height = 0.0f;
	m_Info.Depth = 0.0f;
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

	if (nType == BULLET_ID)
	{
		pBlock->SetModel(2);
	}
	else
	{
		pBlock->SetModel(nType);
	}

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
	m_Info.size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Info.col = INIT_D3DXCOLOR;
	m_Info.nType = 0;

	// ����
	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
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

	// ����
	if (--m_Info.nLife <= 0 && m_Info.nType == BULLET_ID)
	{
		Uninit();
		return;
	}
	else
	{

	}

	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetScale(m_Info.size);
	SetColor(m_Info.col);
	//CObjectX::Update();
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
	CSVFILE<int> data;

	// �ǂݍ���
	data.csv_read("data\\GAMEDATA\\BLOCK\\BLOCK_DATA.csv", true, true, ',');

	// ���I�m��
	int nLineMax = data.cell.size() - 1;
	pSetInfo = new SetInfo[nLineMax];

	for (int nLine = 0; nLine < data.cell.size(); nLine++)
	{
		int nRowMax = data.cell.at(nLine).size();

		for (int nRow = 0; nRow < data.cell.at(nLine).size(); nRow++)
		{
			switch (nRow)
			{
				// ���
			case SET_TYPE:
			{
				pSetInfo[nLine].nType = data.cell.at(nLine).at(nRow);
			}
				break;

				// �ʒu
			case SET_POS:
			{
				pSetInfo[nLine].pos.x = (int)data.cell.at(nLine).at(nRow); nRow++;
				pSetInfo[nLine].pos.y = (int)data.cell.at(nLine).at(nRow); nRow++;
				pSetInfo[nLine].pos.z = (int)data.cell.at(nLine).at(nRow);
			}
				break;

				// �u���b�N��
			case SET_NUM:
			{
				pSetInfo[nLine].nNumX = data.cell.at(nLine).at(nRow); nRow++;
				pSetInfo[nLine].nNumY = data.cell.at(nLine).at(nRow); nRow++;
				pSetInfo[nLine].nNumZ = data.cell.at(nLine).at(nRow);
			}
				break;
			}
		}
	}

	// �z�u
	SetBlock(nLineMax);
}

//========================================
// �z�u
//========================================
void CBlock::SetBlock(int nNumSet)
{
	float fWidth = CModel::GetWidth(0);			// ��
	float fHeight = CModel::GetHeight(0);		// ����
	float fDepth = CModel::GetDepth(0);			// ���s��
	

	for (int nCntSet = 0; nCntSet < nNumSet; nCntSet++, pSetInfo++)
	{
		for (int nCntX = 0; nCntX < pSetInfo->nNumX; nCntX++)
		{
			for (int nCntY = 0; nCntY < pSetInfo->nNumY; nCntY++)
			{
				for (int nCntZ = 0; nCntZ < pSetInfo->nNumZ; nCntZ++)
				{
					CBlock::Create(pSetInfo->nType, 
						D3DXVECTOR3((
							pSetInfo->pos.x + (nCntX * (fWidth * 2))),
							pSetInfo->pos.y + (nCntY * (fHeight * 2)),
							pSetInfo->pos.z + (nCntZ * (fDepth * 2))));
				}
			}
		}
	}
}