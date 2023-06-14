//========================================
// 
// ������
// 
//========================================
// *** floor.cpp ***
//========================================
#include "floor.h"

//========================================
// �R���X�g���N�^
//========================================
CFloor::CFloor(int nPriority) : CObject3D(nPriority)
{
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.fHeight = INIT_FLOAT;
	m_Info.fWidth = INIT_FLOAT;
}

//========================================
// �f�X�g���N�^
//========================================
CFloor::~CFloor()
{

}

//========================================
// ����
//========================================
CFloor *CFloor::Create(void)
{
	CFloor *pFloor = NULL;

	if (pFloor != NULL)
	{
		return pFloor;
	}

	// �I�u�W�F�N�g2D�̐���
	pFloor = new CFloor;

	// ����������
	pFloor->Init();

	return pFloor;
}

//========================================
// ������
//========================================
HRESULT CFloor::Init(void)
{
	CObject3D::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_FLOOR);

	m_Info.pos = D3DXVECTOR3(0.0f,60.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f, 3.141592f);
	m_Info.fWidth = 250.0f;
	m_Info.fHeight = 250.0f;

	// ����
	SetPos(m_Info.pos);
	SetRot(m_Info.rot);
	SetSize(m_Info.fWidth, m_Info.fHeight);
	SetColor(INIT_D3DXCOLOR);

	// �e�N�X�`���̊��蓖��
	BindTexture(10);

	return S_OK;
}

//========================================
// �I��
//========================================
void CFloor::Uninit(void)
{
	CObject3D::Uninit();
}

//========================================
// �X�V
//========================================
void CFloor::Update(void)
{	
	CObject3D::Update();
}

//========================================
// �`��
//========================================
void CFloor::Draw(void)
{
	CObject3D::Draw();
}
