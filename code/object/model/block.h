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

	// ���
	enum STATE
	{
		STATE_NORMAL = 0,	// �ʏ�
		STATE_BREAK,		// �j���
		STATE_INVISIBLE,	// ����
		STATE_MAX,
	};

	// ***** �\���� *****

	// ��ޏ��
	struct TypeInfo
	{
		int nModelID;	// ���f��ID
		int nState;		// ���
	};

	// �u���b�N���
	struct Info
	{
		D3DXVECTOR3 pos;		// �ʒu
		D3DXVECTOR3 posOld;		// �ʒu(�ߋ�)
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3 rotOld;		// ����(�ߋ�)
		D3DXVECTOR3	size;		// �T�C�Y
		D3DXCOLOR col;			// ���_�J���[
		int nModelID;			// ���
		STATE state;			// ���
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
	static CBlock *Create(int nType,D3DXVECTOR3 pos,int nState);

	/* ������		*/HRESULT Init(void);
	/* �I��			*/void Uninit(void);
	/* �X�V			*/void Update(void);
	/* �`��			*/void Draw(void);
	/* �ǂݍ���		*/static void Load(void);
	/* HIT			*/void HitBlock(void);
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
	/* ���		*/int GetBlockType(void) { return m_Info.nModelID; }
	/* �o��		*/static bool IsExit(void) { return m_bExit; }
	/* �o��		*/static int GetBlockExit(void) { return m_nCntExit; }
	/* �o��		*/static bool IsExitCamera(void) { return m_bExitCamera; }

private:	

	// ***** �֐� *****
	/* TNT			*/void TntBlock(void);
	/* �Ђъ����	*/void CrackRock(void);
	/* �o�����		*/void ExitOpen(void);

	// ***** �ϐ� *****
	static D3DXVECTOR3 m_CameraRot;	// �����̕ۑ�
	static float m_CameraHeigth;	// �����̕ۑ�

	Info m_Info;					// �u���b�N���
	static TypeInfo *m_TypeInfo;	// ��ޏ��
	
	static bool m_bExit;			// �o���@�i�o�����J�����̃t���N�j
	static bool m_bExitCamera;		// �o���J����
	static int m_nCntExit;			// �o���ɃJ�����������鎞��


};
#endif