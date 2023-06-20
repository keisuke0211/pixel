//========================================
// 
// ���[�V�������f������
// 
//========================================
// *** motion_model.cpp ***
//========================================
#include "motion.h"
#include "motion_model.h"
#include "../manager.h"
#include "../renderer.h"


//========================================
// �R���X�g���N�^
//========================================
CMotionModel::CMotionModel(int nPriority) : CObject(nPriority)
{
	m_pMotion = NULL;				// ���[�V�������
	m_mtxWorld = D3DXMATRIX();		// ���[���h�}�g���b�N�X
	m_pos = INIT_D3DXVECTOR3;		// �ʒu
	m_posOld = INIT_D3DXVECTOR3;	// �ߋ��ʒu
	m_rot = INIT_D3DXVECTOR3;		// ����
	m_size = INIT_D3DXVECTOR3;		// �傫��
}

//========================================
// �f�X�g���N�^
//========================================
CMotionModel::~CMotionModel()
{

}

//========================================
// ����
//========================================
CMotionModel * CMotionModel::Create()
{
	CMotionModel *pMotionModel = NULL;

	pMotionModel = new CMotionModel;


	// ���l�̏�����
	pMotionModel->Init();

	// �C���X�^���X��Ԃ�
	return pMotionModel;
}

//========================================
// ������
//========================================
HRESULT CMotionModel::Init()
{
	// �ϐ��̏�����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ߋ��ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// ����
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);				// �X�P�[��
	m_size = D3DXVECTOR3(1.0f, 1.0f, 1.0f);					// �����蔻��
	m_quat = { 0.0f,0.0f,0.0f,1.0f };
	SetIsColor(false);
	SetColor({ 1.0f,1.0f,1.0f,1.0f });					// �F
	D3DXVECTOR3 vecY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXQuaternionRotationAxis(&m_quat, &vecY, D3DX_PI);
	return S_OK;
}

//========================================
// �I��
//========================================
void CMotionModel::Uninit()
{
	if (m_pMotion != NULL)
	{// �I������
		m_pMotion->Uninit();

		// �������̉��
		delete m_pMotion;
		m_pMotion = NULL;
	}

	// �I�u�W�F�N�g�̉��
	Release();
}

//========================================
// �X�V
//========================================
void CMotionModel::Update()
{
	if (m_pMotion != NULL)
	{// ���[�V�����ԍ��̐ݒ�
		m_pMotion->Update();
	}
}

//========================================
// �`��
//========================================
void CMotionModel::Draw()
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	if (m_Stencil)
	{
		// �X�e���V���o�b�t�@ -> �L��
		pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

		// �X�e���V���o�b�t�@�Ɣ�r����Q�ƒl�ݒ� -> ref
		pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

		// �X�e���V���o�b�t�@�̒l�ɑ΂��Ẵ}�X�N�ݒ� -> 0xff(�S�Đ^)
		pDevice->SetRenderState(D3DRS_STENCILMASK, 0xff);

		// �X�e���V���e�X�g�̔�r���@ ->
		// �i�Q�ƒl >= �X�e���V���o�b�t�@�̎Q�ƒl�j�Ȃ獇�i
		pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_GREATEREQUAL);

		// �X�e���V���e�X�g�̌��ʂɑ΂��Ă̔��f�ݒ�
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);		// Z�ƃX�e���V������
		pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);			// Z�ƃX�e���V�����s
		pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);			// Z�̂ݎ��s
	}
	else
	{
		// �X�e���V���o�b�t�@ -> ����
		pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	}

	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxRotQuat, mtxScale;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);									// �s�񏉊����֐�

	// �N�H�[�^�j�I���̎g�p�����p���̐ݒ�
	D3DXMatrixRotationQuaternion(&mtxRotQuat, &m_quat);					// �N�I�[�^�j�I���ɂ��s���]

	D3DXMatrixScaling(&mtxScale, m_scale.y, m_scale.x, m_scale.z);		// �X�P�[���g�k�s��
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScale);			// �s��|���Z�֐� 

	// �����̔��f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);	// �s���]�֐�

	D3DXMatrixMultiply(&mtxRot, &mtxRot, &mtxRotQuat);					// �s��|���Z�֐� 
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);				// �s��|���Z�֐� 

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);		// �s��ړ��֐�
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);			// �s��|���Z�֐�

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	if (m_pMotion != NULL)
	{// �p�[�c�̕`��ݒ�
		m_pMotion->SetParts(m_mtxWorld, m_bcolor, m_color);
	}

	// �X�e���V���o�b�t�@ -> ����
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
}


//========================================
// ���[�V�����̐ݒ�
//========================================
void CMotionModel::SetMotion(const char * pName)
{
	if (m_pMotion != nullptr)
	{// �I������
		m_pMotion->Uninit();

		// �������̉��
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	// ���[�V�������
	m_pMotion = new CMotion(pName);
	assert(m_pMotion != nullptr);

	// ���[�V�����̏����ݒ�
	m_pMotion->SetMotion(0);

	// ���[�V�����ԍ��̐ݒ�
	m_pMotion->SetNumMotion(0);
}

//========================================
// �F�ݒ�
//========================================
void CMotionModel::ChangeColar(D3DXCOLOR color)
{
	SetColor(color);
	SetIsColor(true);
}