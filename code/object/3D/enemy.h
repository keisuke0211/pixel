//========================================
// 
// �G�l�~�[����
// 
//========================================
// *** enemy.h ***
//========================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "../../main.h"
#include "../object2D.h"

//****************************************
// �N���X
//****************************************
class CEnemy : public CObject2D
{
public:

	// ***** ��` *****
	static const int MAX_TEXTURE = 50;	// �e�N�X�`���̍ő吔

	static const int MAX_ENEMY = 30;	// �G�̍ő吔

	// ***** �֐� *****
	CEnemy(int nPriority = TYPE_ENEMY);
	virtual~CEnemy();

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
	} Info;

	/* ���C�� */
	static HRESULT Load(char *pPath);			// �e�N�X�`���̐��� 
	static void Unload(void);					// �e�N�X�`���̔j��

	// ����
	static CEnemy *Create(D3DXVECTOR3 pos);

	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

	void HitLife(int nDamage);

	/* �擾 */
	Info GetInfo() { return m_Info; }				// �v���C���[���
	D3DXVECTOR3 GetPos() { return m_Info.pos; }		// �ʒu

private:

	// ***** �ϐ� *****
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];		// ���L�e�N�X�`��
	static int m_nTexture;									// �e�N�X�`���̑���
	Info m_Info;	// ���
};
#endif