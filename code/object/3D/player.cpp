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
#include "../../input.h"
#include "../../sound.h"
#include "bullet.h"
#include "../object2D.h"

//****************************************
// �}�N����`
//****************************************
#define JUMP_POWER		(-20.0f)// �W�����v��
#define GRAVITY_MAG		(0.08f)	// �d�͌W��
#define GRAVITY_POWER	(9.0f)	// �d�͉����x

// ��`
const float CPlayer::PLAYER_SPEED = 2.5f;

// �ÓI�����o�ϐ�
LPDIRECT3DTEXTURE9 CPlayer::m_pTexture[CPlayer::MAX_TEXTURE] = { NULL };
int CPlayer::m_nTexture = -1;

// �R���X�g���N�^
CPlayer::CPlayer(int nPriority) : CObject2D(nPriority)
{
	// �l���N���A
	m_Info.pos = INIT_D3DXVECTOR3;
	m_Info.rot = INIT_D3DXVECTOR3;
	m_Info.move = INIT_D3DXVECTOR3;
	m_Info.fWidth = INIT_FLOAT;
	m_Info.fHeight = INIT_FLOAT;
	m_Info.fJump = INIT_FLOAT;
	m_Info.fMove = INIT_FLOAT;
	m_Info.bJump = false;


	bShot = false;
}

// �f�X�g���N�^
CPlayer::~CPlayer()
{

}

//========================================
// �e�N�X�`���̓ǂݍ���
//========================================
HRESULT CPlayer::Load(char *pPath)
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
void CPlayer::Unload(void)
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
	CObject2D::Init();
	
	// ��ނ̐ݒ�
	SetType(TYPE_PLAYER);

	m_Info.pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_Info.fWidth = 75.0f;
	m_Info.fHeight = 75.0f;
	m_Info.fJump = 2.0f;

	// ����
	SetPos(m_Info.pos);
	SetSize(m_Info.fWidth,m_Info.fHeight);
	SetRot(m_Info.rot);
	SetColor(INIT_D3DXCOLOR);
	SetPtn(25);
	SetPtnInfo(5, 8, 46, false, 0);

	// �e�N�X�`���̊��蓖��
	BindTexture(m_pTexture[0]);

	return S_OK;
}

//========================================
// �I��
//========================================
void CPlayer::Uninit(void)
{
	CObject2D::Uninit();
}

//========================================
// �X�V
//========================================
void CPlayer::Update(void)
{
	// �ړ��E��������
	Physics();

	CObject2D::Update();
}

//========================================
// �`��
//========================================
void CPlayer::Draw(void)
{
	CObject2D::Draw();
}

//========================================
// �ړ��E��������
//========================================
void CPlayer::Physics(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();	// �L�[�{�[�h�̎擾
	CInputMouse *pInputMouse = CManager::GetInputMouse();			// �}�E�X�̎擾
	CInputJoypad *pInputJoypad = CManager::GetInputJoypad();		// �W���C�p�b�g�̎擾

	// --- �ړ� ---------------------------------

	if (pInputKeyboard->GetPress(DIK_D) == true || pInputJoypad->GetJoypadPress(CInputJoypad::JOYKEY_RIGHT, 0) == true)
	{// �E
		AddMove(0.5f);
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true || pInputJoypad->GetJoypadPress(CInputJoypad::JOYKEY_LEFT, 0) == true)
	{// ��
		AddMove(-0.5f);
	}

	//�ړ��ʂ��X�V(����������)
	m_Info.move.x += (0.0f - m_Info.move.x) * 0.25f;

	// --- �W�����v ---------------------------------
	if (pInputKeyboard->GetPress(DIK_SPACE) == true || pInputJoypad->GetJoypadPress(CInputJoypad::JOYKEY_A, 0) == true)
	{
		m_Info.bJump = true;	// �W�����v�t���O��^�ɂ���
		m_Info.move.y += JUMP_POWER;
	}

	m_Info.pos.y += m_Info.move.y;

	// �ړ��ʂ��X�V(����)
	m_Info.move.y += GRAVITY_MAG;

	if (m_Info.bJump)
	{// �W�����v�t���O���^�̎��A
	
	}


	// �ʒu�̍X�V
	SetPos(m_Info.pos);

	CSound *pSound = CManager::GetSound();

	// �}�E�X

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		CBullet::Create(m_Info.pos, D3DXVECTOR3(0.0f, -7.5f, 0.0f), false);
		CBullet::Create(m_Info.pos, D3DXVECTOR3(0.0f, -7.5f, 0.0f), true);
		pSound->PlaySound(1);
	}
	else if (pInputMouse->GetTrigger(CInputMouse::MOUSE_RIGHT) == true)
	{
		CBullet::Create(m_Info.pos, D3DXVECTOR3(0.0f, -7.5f, 0.0f), false);
		pSound->PlaySound(1);
	}

	else if (pInputMouse->GetTrigger(CInputMouse::MOUSE_LEFT) == true)
	{
		CBullet::Create(m_Info.pos, D3DXVECTOR3(0.0f, -7.5f, 0.0f), true);
		pSound->PlaySound(1);
	}
}

//========================================
// �ړ��ʂ̍X�V
//========================================
void CPlayer::AddMove(float fRoty)
{
	// �ړ���
	m_Info.move.x += sinf(D3DX_PI * fRoty) * PLAYER_SPEED;
	m_Info.move.y += cosf(D3DX_PI * fRoty) * PLAYER_SPEED;

	m_Info.pos += m_Info.move;
}

//========================================
// �����蔻��
//========================================
D3DXVECTOR3 CPlayer::Collision(D3DXVECTOR3 pos)
{

}