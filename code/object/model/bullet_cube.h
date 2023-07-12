//========================================
// 
// �L���[�u����
// 
//========================================
// *** bullet_cube.h ***
//========================================
#ifndef _BULLET_CUBE_H_
#define _BULLET_CUBE_H_

#include "../../main.h"
#include "../objectX.h"

//****************************************
// �N���X
//****************************************
class CCube : public CObjectX
{
public:

	// ***** �\���� *****

	// �v���C���[���
	typedef struct
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 posOld;		// �ʒu(�ߋ�)
		D3DXVECTOR3 movePos;	// �ړ��ʒu
		D3DXVECTOR3 targetPos;	// �ڕW�ʒu	
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 rotOld;		// ����(�ߋ�)
		D3DXVECTOR3	size;		// �T�C�Y
		D3DXCOLOR col;			// ���_�J���[
		int nType;				// ���
		int nStandTime;			// �ҋ@����
		bool bContact;			// �ڐG�t���O
		bool bActivation;		// �����t���O
		int nLife;				// ����
		int nLifeMax;			// �����̍ő�l
		float fRadius;			// ���a
		int nCntRadius;			// ���a�E���ڎ���
		float fRadiusRate;		// ���a�̊���
		bool bSet;				// �z�u�t���O
		int nID;				// ���g��ID
	} Info;

	// ***** �֐� *****
	/* �R���X�g���N�^	*/CCube(int nPriority = PRIO_OBJX);
	/* �f�X�g���N�^		*/~CCube();

	// -- ���C�� -------------------------------
	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);
	/* ����		*/static CCube *Create(int nType, D3DXVECTOR3 pos);

	// -- �ݒ� -------------------------------
	/* �ʒu		*/void CubeSetPos(const D3DXVECTOR3 pos) { m_Info.pos = m_Info.posOld = pos; }
	/* ����		*/void CubeSetRot(const D3DXVECTOR3 rot) { m_Info.rot = rot; }
	/* �F		*/void CubeSetColor(const D3DXCOLOR col) { m_Info.col = col; }
	/* �T�C�Y	*/void CubeSetSize(const D3DXVECTOR3 size) { m_Info.size = size; }
	/* ���		*/void CubeSetType(const int type) { m_Info.nType = type; }

	// -- �擾 -------------------------------
	/* �ʒu		*/D3DXVECTOR3 CubeGetPos(void) { return m_Info.pos; }
	/* ����		*/D3DXVECTOR3 GetRot(void) { return m_Info.rot; }
	/* �F		*/D3DXCOLOR CubeGetColor(void) { return m_Info.col; }
	/* �T�C�Y	*/D3DXVECTOR3 CubeGetSize(void) { return m_Info.size; }

private:

	// ***** �֐� ***** correction
	/* �ʒu�␳		*/bool Correction(DIRECTION direction, D3DXVECTOR3 pos);
	/* �ڐG����		*/bool Contact(VECTOR vector, D3DXVECTOR3 pos);
	/* �����蔻��	*/bool Collsion(DIRECTION direction,CObject *pObj);

	// ***** �ϐ� *****
	Info m_Info;		// �v���C���[���

};
#endif