//========================================
// 
// �G�l�~�[����
// 
//========================================
// *** enemy.cpp ***
//========================================
#include "enemy.h"
#include "../../manager.h"
#include "../../renderer.h"
#include "../../sound.h"
#include "../object2D.h"
#include "../2D/score.h"
#include "../2D/particle2D.h"

// �ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CEnemy::m_pTexture[CEnemy::MAX_TEXTURE] = { NULL };
int CEnemy::m_nTexture = -1;

// �R���X�g���N�^
CEnemy::CEnemy(int nPriority) : CObject2D(nPriority)
{
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.fWidth = INIT_FLOAT;
	m_Info.fHeight = INIT_FLOAT;
	m_Info.nType = 0;
	m_Info.nLife = 0;
}

// �f�X�g���N�^
CEnemy::~CEnemy()
{

}

//========================================
// �e�N�X�`���̓ǂݍ���
//========================================
HRESULT CEnemy::Load(char *pPath)
{
	if (pPath != NULL)
	{
		m_nTexture++;	// �e�N�X�`�������Z

		// �f�o�C�X�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// �e�N�X�`���̓ǂݍ���
		if (FAILED(D3DXCreateTextureFromFile(pDevice, pPath, &m_pTexture[m_nTexture])))
		{
			m_pTexture[m_nTexture] = NULL;
		}
	}

	return S_OK;
}
//========================================
// �e�N�X�`���̔j��
//========================================
void CEnemy::Unload(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < m_nTexture; nCntTex++)
	{
		if (m_pTexture[nCntTex] != NULL)
		{
			m_pTexture[nCntTex]->Release();
			m_pTexture[nCntTex] = NULL;
		}
	}
}

//========================================
// ����
//========================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos)
{
	CEnemy *pEnemy = NULL;

	if (pEnemy != NULL)
	{
		return pEnemy;
	}

	// �I�u�W�F�N�g2D�̐���
	pEnemy = new CEnemy;

	pEnemy->m_Info.pos = pos;
	pEnemy->m_Info.nLife = 1;

	// ����������
	pEnemy->Init();

	return pEnemy;
}

//========================================
// ������
//========================================
HRESULT CEnemy::Init(void)
{
	CObject2D::Init();

	m_Info.fWidth = 50.0f;
	m_Info.fHeight = 50.0f;

	// ��ނ̐ݒ�
	SetType(TYPE_ENEMY);

	// ����
	SetPos(m_Info.pos);
	SetSize(m_Info.fWidth, m_Info.fHeight);
	SetRot(m_Info.rot);
	SetColor(INIT_D3DXCOLOR);

	// �e�N�X�`���̊��蓖��
	BindTexture(6);

	return S_OK;
}

//========================================
// �I��
//========================================
void CEnemy::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================
// �X�V
//========================================
void CEnemy::Update(void)
{
	CObject2D::Update();
}

//========================================
// �`��
//========================================
void CEnemy::Draw(void)
{
	/*CObject2D::Draw();*/
}

//========================================
// �q�b�g����
//========================================
void CEnemy::HitLife(int nDamage)
{
	CSound *pSound = CManager::GetSound();

	m_Info.nLife -= nDamage;

	if (m_Info.nLife >= 0)
	{
		for (int nCntPtcl = 0; nCntPtcl < 16; nCntPtcl++) 
		{
			// �G�t�F�N�g2D����
			CParticle2D *pObj = CParticle2D::Create();

			// �ʒu�ݒ�
			pObj->SetPos(GetPos());

			// �����ݒ�
			pObj->SetRot(D3DXVECTOR3(0.0f, 0.0f, ((float)rand() / RAND_MAX) * D3DX_PI * 2.0f));

			// �ړ��ʐݒ�
			pObj->SetMove(5.0f + (5.0f * ((float)rand() / RAND_MAX)));

			// �����ݒ�
			pObj->SetLife(8 + (rand() % 24));
		}

		// �G�̔j��
		Uninit();

		// �X�R�A�ݒ�
		CScore::SetScore(300);

		pSound->PlaySound(3);

		return;
	}
	else
	{
		pSound->PlaySound(2);
	}
}