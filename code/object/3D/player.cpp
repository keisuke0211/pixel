//========================================
// 
// �v���C���[����
// 
//========================================
// *** player.cpp ***
//========================================
#include "player.h"
#include "../../manager.h"
#include "../../renderer.h"
#include "../../camera.h"
#include "../../input.h"
#include "../../sound.h"
#include "../../camera.h"

// ��`
const float CPlayer::PLAYER_SPEED = 2.5f;

//========================================
// �R���X�g���N�^
//========================================
CPlayer::CPlayer(int nPriority) : CObjectX(nPriority)
{
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.moveRot = INIT_D3DXVECTOR3;
	m_Info.targetRot = INIT_D3DXVECTOR3;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.fWidth = INIT_FLOAT;
	m_Info.fHeight = INIT_FLOAT;
	m_Info.fDepth = INIT_FLOAT;
}

//========================================
// �f�X�g���N�^
//========================================
CPlayer::~CPlayer()
{

}

//========================================
// ����
//========================================
CPlayer *CPlayer::Create(void)
{
	CPlayer *pPlayer = NULL;

	if (pPlayer != NULL)
	{
		return pPlayer;
	}

	// �I�u�W�F�N�g2D�̐���
	pPlayer = new CPlayer;

	// ����������
	pPlayer->Init();

	return pPlayer;
}

//========================================
// ������
//========================================
HRESULT CPlayer::Init(void)
{
	CCamera *pCamera = CManager::GetCamera();	// �J�����̎擾

	CObjectX::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_PLAYER);

	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	m_Info.col = INIT_D3DXCOLOR;
	
	// ����
	SetPos(m_Info.pos);
	SetSize();
	SetRot(m_Info.rot);

	return S_OK;
}

//========================================
// �I��
//========================================
void CPlayer::Uninit(void)
{
	CObjectX::Uninit();
}

//========================================
// �X�V
//========================================
void CPlayer::Update(void)
{
	// �ړ�����
	MovePos();

	// �ʒu�X�V
	UpdatePos();

	CObjectX::Update();
}

//========================================
// �`��
//========================================
void CPlayer::Draw(void)
{
	CObjectX::Draw();
}

//========================================
// �ړ�����
//========================================
void CPlayer::MovePos(void)
{
	// --- ��� ---------------------------------
	m_Info.moveRot = m_Info.rot;	// �ړ�����

	// --- �擾 ---------------------------------
	CCamera *pCamera = CManager::GetCamera();						// �J����
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// �W���C�p�b�g

	
	// --- �ړ� ---------------------------------
	if (pInputKeyboard->GetPress(DIK_D) == true || pInputJoypad->GetJoypadPress(CInputJoypad::JOYKEY_RIGHT, 0) == true)
	{// �E
		m_Info.moveRot.y = D3DX_PI;
		m_Info.moveRot.y *= 0.5f;

		float fAngle;	// �p�x

		fAngle = atan2f(pCamera->GetInfo().posR.z - pCamera->GetInfo().posV.z, pCamera->GetInfo().posR.x - pCamera->GetInfo().posV.x);

		fAngle -= (D3DX_PI * 0.5f);
		fAngle *= -1;

		m_Info.moveRot.y += fAngle;

		m_Info.move.x += sinf(m_Info.moveRot.y) * PLAYER_SPEED;
		m_Info.move.z += cosf(m_Info.moveRot.y) * PLAYER_SPEED;
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true || pInputJoypad->GetJoypadPress(CInputJoypad::JOYKEY_LEFT, 0) == true)
	{// ��
		m_Info.move.x -= PLAYER_SPEED;
	}
	else if (pInputKeyboard->GetPress(DIK_W) == true || pInputJoypad->GetJoypadPress(CInputJoypad::JOYKEY_UP, 0) == true)
	{// ��
		m_Info.move.z += PLAYER_SPEED;
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true || pInputJoypad->GetJoypadPress(CInputJoypad::JOYKEY_DOWN, 0) == true)
	{// ��
		m_Info.move.z -= PLAYER_SPEED;
	}

	// �ړ��ʂ̑��
	m_Info.pos += m_Info.move;

	// �ړ��ʂ̌���
	m_Info.move.x *= 0.8f;
	m_Info.move.z *= 0.8f;

	SetPos(m_Info.pos);

	// �J�����̒����_��ݒ�
	pCamera->SetPosR(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 95, m_Info.pos.z));
}
//========================================
// �ʒu�X�V
//========================================
void CPlayer::UpdatePos(void)
{


	// �ڕW�����Ɉړ���������
	m_Info.targetRot = m_Info.moveRot;
}