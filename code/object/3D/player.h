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
#include "../../physics.h"
#include "../model.h"

//****************************************
// �N���X
//****************************************
class CPlayer : public CObject
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
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 moveRot;	// �ړ�����
		D3DXVECTOR3 targetRot;	// �ڕW����
		D3DXVECTOR3 move;		// �ړ���
		D3DCOLOR col;			//�@���_�J���[
		float fWidth;			// ��
		float fHeight;			// ����
		float fDepth;			// ���s��
	} Info;

	// ***** �֐� *****
	CPlayer(int nPriority = CObject::TYPE_PLAYER);
	~CPlayer();

	/* ���C�� */

	// ����
	static CPlayer *Create(void);

	HRESULT Init(void);				// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��

	/* �擾 */
	D3DXVECTOR3 GetPos() { return m_Info.pos; }

private:
	// ***** �֐� *****
	void MovePos(float fMove);	// �ړ�
	void UpdatePos(void);		// �ʒu�X�V

	/* �ړ� */
	void MoveKeyboard(DIRECTION drct);	// �L�[�{�[�h�̈ړ�����

	/* ���� */
	void KeyInput(void);	// �L�[�{�[�h

	// ***** �ϐ� *****
	Info m_Info;		// �v���C���[���
};
#endif