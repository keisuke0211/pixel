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
CBlock *CBlock::Create(D3DXVECTOR3 pos)
{
	CBlock *pBlock = NULL;

	if (pBlock != NULL)
	{
		return pBlock;
	}

	// �I�u�W�F�N�g2D�̐���
	pBlock = new CBlock;

	pBlock->SetModel(0);

	// ����������
	pBlock->Init();

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
	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetScale(m_Info.size);
	SetColor(m_Info.col);

	CObjectX::Update();
}

//========================================
// �`��
//========================================
void CBlock::Draw(void)
{
	CObjectX::Draw();
}