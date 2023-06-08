//========================================
// 
// �e����
// 
//========================================
// *** bullet.h ***
//========================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "../../main.h"
#include "../object2D.h"

//****************************************
// �N���X
//****************************************
class CBullet : public CObject2D
{
public:

	// ***** ��` *****
	static const int MAX_TEXTURE = 50;	// �e�N�X�`���̍ő吔

	// ***** �\���� *****

	// �e���
	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 rot;	// ����
		D3DXVECTOR3 move;	// �ړ���
		int nType;			// ���
		int nLife;			// ����
		float fWidth;		// ��
		float fHeight;		// ����
		bool bShot;			// �ʒu�؂�ւ�
	} Info;

	// ***** �֐� *****
	CBullet(int nPriority = TYPE_BULLET);
	~CBullet();

	/* ���C�� */
	static HRESULT Load(char *pPath);			// �e�N�X�`���̐��� 
	static void Unload(void);					// �e�N�X�`���̔j��

	// ����
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,bool bShot);

	HRESULT Init(void);				// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��

	/* �擾 */
	Info GetInfo() { return m_Info; }				// �v���C���[���

private:

	// ***** �֐� *****
	bool CollsionEnemy(D3DXVECTOR3 pos);					// �G�Ƃ̓����蔻��

	// ***** �ϐ� *****
	Info m_Info;	// ���

	// ***** �ÓI�ϐ� *****
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	// ���L�e�N�X�`��
	static int m_nTexture;								// �e�N�X�`���̐�

};
#endif