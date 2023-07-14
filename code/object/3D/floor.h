//========================================
// 
// ������
// 
//========================================
// *** floor.h ***
//========================================
#ifndef _FLOOR_H_
#define _FLOOR_H_

#include "../../main.h"
#include "../object3D.h"

//****************************************
// �N���X
//****************************************
class CFloor : public CObject3D
{
public:

	// ***** �\���� *****

	// �v���C���[���
	typedef struct
	{
		D3DXVECTOR3 pos;			// �ʒu
		D3DXVECTOR3 rot;			// ����
		float fWidth;				// ��
		float fHeight;				// ����
	} Info;

	// ***** �֐� *****
	CFloor(int nPriority = PRIO_OBJECT);	// �R���X�g���N�^
	~CFloor();								// �f�X�g���N�^

	// ����
	static CFloor *Create(void);

	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

	/* �擾 */
	Info GetInfo() { return m_Info; }	// �v���C���[���
private:

	// ***** �ϐ� *****
	Info m_Info;	// �v���C���[���

};
#endif