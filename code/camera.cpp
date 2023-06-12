//========================================
// 
// �J��������
// 
//========================================
// *** camera.cpp ***
//========================================
#include "camera.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

// �R���X�g���N�^
CCamera::CCamera()
{
	m_posR = INIT_D3DXVECTOR3;		// ���݂̎��_
	m_posV = INIT_D3DXVECTOR3;		// ���݂̒����_
	m_posOldR = INIT_D3DXVECTOR3;	// �O��̎��_R3;
	m_posOldV = INIT_D3DXVECTOR3;	// �O��̒����_R3;
	m_vecU = INIT_VEC;				// ������x�N�g��
	m_rot = INIT_D3DXVECTOR3;		// ����
	m_ra = INIT_FLOAT;
	m_rb = INIT_FLOAT;
	m_rc = INIT_FLOAT;
	m_length = INIT_FLOAT;

	m_MousePos = INIT_D3DXVECTOR3;
	m_MousePosOld = INIT_D3DXVECTOR3;
	m_nCnt = 0;
}

// �f�X�g���N�^
CCamera::~CCamera()
{

}

//========================================
// ������
//========================================
HRESULT CCamera::lnit(void)
{
	m_posV = D3DXVECTOR3(0.0f, 100.0f, -120.0f);	//�J�����̈ʒu
	m_posR = D3DXVECTOR3(0.0f, 100.0f, 0.0f);		//����ꏊ
	m_posOldR = INIT_D3DXVECTOR3;	// �O��̎��_R3;
	m_posOldV = INIT_D3DXVECTOR3;	// �O��̒����_R3;
	m_vecU = INIT_VEC;				// ������x�N�g��
	m_rot = INIT_D3DXVECTOR3;		// ����

	return S_OK;
}

//========================================
// �I��
//========================================
void CCamera::Uninit(void)
{

}

//========================================
// �X�V
//========================================
void CCamera::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h�̎擾
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X�̎擾
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// �W���C�p�b�g�̎擾

	float MoveX, MoveY;
	int MoveZ;

	m_nCnt++;
	if ((m_nCnt % 2) == 0)
	{
		// �ߋ��̈ʒu
		m_MousePosOld = pInputMouse->GetPos();
	}

	// ���݂̈ʒu
	m_MousePos = pInputMouse->GetPos();

	// �ߋ��̈ʒu����
	m_posOldV = m_posV;
	m_posOldR = m_posR;

	// �����̌v�Z
	m_ra = m_posV.x - m_posR.x;
	m_rb = m_posV.z - m_posR.z;
	m_length = sqrtf(m_ra * m_ra + m_rb * m_rb);


	MoveX = m_MousePos.x - m_MousePosOld.x;
	MoveY = m_MousePos.y - m_MousePosOld.y;

	// �ړ�
	if (pInputMouse->GetPress(CInputMouse::MOUSE_LEFT) == true && pInputMouse->GetPress(CInputMouse::MOUSE_RIGHT) == true)
	{
		m_posV.x += MoveX;
		m_posV.z += MoveY;

		m_posR.x += MoveX;
		m_posR.z += MoveY;

		MoveZ = pInputMouse->GetWheel();

		if (MoveZ > 0 || MoveZ < 0)
		{
			float MoveRot;

			if (MoveZ >= 0)
			{
				MoveRot = 0.0f;
			}
			else if (MoveZ <= 0)
			{
				MoveRot = 3.1425f;
			}

			m_posV.x += sinf(MoveRot - (m_rot.z * D3DX_PI)) * CAMERA_SPEED;
			m_posV.z += cosf(MoveRot - (m_rot.z * D3DX_PI)) * CAMERA_SPEED;

			m_posR.x += sinf(MoveRot - (m_rot.z * D3DX_PI)) * CAMERA_SPEED;
			m_posR.z += cosf(MoveRot - (m_rot.z * D3DX_PI)) * CAMERA_SPEED;
		}
	}
	else if (pInputMouse->GetPress(CInputMouse::MOUSE_RIGHT) == true)
	{// �㉺�̈ړ�
		m_rot.z += MoveX / 100;

		MoveZ = pInputMouse->GetWheel();

		if (MoveZ > 0 || MoveZ < 0)
		{
			float MoveRot;

			if (MoveZ >= 0)
			{
				MoveRot = 1.0f;
			}
			else if (MoveZ <= 0)
			{
				MoveRot = -1.0f;
			}

			m_posV.y += MoveRot;
			m_posR.y += MoveRot;
		}
	}
	else if (pInputMouse->GetPress(CInputMouse::MOUSE_LEFT) == true)
	{//���̉�]�E���_
		m_rot.z += MoveX / 100;

		m_posV.x = m_posR.x + sinf(D3DX_PI * (1.0f - m_rot.z)) * m_length;
		m_posV.z = m_posR.z + cosf(D3DX_PI * (1.0f - m_rot.z)) * m_length;
	}
}

//========================================
// �ݒ�
//========================================
void CCamera::SetCamera(void)
{
	//�f�o�C�X�̏���
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(90.0f),						/* ����p */
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	/*��ʂ̃A�X�y�N�g��*/
		10.0f,										/*Z�l�̍ŏ��l*/
		1000.0f);									/*Z�l�̍ő�l*/

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,		/*���_*/
		&m_posR,		/*�����_*/
		&m_vecU);		/*������x�N�g��*/

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}