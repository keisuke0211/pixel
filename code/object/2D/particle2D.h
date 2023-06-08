//========================================
//
// �p�[�e�B�N���y 2D �z
//
//========================================
// *** particle2D.h ***
//========================================
#ifndef _PARTICLE2D_H_
#define _PARTICLE2D_H_

#include "../../main.h"
#include "../object.h"

//****************************************
// �N���X
//****************************************
class CParticle2D : public CObject
{
public:

	CParticle2D(int nPriority = TYPE_PARTICLE);
	~CParticle2D();

	// *****  �֐� *****

	/* ���C�� */
	HRESULT Init(void);		// ������
	void Uninit(void);		// �I��
	void Update(void);		// �X�V
	void Draw(void);		// �`��

	// ����
	static CParticle2D *Create(void);
	void SetEffect(void);

	/* �ݒ� */
	void SetMove(float fMove) { m_fMove = fMove; }				// �ړ���
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }				// �ʒu
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }				// ����
	void SetLife(int nLife) { m_nLife = m_nLifeMax = nLife; }	// ����
	void SetParColor(D3DXCOLOR col) { m_col = col; }			// �F

private:
	// ***** �ϐ� *****
	float m_fMove;		// �ړ���
	int m_nLife;		// ����
	int m_nLifeMax;		// �����ő�l
	D3DXCOLOR m_col;	// �F
	D3DXVECTOR3 m_pos;	// �ʒu
	D3DXVECTOR3 m_rot;	// ����
};
#endif 