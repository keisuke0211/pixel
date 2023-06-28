//========================================
//
// �G�t�F�N�g�y 2D �z
//
//========================================
// *** effect2D.h ***
//========================================
#ifndef _EFFECT2D_H_
#define _EFFECT2D_H_

#include "../../main.h"
#include "../object2D.h"

//****************************************
// �N���X
//****************************************
class CEffect2D : public CObject2D
{
public:

	CEffect2D(int nPriority = TYPE_EFFECT);
	~CEffect2D();

	// *****  �֐� *****

	/* ���C�� */
	HRESULT Init(void);		// ������
	void Uninit(void);		// �I��
	void Update(void);		// �X�V
	void Draw(void);		// �`��

	// ����
	static CEffect2D *Create(void);

	/* �ݒ� */
	void SetLife(int nLife) { m_nLife = m_nLifeMax = nLife; }	// ����
	void SetEffColor(D3DXCOLOR col) { m_color = col; }			// �F

private:
	// ***** �ϐ� *****
	int m_nLife;		// ����
	int m_nLifeMax;		// �����ő�l
	D3DXCOLOR m_color;	// �F

};
#endif 