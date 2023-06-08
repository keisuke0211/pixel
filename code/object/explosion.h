//========================================
// 
// ��������
// 
//========================================
// *** explosion.h ***
//========================================
#ifndef _EXPLOSION_H_	//���̃}�N����`������ĂȂ�������
#define _EXPLOSION_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include "../main.h"
#include "object2D.h"

//==================================================
// ��`
//==================================================
class CExplosion : public CObject2D
{
public:

	// ***** ��` *****
	static const int MAX_TEXTURE = 50;	// �e�N�X�`���̍ő吔

	// ***** �\���� *****
	typedef struct
	{
		D3DXVECTOR3 pos;//�ʒu
		D3DXCOLOR col;//�F
		int nCounterAnim;//�A�j���[�V�����J�E���^�[
		int nPatternAnim;//�A�j���[�V�����p�^�[��No.
		int nLife;
	}Info;

	// ***** �֐� *****
	CExplosion(int nPriority = TYPE_EFFECT);		// �f�t�H���g�R���X�g���N�^
	~CExplosion();		// �f�X�g���N�^

	/* ���C�� */
	static HRESULT Load(char *pPath);			// �e�N�X�`���̐��� 
	static void Unload(void);					// �e�N�X�`���̔j��

	// ����
	static CExplosion *Create(D3DXVECTOR3 pos);


	HRESULT Init(void);				// ������
	void Uninit(void);				// �I��
	void Update(void);				// �X�V
	void Draw(void);				// �`��

	/* �擾 */
	Info GetInfo() { return m_Info; }	// �v���C���[���

private:
	// ***** �ϐ� *****
	Info m_Info;	// ���

	// ***** �ÓI�ϐ� *****
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_TEXTURE];	// ���L�e�N�X�`��
	static int m_nTexture;								// �e�N�X�`���̐�
};

#endif // !_TEXTURE_H_
