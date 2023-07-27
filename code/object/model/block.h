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
	struct Info
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 posOld;		// �ʒu(�ߋ�)
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 rotOld;		// ����(�ߋ�)
		D3DXVECTOR3	size;		// �T�C�Y
		D3DXCOLOR col;			// ���_�J���[
		int nType;				// ���
		float fRadius;			// ���a
		int nCntRadius;			// ���a�E���ڎ���
		float fRadiusRate;		// ���a�̊���
		bool bSet;				// �z�u�t���O

		int nEraseTime;			// �����܂ł̎���
		bool bErase;			// �����t���O
	};

	// ***** �֐� *****
	CBlock(int nPriority = PRIO_BLOCK);
	~CBlock();

	// ����
	static CBlock *Create(int nType,D3DXVECTOR3 pos);

	/* ������		*/HRESULT Init(void);
	/* �I��			*/void Uninit(void);
	/* �X�V			*/void Update(void);
	/* �`��			*/void Draw(void);
	/* HIT			*/void HitBlock(void);
	/* TNT			*/void TntBlock(void);
	/* �����蔻��	*/void ModelCollsion(PRIO nPrio, TYPE nType, D3DXVECTOR3 pos);
	
	// -- �ݒ� ---------------------------------------------
	/* �ʒu		*/virtual void SetBlockPos(const D3DXVECTOR3 pos) { m_Info.pos = pos; }
	/* ����		*/void SetBlockRot(const D3DXVECTOR3 rot) { m_Info.rot = rot; }
	/* �F		*/void SetBlockColor(const D3DXCOLOR col) { m_Info.col = col; }
	/* �傫��	*/void SetBlockSize(const D3DXVECTOR3 size) { m_Info.size = size; }

	// -- ���� ---------------------------------------------
	/* �ʒu		*/D3DXVECTOR3 GetBlockPos(void) { return m_Info.pos; }
	/* ����		*/D3DXVECTOR3 GetBlockRot(void) { return m_Info.rot; }
	/* �F		*/D3DXCOLOR GetBlockColor(void) { return m_Info.col; }
	/* �傫��	*/D3DXVECTOR3 GetBlockSize(void) { return m_Info.size; }
	/* ���		*/int GetBlockType(void) { return m_Info.nType; }

private:

	// ***** �ϐ� *****
	Info m_Info;				// �v���C���[���

};
#endif