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

	// ***** ��` *****
	static const int MAX_TEXTURE = 50;	// �e�N�X�`���̍ő吔

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
	CFloor(int nPriority = TYPE_FLOOR);	// �R���X�g���N�^
	~CFloor();							// �f�X�g���N�^

	// ����
	static CFloor *Create(void);

	HRESULT Init(void);	// ������
	void Uninit(void);	// �I��
	void Update(void);	// �X�V
	void Draw(void);	// �`��

	static HRESULT Load(char *pPath);			// �e�N�X�`���̐��� 
	static void Unload(void);					// �e�N�X�`���̔j��

	/* �擾 */
	Info GetInfo() { return m_Info; }	// �v���C���[���
private:

	// ***** �ϐ� *****
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];		// ���L�e�N�X�`��
	static int m_nTexture;									// �e�N�X�`���̐�
	Info m_Info;	// �v���C���[���

};
#endif