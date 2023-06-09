//========================================
// 
// �v���C���[����
// 
//========================================
// *** player.h ***
//========================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "../../main.h"
#include "../object2D.h"

//****************************************
// �N���X
//****************************************
class CPlayer : public CObject2D
{
public:

	// ***** ��` *****
	static const int MAX_TEXTURE = 50;	// �e�N�X�`���̍ő吔

	static const int PLAYER_MAX = 1;	// �v���C���[�̍ő吔
	static const float PLAYER_SPEED;	// �v���C���[�̈ړ���

	// ***** �\���� *****

	// �v���C���[���
	typedef struct
	{
		D3DXVECTOR3 pos;			// �ʒu
		D3DXVECTOR3 rot;			// ����
		D3DXVECTOR3 move;			// �ړ���
		float fWidth;				// ��
		float fHeight;				// ����
		float fJump;				// �W�����v��
		bool bJump;					// �W�����v�t���O
	} Info;

	// ***** �֐� *****
	CPlayer(int nPriority = TYPE_PLAYER);
	~CPlayer();

	/* ���C�� */
	static HRESULT Load(char *pPath);			// �e�N�X�`���̐��� 
	static void Unload(void);					// �e�N�X�`���̔j��

	// ����
	static CPlayer *Create(void);

	HRESULT Init(void);				// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��

	/* �擾 */
	Info GetInfo() { return m_Info; }	// �v���C���[���

private:
	// ***** �֐� *****
	void AddMove(float fRoty);				// �ړ��ʂ̍X�V
	void Physics(void);						// �ړ��E��������
	D3DXVECTOR3 Collision(D3DXVECTOR3 pos);	// �u���b�N�̓����蔻��

	// ***** �ϐ� *****
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];		// ���L�e�N�X�`��
	static int m_nTexture;									// �e�N�X�`���̐�

	Info m_Info;	// �v���C���[���
	bool bShot;
};
#endif