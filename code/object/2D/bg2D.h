//========================================
// 
// �w�i����
// 
//========================================
// *** bg.h ***
//========================================
#ifndef _BG_H_
#define _BG_H_

#include "../../main.h"
#include "../object2D.h"


//****************************************
// �N���X
//****************************************
class CBg : public CObject2D
{
public:

	// ***** ��` *****
	static const int MAX_TEXTURE = 50;	// �e�N�X�`���̍ő吔

	static const int BG_MAX = 3;	// �w�i�̍ő吔

	// ***** �֐� *****
	CBg(int nPriority = TYPE_BG);
	virtual~CBg();

	/* ���C�� */
	static HRESULT Load(char *pPath);			// �e�N�X�`���̐��� 
	static void Unload(void);					// �e�N�X�`���̔j��

	// ����
	static CBg *Create(D3DXVECTOR3 move, int nType);

	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

private:
	// ***** �ϐ� *****
	static int m_nTexture;								// �e�N�X�`���̑���
	D3DXVECTOR3 m_texPos;								// �e�N�X�`���̈ʒu		
	D3DXVECTOR3 m_texMove;								// �e�N�X�`���̉��Z�l
	int m_Type;											// �摜���

	// ***** �ÓI�ϐ� *****
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	// ���L�e�N�X�`��
};
#endif