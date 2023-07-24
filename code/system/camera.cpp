//========================================
// 
// �J��������
// 
//========================================
// *** camera.cpp ***
//========================================
#include "camera.h"
#include "../manager.h"
#include "renderer.h"
#include "input.h"

//****************************************
// �}�N����`
//****************************************
#define CAMERA_ROT_FORCE_BY_CURSOR	(D3DXVECTOR3(0.0005f,0.00075f,0.0f))	// �J�[�\���̉�]��
#define CAMERA_ROT_FORCE_BY_STICK	(D3DXVECTOR3(0.004f,-0.006f,0.0f))		// �X�e�B�b�N�̉�]��
#define CAMERA_SPIN_DAMP			(0.9f)									// ��]�̌����l
#define CAMERA_SPEED				(50)									// �ړ����x�iX�EZ���W�j

//========================================
// �R���X�g���N�^
//========================================
CCamera::CCamera()
{
	/* �J������� */
	m_Info.posR = INIT_D3DXVECTOR3;		// ���݂̎��_
	m_Info.posV = INIT_D3DXVECTOR3;		// ���݂̒����_
	m_Info.posOldR = INIT_D3DXVECTOR3;	// �O��̎��_R3;
	m_Info.posOldV = INIT_D3DXVECTOR3;	// �O��̒����_R3;
	m_Info.vecU = INIT_VEC;				// ������x�N�g��
	m_Info.rot = INIT_D3DXVECTOR3;		// ����
	m_Info.spin = INIT_D3DXVECTOR3;		// ��]��
	m_Info.fDistance = INIT_FLOAT;		// ����
	m_Info.fHeight = INIT_FLOAT;		// ����
	m_Info.fVerticalMove = INIT_FLOAT;	// �c�̈ړ���
	m_Info.nScreen = SCREEN_NONE;		// ���e���[�h

	/* �ۑ���� */
	m_Save.posV = INIT_D3DXVECTOR3;		// ���_
	m_Save.posR = INIT_D3DXVECTOR3;		// �����_
	m_Save.rot = INIT_D3DXVECTOR3;		// ����
	m_Save.spin = INIT_D3DXVECTOR3;		// ��]��
	m_Save.fVerticalMove = INIT_FLOAT;	// �c�̈ړ���
	m_Save.fHeight = INIT_FLOAT;		// ����
	m_Save.fDistance = INIT_FLOAT;		// ����
}

//========================================
// �f�X�g���N�^
//========================================
CCamera::~CCamera()
{

}

//========================================
// ������
//========================================
HRESULT CCamera::Init(void)
{
	/* �J������� */
	m_Info.posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �J�����̈ʒu
	m_Info.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����ꏊ
	m_Info.posOldR = INIT_D3DXVECTOR3;				// �O��̎��_R3;
	m_Info.posOldV = INIT_D3DXVECTOR3;				// �O��̒����_R3;
	m_Info.vecU = INIT_VEC;							// ������x�N�g��
	m_Info.rot = INIT_D3DXVECTOR3;					// ����
	m_Info.spin = INIT_D3DXVECTOR3;					// ��]��
	m_Info.fDistance = 100.0f;						// ����
	m_Info.fHeight = 0.05f;							// ����
	m_Info.fVerticalMove = INIT_FLOAT;				// �c�̈ړ���
	m_Info.nScreen = SCREEN_3D;						// ���e���[�h

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
	// --- �擾---------------------------------
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// �W���C�p�b�g

	// �ߋ��̈ʒu����
	m_Info.posOldV = m_Info.posV;
	m_Info.posOldR = m_Info.posR;

	if (pInputMouse->GetPress(CInputMouse::MOUSE_RIGHT))
	{// �}�E�X�̉E�{�^����������Ă����

		 // �J�[�\���̈ړ��ʂɉ����ĉ�]

		if (m_Info.nScreen == SCREEN_3D)
		{
			AxisRotationCamera(DIRECTION_UP, pInputMouse->GetCursorMove().y * CAMERA_ROT_FORCE_BY_CURSOR.x);
		}
		AxisRotationCamera(DIRECTION_LEFT, pInputMouse->GetCursorMove().x * CAMERA_ROT_FORCE_BY_CURSOR.y);	
	}
	else if (pInputJoypad->GetStick().aTplDiameter[CInputJoypad::STICK_TYPE_RIGHT] > 0.1f)
	{
		AxisRotationCamera(DIRECTION_UP, (cosf(pInputJoypad->GetStick().aAngle[CInputJoypad::STICK_TYPE_RIGHT]) * pInputJoypad->GetStick().aTplDiameter[CInputJoypad::STICK_TYPE_RIGHT]) * CAMERA_ROT_FORCE_BY_STICK.x);
		AxisRotationCamera(DIRECTION_LEFT, (sinf(pInputJoypad->GetStick().aAngle[CInputJoypad::STICK_TYPE_RIGHT]) * pInputJoypad->GetStick().aTplDiameter[CInputJoypad::STICK_TYPE_RIGHT]) * CAMERA_ROT_FORCE_BY_STICK.y);
	}

	m_Info.rot += m_Info.spin;					// �������X�V
	m_Info.spin *= CAMERA_SPIN_DAMP;			// ��]�ʂ�����
	m_Info.fHeight += m_Info.fVerticalMove;		// �������X�V
	m_Info.fVerticalMove *= CAMERA_SPIN_DAMP;	// �c�����̈ړ��ʂ�����

	// �����𐧌�
	RotControl(&m_Info.rot);

	// �����𐧌�
	FloatControl(&m_Info.fHeight, D3DX_PI * 0.30f, D3DX_PI * 0.01f);

	//// ���_�̈ʒu�ݒ�
	//m_Info.posV.x = m_Info.posR.x + (sinf(m_Info.rot.y + D3DX_PI) * (m_Info.fDistance * (1.0 - fabsf(m_Info.fHeight))));
	//m_Info.posV.y = m_Info.posR.y + (m_Info.fDistance * m_Info.fHeight);
	//m_Info.posV.z = m_Info.posR.z + (cosf(m_Info.rot.y + D3DX_PI) * (m_Info.fDistance * (1.0 - fabsf(m_Info.fHeight))));

	if (pInputKeyboard->GetTrigger(DIK_Q) == true || pInputMouse->GetTrigger(CInputMouse::MOUSE_5) == true)
	{// �}�E�X�̃T�C�h�{�^��2����������

		// ��ʐݒ�
		SetScreen();
	}

	if (pInputKeyboard->GetPress(DIK_UP))
	{
		m_Info.posV.z += 1.0f;
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
	D3DXMatrixIdentity(&m_Info.mtxProjection);

	//�v���W�F�N�V�����}�g���b�N�X���쐬

	switch (m_Info.nScreen)
	{
	case SCREEN_2D: {	// ���s���e
		D3DXMatrixOrthoLH(&m_Info.mtxProjection,
			SCREEN_WIDTH / 2,						/* ��ʂ̕� */
			SCREEN_HEIGHT / 2,						/* ��ʂ̍��� */
			1.0f,									/* Z�l�̍ŏ��l */
			1500.0f);								/* Z�l�̍ő�l */
	}
		break;

	case SCREEN_3D: {	// �������e
		D3DXMatrixPerspectiveFovLH(&m_Info.mtxProjection,
			D3DXToRadian(90.0f),							/* ����p */
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,		/*��ʂ̃A�X�y�N�g��*/
			10.0f,											/*Z�l�̍ŏ��l*/
			2000.0f);										/*Z�l�̍ő�l*/
	}
		break;
	}

	//�v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_Info.mtxProjection);

	//�r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_Info.mtxView);

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_Info.mtxView,
		&m_Info.posV,		/*���_*/
		&m_Info.posR,		/*�����_*/
		&m_Info.vecU);		/*������x�N�g��*/

	//�r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_Info.mtxView);
}

