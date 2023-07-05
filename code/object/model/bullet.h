//========================================
// 
// �e����
// 
//========================================
// *** bullet.h ***
//========================================
#ifndef _BULLET_H_
#define _BULLET_H_

#include "../../main.h"
#include "../objectX.h"

//****************************************
// �N���X
//****************************************
class CBullet : public CObjectX
{
public:

	// ***** �\���� *****

	// �e���
	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		D3DXVECTOR3 posOld;	// �ʒu(�ߋ�)
		D3DXVECTOR3 rot;	// ����
		D3DXVECTOR3 rotOld;	// ����(�ߋ�)
		D3DXVECTOR3 move;	// �ړ���
		D3DXVECTOR3	size;	// �T�C�Y
		D3DCOLOR col;		// ���_�J���[
		int nType;			// ���
		int nLife;			// ����

		float fWidth;		// ��
		float fHeight;		// ����
		bool bHit;			// �q�b�g�t���O
	} Info;

	// ***** �֐� *****
	CBullet(int nPriority = PRIO_OBJX);
	~CBullet();

	/* ���C�� */

	// ����
	static CBullet *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	HRESULT Init(void);				// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��

	/* �擾 */
	Info GetInfo() { return m_Info; }					// �e���
	D3DXVECTOR3 GetPos() { return m_Info.pos; }			// �ʒu
	D3DXVECTOR3 GetPosOld() { return m_Info.posOld; }	// �ʒu(�ߋ�)
	D3DXVECTOR3 GetRot() { return m_Info.rot; }			// ����
	D3DXVECTOR3 GetMove() { return m_Info.move; }		// �ړ���

private:

	// ***** �֐� *****
	bool Collsion(VECTOR vector, D3DXVECTOR3 pos);	// �����蔻��

	// ***** �ϐ� *****
	Info m_Info;	// ���
};
#endif