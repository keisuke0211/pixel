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

	// ***** �񋓌^ *****

	// ���f�����
	enum SHAPE
	{
		SHAPE_LINE = 0,	// ����
		SHAPE_SQUARE,	// �l�p
		SHAPE_MAX
	};

	// ***** �\���� *****

	// �v���C���[���
	struct Info
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 posOld;		// �ʒu(�ߋ�)
		D3DXVECTOR3 movePos;	// �ړ��ʒu
		D3DXVECTOR3 targetPos;	// �ڕW�ʒu	
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 rotOld;		// ����(�ߋ�)
		D3DXVECTOR3	size;		// �T�C�Y
		D3DXCOLOR col;			// ���_�J���[
		int nShape;				// �`��
		int nStandTime;			// �ҋ@����
		bool bContact;			// �ڐG�t���O
		bool bActivation;		// �����t���O
		int nLife;				// ����
		int nLifeMax;			// �����̍ő�l
		float fRadius;			// ���a
		int nCntRadius;			// ���a�E���ڎ���
		float fRadiusRate;		// ���a�̊���
		bool bSet;				// �z�u�t���O
		int nChain;				// �A���J�E���g
		bool bBom;				// �����t���O
		int nID;				// ���g��ID
	};

	// ***** �֐� *****
	/* �R���X�g���N�^	*/CCube(int nPriority = PRIO_CUBE);
	/* �f�X�g���N�^		*/~CCube();

	// -- ���C�� -------------------------------
	/* ������	*/HRESULT Init(void);
	/* �I��		*/void Uninit(void);
	/* �X�V		*/void Update(void);
	/* �`��		*/void Draw(void);
	/* ����		*/static CCube *Create(int nType, D3DXVECTOR3 pos);

	// -- �ݒ� -------------------------------
	/* �ʒu			*/void CubeSetPos(const D3DXVECTOR3 pos) { m_Info.pos = m_Info.posOld = pos; }
	/* ����			*/void CubeSetRot(const D3DXVECTOR3 rot) { m_Info.rot = rot; }
	/* �F			*/void CubeSetColor(const D3DXCOLOR col) { m_Info.col = col; }
	/* �T�C�Y		*/void CubeSetSize(const D3DXVECTOR3 size) { m_Info.size = size; }
	/* ����			*/void CubeSetLife(const int nLife) { m_Info.nLife = nLife; }
	/* ���			*/void CubeSetType(const int type) { m_Info.nShape = type; }
	/* �擪�t���O	*/void CubeLeadSet(const bool bSet) { bLeadSet = bSet; }

	// -- �擾 -------------------------------
	/* �ʒu			*/D3DXVECTOR3 CubeGetPos(void) { return m_Info.pos; }
	/* ����			*/D3DXVECTOR3 GetRot(void) { return m_Info.rot; }
	/* �F			*/D3DXCOLOR CubeGetColor(void) { return m_Info.col; }
	/* �T�C�Y		*/D3DXVECTOR3 CubeGetSize(void) { return m_Info.size; }
	/* �z�u�t���O	*/bool CubeGetSet(void) { return m_Info.bSet; }
	/* �擪�t���O	*/static bool GetLeadSet(void) { return bLeadSet; }
	/* �A���J�E���g	*/int GetChain(void) { return m_Info.nChain; }
	/* ID			*/int GetID(void) { return m_Info.nID; }

private:

	// ***** �֐� ***** correction
	/* �ʒu�␳			*/bool Correction(VECTOR vector, D3DXVECTOR3 pos);
	/* �ڐG����			*/bool Contact(int mode,VECTOR vector, D3DXVECTOR3 pos);
	/* �����蔻��		*/bool Collsion(D3DXVECTOR3 pos, D3DXVECTOR3 PairPos, D3DXVECTOR3 size, D3DXVECTOR3	PairSize);
	/* �G�Ƃ̓����蔻�� */void EnemyCollsion(D3DXVECTOR3 pos);
	/* �����蔻��(����)	*/bool Collsion(VECTOR vector,CObject *pObj,CObject *pPairObj);
	/* �j�󏈗�			*/void Destruction(CCube *pCube);


	// ***** �ϐ� *****
	static int m_nNumAll;	// �L���[�u�̑���
	static int m_nNumChain;	// �A���̑���
	static bool bLeadSet;	// �擪�z�u�t���O
	Info m_Info;			// �v���C���[���

};
#endif