//========================================
// �J�����̉�ʐݒ�
//========================================
void CCamera::SetScreen(void)
{
	// ���e���[�h�̐؂�ւ�

	switch (m_Info.nScreen)
	{
	case SCREEN_2D: {	// ���s���e
		
		// �ۑ�����������
		m_Info.posV = m_Save.posV;						// ���_
		m_Info.posR = m_Save.posR;						// �����_
		m_Info.rot  = m_Save.rot;						// ����
		m_Info.spin = m_Save.spin;						// ��]��
		m_Info.fHeight = m_Save.fHeight;				// ����
		m_Info.fDistance = m_Save.fDistance;			// ����
		m_Info.fVerticalMove = m_Save.fVerticalMove;	// �c�̈ړ���

		m_Info.nScreen = SCREEN_3D;
	}
	 break;

	case SCREEN_3D: {	// �������e
		
		// ����ۑ�����
		m_Save.posV = m_Info.posV;						// ���_
		m_Save.posR = m_Info.posR;						// �����_
		m_Save.rot	= m_Info.rot;						// ����
		m_Save.spin	= m_Info.spin;						// ��]��
		m_Save.fHeight = m_Info.fHeight;				// ����
		m_Save.fDistance = m_Info.fDistance;			// ����
		m_Save.fVerticalMove = m_Info.fVerticalMove;	// �c�̈ړ���

		// ������������
		m_Info.rot.y = 0.0f;

		m_Info.nScreen = SCREEN_2D;
	}
	 break;
	}
}

//========================================
// �J�����̉�]����
//========================================
void CCamera::AxisRotationCamera(DIRECTION drct, float fRot, int nIdx)
{
	// �����ɉ����Č����̈ړ��ʂ��X�V
	switch (drct)
	{
	case DIRECTION_UP:m_Info.fVerticalMove += fRot; break;
	case DIRECTION_DOWN:m_Info.fVerticalMove -= fRot; break;
	case DIRECTION_LEFT:m_Info.spin.y -= fRot; break;
	case DIRECTION_RIGHT:m_Info.spin.y += fRot; break;
	}
}

//========================================
// �J�����̎��_�ݒ�
//========================================
void CCamera::SetPosV(D3DXVECTOR3 pos, int nIdx)
{
	// ���_�̈ʒu����
	m_Info.posV = pos;

	// �����_�̈ʒu��ݒ�
	m_Info.posR.x = m_Info.posV.x + (sinf(m_Info.rot.y) * (m_Info.fDistance * (1.0f - fabsf(m_Info.fHeight))));
	m_Info.posR.y = m_Info.posV.y + (m_Info.fDistance * m_Info.fHeight);
	m_Info.posR.z = m_Info.posV.z + (cosf(m_Info.rot.y) * (m_Info.fDistance * (1.0f - fabsf(m_Info.fHeight))));
}

//========================================
// �J�����̒����_�ݒ�
//========================================
void CCamera::SetPosR(D3DXVECTOR3 pos, int nIdx)
{
	// �����_�̈ʒu����
	m_Info.posR = pos;

	// ���_�̈ʒu��ݒ�
	m_Info.posV.x = m_Info.posR.x + (sinf(m_Info.rot.y) * (m_Info.fDistance * (1.0f - fabsf(m_Info.fHeight))));
	m_Info.posV.y = m_Info.posR.y + (m_Info.fDistance * m_Info.fHeight);
	m_Info.posV.z = m_Info.posR.z + (cosf(m_Info.rot.y) * (m_Info.fDistance * (1.0f - fabsf(m_Info.fHeight))));
}