//========================================
// 
// �u���b�N����
// 
//========================================
// *** block.h ***
//========================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "../../main.h"
#include "../objectX.h"

//****************************************
// �N���X
//****************************************
class CBlock : public CObjectX
{
public:

	// ***** �\���� *****

	// �v���C���[���
	typedef struct
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 posOld;		// �ʒu(�ߋ�)
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 rotOld;		// ����(�ߋ�)
		D3DXVECTOR3	size;		// �T�C�Y
		D3DXCOLOR col;			// ���_�J���[
		int nType;				// ���
		int nLife;				// ����
		int nLifeMax;			// �����̍ő�l
		float fRadius;			// ���a
		int nCntRadius;			// ���a�E���ڎ���
		float fRadiusRate;		// ���a�̊���
		bool bSet;				// �z�u�t���O
	} Info;

	// ***** �֐� *****
	CBlock(int nPriority = PRIO_OBJX);
	~CBlock();

	/* ���C�� */

	// ����
	static CBlock *Create(int nType,D3DXVECTOR3 pos);

	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��
	
	/* �ݒ� */
	virtual void BlockSetPos(const D3DXVECTOR3 pos) { m_Info.pos = pos; }	// �ʒu
	void BlockSetRot(const D3DXVECTOR3 rot) { m_Info.rot = rot; }			// ����
	void BlockSetColor(const D3DXCOLOR col) { m_Info.col = col; }			// �F
	void BlockSetSize(const D3DXVECTOR3 size) { m_Info.size = size; }		// �傫��

	/* ���� */
	D3DXVECTOR3 BlockGetPos(void) { return m_Info.pos; }					// �ʒu
	D3DXVECTOR3 GetRot(void) { return m_Info.rot; }							// ����
	D3DXCOLOR BlockGetColor(void) { return m_Info.col; }					// �F
	D3DXVECTOR3 BlockGetSize(void) { return m_Info.size; }					// �傫��

private:

	// ***** �ϐ� *****
	Info m_Info;				// �v���C���[���

};
#endif