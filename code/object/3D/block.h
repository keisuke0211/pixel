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
		D3DXVECTOR3 rot;		// ����
		D3DXVECTOR3	size;		// �T�C�Y
		D3DCOLOR col;			// ���_�J���[
		int nType;				// ���
		int nLife;				// ����
		int nLifeMax;			// �����̍ő�l
		float Width;			// ��
		float Height;			// ����
		float Depth;			// ���s��
	} Info;

	// �z�u���
	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		int nType;			// ���
		int nNumX;			// X �u���b�N��
		int nNumY;			// Y �u���b�N��
		int nNumZ;			// Z �u���b�N��
		float Width;		// ��
		float Height;		// ����
		float Depth;		// ���s��
	} SetInfo;

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
	
	static void Load(void);				// �ǂݍ���
	static void SetBlock(int nNumSet);	// �z�u

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

	// ***** �񋓌^ *****

	// �ݒ荀��
	typedef enum
	{
		SET_TYPE,	// ���
		SET_POS,	// �ʒu
		SET_POS_Y,	// �ʒu Y
		SET_POS_Z,	// �ʒu Z
		SET_NUM,	// �u���b�N��
		SET_NUM_Y,	// �u���b�N�� Y
		SET_NUM_Z,	// �u���b�N�� Z
		SET_MAX,
	}SET;

	// ***** �ϐ� *****
	Info m_Info;				// �v���C���[���
	static SetInfo *pSetInfo;	// �Z�b�g���

};
#endif