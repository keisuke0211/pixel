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

	// ***** ��` ****
	static const int BG_MAX = 3;	// �w�i�̍ő吔

	// ***** �֐� *****
	CBg(int nPriority = TYPE_BG);
	virtual~CBg();

	/* ���C�� */

	// ����
	static CBg *Create(D3DXVECTOR3 move, int nType);

	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

private:
	// ***** �ϐ� *****
	D3DXVECTOR3 m_texPos;								// �e�N�X�`���̈ʒu		
	D3DXVECTOR3 m_texMove;								// �e�N�X�`���̉��Z�l
	int m_Type;											// �摜���

};
#endif