//========================================
// 
// �}���`�w�i����
// 
//========================================
// *** bg_Multi.h ***
//========================================
#ifndef _BG_MULTI_H_
#define _BG_MULTI_H_

#include "../main.h"
#include "object.h"
//****************************************
// �O���錾
//****************************************
class CBg;

//****************************************
// �N���X
//****************************************
class CBgMulti : public CObject
{
public:

	// ***** �֐� *****
	CBgMulti(int nPriority = TYPE_BG);
	virtual~CBgMulti();

	// ����
	static CBgMulti *Create(D3DXVECTOR3 move, int nType);

	/* ���C�� */
	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

private:

	// ***** ��` *****
	static const int BG_MAX = 3;	// �w�i�̍ő吔

	// ***** �ϐ� *****
	CBg *m_apBg[BG_MAX];		// �w�i�̃|�C���^�z��
	D3DXVECTOR3 m_move;
	int m_nType;

	// ***** �ÓI�ϐ� *****
	static int m_nNumBg;			// �w�i�̐�

};
#endif