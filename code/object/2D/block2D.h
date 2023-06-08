//========================================
// 
// �u���b�N����
// 
//========================================
//  *** block2D.h ***
//========================================
#ifndef _BLOCK2D_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _BLOCK2D_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

#include "../object2D.h"
#include "../../main.h"

//****************************************
// �N���X��`
//****************************************
class CBlock2D :public CObject2D
{
public:

	// ***** �\���� *****

	// �v���C���[���
	typedef struct
	{
		D3DXVECTOR3 pos;	// �ʒu
		float fWidth;		// ��
		float fHeight;		// ����
	} Info;

	// ***** �֐� *****
	CBlock2D(int nPriority = TYPE_BLOCK);	// �R���X�g���N�^
	virtual ~CBlock2D();					// �f�X�g���N�^
	static HRESULT Load(char *pPath);		// �e�N�X�`���ǂݍ���
	static void Unload(void);				// �e�N�X�`���j��
	HRESULT Init(void);						// ������
	void Uninit(void);						// �I��
	void Update(void);						// �X�V
	void Draw(void);						// �`��

	// ����
	static CBlock2D *Create(D3DXVECTOR3 pos);

	/* �擾 */
	Info GetInfo() { return m_Info; }	// �v���C���[���

private:

	// ***** �ϐ� *****
	Info m_Info;	// �v���C���[���

	// ***** �ÓI�ϐ� *****
	static LPDIRECT3DTEXTURE9 m_pTexture;	// ���L�e�N�X�`��
};

#endif