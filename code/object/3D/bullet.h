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
		D3DXVECTOR3 rot;	// ����
		D3DXVECTOR3 move;	// �ړ���
		int nType;			// ���
		int nLife;			// ����
		float fWidth;		// ��
		float fHeight;		// ����
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
	Info GetInfo() { return m_Info; }				// �v���C���[���

private:

	// ***** �֐� *****
	bool Collsion(D3DXVECTOR3 pos);					// �����蔻��

	// ***** �ϐ� *****
	Info m_Info;	// ���


};
#endif