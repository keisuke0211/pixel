//========================================
//
// �p�[�e�B�N���y 2D �z
//
//========================================
// *** particle2D.cpp ***
//========================================
#include "particle2D.h"
#include "effect2D.h"

// �R���X�g���N�^
CParticle2D::CParticle2D(int nPriority) : CObject(nPriority)
{
	// �l���N���A
	m_fMove = 0.0f;
	m_nLife = 0;
	m_nLifeMax = 0;
	m_pos = INIT_D3DXVECTOR3;
	m_rot = INIT_D3DXVECTOR3;
}

// �f�X�g���N�^
CParticle2D::~CParticle2D()
{

}

//========================================
// ����
//========================================
CParticle2D *CParticle2D::Create(void)
{
	// �p�[�e�B�N��2D
	CParticle2D *pParticle2D = NULL;

	// �p�[�e�B�N��2D�̐���
	pParticle2D = new CParticle2D;

	// ����������
	pParticle2D->Init();

	return pParticle2D;
}
//========================================
// ������
//========================================
HRESULT CParticle2D::Init(void)
{
	// ��ސݒ�
	SetType(TYPE_PARTICLE);

	return S_OK;
}

//========================================
// �I��
//========================================
void CParticle2D::Uninit(void)
{
	Release();
}

//========================================
// �X�V
//========================================
void CParticle2D::Update(void)
{
	if (--m_nLife <= 0)
	{// �������s�������A
		Uninit();		// �I������
		return;
	}

	// �G�t�F�N�g�ݒ�
	SetEffect();

	// �ʒu�X�V
	float fRate = (float)m_nLife / m_nLifeMax;
	m_pos.x += sinf(m_rot.z) * m_fMove * fRate;
	m_pos.y += cosf(m_rot.z) * m_fMove * fRate;
}

//========================================
// �`��
//========================================
void CParticle2D::Draw(void)
{

}

//========================================
// �G�t�F�N�g����
//========================================
void CParticle2D::SetEffect(void)
{
	// �G�t�F�N�g2D����
	CEffect2D *pObj = CEffect2D::Create();

	// �ʒu�ݒ�
	pObj->SetPos(m_pos);

	// �����ݒ�
	pObj->SetRot(m_rot);

	// �ʒu�X�V
	float fRate = (float)m_nLife / m_nLifeMax;

	// �T�C�Y�ݒ�
	pObj->SetSize(8.0f, 8.0f);

	// �F
	pObj->SetColor(D3DXCOLOR(0.1f, 0.5f, 1.0f, 1.0f));

	// �����ݒ�
	pObj->SetLife(8);
}
