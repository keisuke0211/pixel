//========================================
// 
// �e�X�g
// 
//========================================
// *** test.h ***
//========================================
#ifndef _TEST_H_	//���̃}�N����`������ĂȂ�������
#define _TEST_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

#include "../../main.h"
#include "../object2D.h"

//****************************************
//�@�N���X
//****************************************
class CTest : public CObject2D
{
public:

	// ***** �\���� *****

	// ���ʏ��
	struct Info
	{
		D3DXVECTOR3 pos;			// �ʒu
		D3DXVECTOR3 rot;			// ����
		D3DXVECTOR2 size;			// �傫��
		D3DXCOLOR col;				// �F
		int nLife;					// ����
		int nLifeMax;				// �����̍ő�l
	};

	// ***** �֐� *****
	CTest(int nPriority = PRIO_UI);
	~CTest();

	// -- ���C�� ------------------------------------------
	/* ������		*/HRESULT Init(void);
	/* �I��			*/void Uninit(void);
	/* �X�V			*/void Update(void);
	/* �`��			*/void Draw(void);
	/* ����			*/static CTest *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	static void TextSetTexture(LPDIRECT3DTEXTURE9 pTexture);

private:

	static LPDIRECT3DTEXTURE9 m_pTexture; // �e�N�X�`��

	// ***** �ϐ� *****
	Info m_Info;		// ���
};

#endif