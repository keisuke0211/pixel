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
#include "../../physics.h"


// ��`
const float CPlayer::PLAYER_SPEED = 2.5f;
int CPlayer::nCnt = -1;

//========================================
// �R���X�g���N�^
//========================================
CPlayer::CPlayer(int nPriority) : CMotionModel(nPriority)
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
	nCnt++;
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

	CMotionModel::Init();

	// ��ނ̐ݒ�
	SetType(TYPE_PLAYER);

	m_Info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Info.rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);
	m_Info.col = INIT_D3DXCOLOR;
	
	// ����
	SetMotion("data\\GAMEDATA\\MODEL\\Player\\PLAYER_DATA.txt");
	SetPos(m_Info.pos);
	SetRot(m_Info.rot);

	return S_OK;
}

//========================================
// �I��
//========================================
void CPlayer::Uninit(void)
{
	CMotionModel::Uninit();
}

//========================================
// �X�V
//========================================
void CPlayer::Update(void)
{
	// �ړ�����
	KeyInput();

	// �ʒu�X�V����
	UpdatePos();

	CMotionModel::Update();
}

//========================================
// �`��
//========================================
void CPlayer::Draw(void)
{
	CMotionModel::Draw();
}

//========================================
// �L�[�{�[�h�̓��͏���
//========================================
void CPlayer::KeyInput(void)
{
	// --- �擾 ---------------------------------
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// �W���C�p�b�g

	if (pInputKeyboard->GetPress(DIK_A))
	{
		if (pInputKeyboard->GetPress(DIK_W)) { MoveKeyboard(DIRECTION_LEFT_BACK); }			// �����ړ�
		else if (pInputKeyboard->GetPress(DIK_S)) { MoveKeyboard(DIRECTION_LEFT_FRONT); }	// ����O�ړ�
		else { MoveKeyboard(DIRECTION_LEFT); }		// ���ړ�
	}
	else if (pInputKeyboard->GetPress(DIK_D))
	{
		if (pInputKeyboard->GetPress(DIK_W)) { MoveKeyboard(DIRECTION_RIGHT_BACK); }		// �E���ړ�
		else if (pInputKeyboard->GetPress(DIK_S)) { MoveKeyboard(DIRECTION_RIGHT_FRONT); }	// �E��O�ړ�
		else { MoveKeyboard(DIRECTION_RIGHT); }		// �E�ړ�
	}
	else if (pInputKeyboard->GetPress(DIK_W)) { MoveKeyboard(DIRECTION_BACK); }		// ���ړ�
	else if (pInputKeyboard->GetPress(DIK_S)) { MoveKeyboard(DIRECTION_FRONT); }	// ��O�ړ�
}

//========================================
// �L�[�{�[�h�̈ړ�����
//========================================
void CPlayer::MoveKeyboard(DIRECTION drct)
{
	// --- ��� ---------------------------------
	m_Info.moveRot = m_Info.rot;	// �ړ�����

	// --- �ړ� ---------------------------------

	// �ړ������ɉ~��������
	m_Info.moveRot.y = D3DX_PI;

	switch (drct)
	{
	case DIRECTION_LEFT:m_Info.moveRot.y *= -0.5f; break;			// ��
	case DIRECTION_RIGHT:m_Info.moveRot.y *= 0.5f; break;			// �E
	case DIRECTION_BACK:m_Info.moveRot.y *= 0.0f; break;			// ��
	case DIRECTION_FRONT:m_Info.moveRot.y *= 1.0f; break;			// ��O
	case DIRECTION_LEFT_BACK:m_Info.moveRot.y *= -0.25f; break;		// ����
	case DIRECTION_LEFT_FRONT:m_Info.moveRot.y *= -0.75f; break;	// ����O
	case DIRECTION_RIGHT_BACK:m_Info.moveRot.y *= 0.25f; break;		// �E��
	case DIRECTION_RIGHT_FRONT:m_Info.moveRot.y *= 0.75f; break;	// �E��O
	}

	// �ʒu�X�V
	MovePos(PLAYER_SPEED);
}

//========================================
// �ړ�����
//========================================
void CPlayer::MovePos(float fMove)
{
	// --- �擾 ---------------------------------
	CCamera *pCamera = CManager::GetCamera();		// �J����

	D3DXVECTOR3 posV = pCamera->GetInfo().posV;	// ���_
	D3DXVECTOR3 posR = pCamera->GetInfo().posR;	// �����_

	// ���_���璍���_�܂ł̊p�x
	float fAngle
		= FindAngle(D3DXVECTOR3(posV.x, posV.z, 0.0f), D3DXVECTOR3(posR.x, posR.z, 0.0f));

	m_Info.moveRot.y += fAngle;

	m_Info.move.x += sinf(m_Info.moveRot.y) * fMove;
	m_Info.move.z += cosf(m_Info.moveRot.y) * fMove;
}

//========================================
// �ʒu�X�V
//========================================
void CPlayer::UpdatePos(void)
{
	// --- �擾 ---------------------------------
	CCamera *pCamera = CManager::GetCamera();		// �J����

	// �ړ��ʂ̑��
	m_Info.pos += m_Info.move;

	// �ړ��ʂ̌���
	m_Info.move.x *= 0.8f;
	m_Info.move.z *= 0.8f;

	SetPos(m_Info.pos);

	// �ڕW�����Ɉړ���������
	m_Info.targetRot = m_Info.moveRot;

	// �J�����̒����_��ݒ�
	pCamera->SetPosR(D3DXVECTOR3(m_Info.pos.x, m_Info.pos.y + 95, m_Info.pos.z));
}